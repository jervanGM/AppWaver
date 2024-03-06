#include "protocol_drv.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <avsystem/commons/avs_sched.h>

#include <anjay/anjay.h>
#include <anjay/attr_storage.h>
#include <anjay/core.h>
#include <anjay/security.h>
#include <anjay/server.h>
#include <nvs_flash.h>

#include "wls_port.h"
#include "default_config.h"
#include "firmware_update.h"
#include "objects/objects.h"
#include "sdkconfig.h"

#ifdef CONFIG_ANJAY_SECURITY_MODE_CERTIFICATES
extern const uint8_t CLIENT_PRIVATE_KEY[] asm("_binary_client_key_der_start");
extern const uint32_t CLIENT_PRIVATE_KEY_LEN asm("client_key_der_length");
extern const uint8_t CLIENT_CERT[] asm("_binary_client_cert_der_start");
extern const uint32_t CLIENT_CERT_LEN asm("client_cert_der_length");
extern const uint8_t SERVER_CERT[] asm("_binary_server_cert_der_start");
extern const uint32_t SERVER_CERT_LEN asm("server_cert_der_length");
#else
static char PSK[ANJAY_MAX_SECRET_KEY_SIZE];
static char IDENTITY[ANJAY_MAX_PK_OR_IDENTITY_SIZE];
#endif // CONFIG_ANJAY_SECURITY_MODE_CERTIFICATES

#ifdef CONFIG_ANJAY_CLIENT_SOCKET_TCP
#    define MAIN_PREFERRED_TRANSPORT "T"
#else
#    define MAIN_PREFERRED_TRANSPORT "U"
#endif // CONFIG_ANJAY_CLIENT_TCP_SOCKET

static char SERVER_URI[ANJAY_MAX_PK_OR_IDENTITY_SIZE];
static char ENDPOINT_NAME[ANJAY_MAX_PK_OR_IDENTITY_SIZE];

static const anjay_dm_object_def_t **DEVICE_OBJ;
static const anjay_dm_object_def_t **TIME_CONTROL_OBJ;

static anjay_t *anjay;
static avs_sched_handle_t sensors_job_handle;
static avs_sched_handle_t connection_status_job_handle;

static int read_anjay_config();

// Installs Security Object and adds and instance of it.
// An instance of Security Object provides information needed to connect to
// LwM2M server.
static int setup_security_object(anjay_t *anjay) {
    if (anjay_security_object_install(anjay)) {
        return -1;
    }

    anjay_security_instance_t security_instance = {
        .ssid = 1,
        .server_uri = SERVER_URI,
#if defined(CONFIG_ANJAY_SECURITY_MODE_CERTIFICATES)
        .security_mode = ANJAY_SECURITY_CERTIFICATE,
        .public_cert_or_psk_identity = CLIENT_CERT,
        .public_cert_or_psk_identity_size = CLIENT_CERT_LEN,
        .private_cert_or_psk_key = CLIENT_PRIVATE_KEY,
        .private_cert_or_psk_key_size = CLIENT_PRIVATE_KEY_LEN,
        .server_public_key = SERVER_CERT,
        .server_public_key_size = SERVER_CERT_LEN
#elif defined(CONFIG_ANJAY_SECURITY_MODE_PSK)
        .security_mode = ANJAY_SECURITY_PSK,
        .public_cert_or_psk_identity = (const uint8_t *) IDENTITY,
        .public_cert_or_psk_identity_size = strlen(IDENTITY),
        .private_cert_or_psk_key = (const uint8_t *) PSK,
        .private_cert_or_psk_key_size = strlen(PSK)
#else
        .security_mode = ANJAY_SECURITY_NOSEC
#endif // CONFIG_ANJAY_SECURITY_MODE_CERTIFICATES
    };

    // Anjay will assign Instance ID automatically
    anjay_iid_t security_instance_id = ANJAY_ID_INVALID;
    if (anjay_security_object_add_instance(anjay, &security_instance,
                                           &security_instance_id)) {
        return -1;
    }

    return 0;
}

// Installs Server Object and adds and instance of it.
// An instance of Server Object provides the data related to a LwM2M Server.
static int setup_server_object(anjay_t *anjay) {
    if (anjay_server_object_install(anjay)) {
        return -1;
    }

    const anjay_server_instance_t server_instance = {
        // Server Short ID
        .ssid = 1,
        // Client will send Update message often than every 60 seconds
        .lifetime = 60,
        // Disable Default Minimum Period resource
        .default_min_period = -1,
        // Disable Default Maximum Period resource
        .default_max_period = -1,
        // Disable Disable Timeout resource
        .disable_timeout = -1,
        // Sets preferred transport
        .binding = MAIN_PREFERRED_TRANSPORT
    };

    // Anjay will assign Instance ID automatically
    anjay_iid_t server_instance_id = ANJAY_ID_INVALID;
    if (anjay_server_object_add_instance(anjay, &server_instance,
                                         &server_instance_id)) {
        return -1;
    }

    return 0;
}

static void update_objects_job(avs_sched_t *sched, const void *anjay_ptr) {
    anjay_t *anjay = *(anjay_t *const *) anjay_ptr;

    device_object_update(anjay, DEVICE_OBJ);
    custom_object_update(anjay, TIME_CONTROL_OBJ);

    AVS_SCHED_DELAYED(sched, &sensors_job_handle,
                      avs_time_duration_from_scalar(1, AVS_TIME_S),
                      &update_objects_job, &anjay, sizeof(anjay));
}

// Periodically issues a Send message with application type and current time
static void send_job(avs_sched_t *sched, const void *anjay_ptr) {
    anjay_t *anjay = *(anjay_t *const *) anjay_ptr;

    custom_object_send(anjay, TIME_CONTROL_OBJ);

    // Schedule run of the same function after 10 seconds
    AVS_SCHED_DELAYED(sched, NULL,
                      avs_time_duration_from_scalar(1, AVS_TIME_S), send_job,
                      &anjay, sizeof(anjay));
}

static void update_connection_status_job(avs_sched_t *sched,
                                         const void *anjay_ptr) {
    anjay_t *anjay = *(anjay_t *const *) anjay_ptr;

    static bool connected_prev = true;
    bool err;

    if (connected_prev) {
        connected_prev = false;
        anjay_transport_enter_offline(anjay, ANJAY_TRANSPORT_SET_IP);
    } else if (!connected_prev) {
        anjay_transport_exit_offline(anjay, ANJAY_TRANSPORT_SET_IP);
        connected_prev = true;
    }

    AVS_SCHED_DELAYED(sched, &connection_status_job_handle,
                      avs_time_duration_from_scalar(1, AVS_TIME_S),
                      update_connection_status_job, &anjay, sizeof(anjay));
}

static void anjay_init(void) {
    const anjay_configuration_t CONFIG = {
        .endpoint_name = ENDPOINT_NAME,
        .in_buffer_size = 4000,
        .out_buffer_size = 4000,
        .msg_cache_size = 4000
    };

    // Read necessary data for object install
    read_anjay_config();

    anjay = anjay_new(&CONFIG);
    if (!anjay) {
        TRACE_ERROR("Could not create Anjay object");
        return;
    }

    // Install Attribute storage and setup necessary objects
    if (setup_security_object(anjay) || setup_server_object(anjay)
            || fw_update_install(anjay)) {
        TRACE_ERROR("Failed to install core objects");
        return;
    }

    if (!(DEVICE_OBJ = device_object_create())
            || anjay_register_object(anjay, DEVICE_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        return;
    }

    if ((TIME_CONTROL_OBJ = custom_object_create())) {
        anjay_register_object(anjay, TIME_CONTROL_OBJ);
    }

}

void anjay_main() {

    update_connection_status_job(anjay_get_scheduler(anjay), &anjay);
    update_objects_job(anjay_get_scheduler(anjay), &anjay);
    send_job(anjay_get_scheduler(anjay), &anjay);

    anjay_event_loop_run(anjay, avs_time_duration_from_scalar(1, AVS_TIME_S));

    avs_sched_del(&sensors_job_handle);
    avs_sched_del(&connection_status_job_handle);
    anjay_delete(anjay);

    if (fw_update_requested()) {
        fw_update_reboot();
    }
}

static int read_nvs_anjay_config(void) {
    nvs_handle_t nvs_h;

    if (nvs_open(MAIN_NVS_CONFIG_NAMESPACE, NVS_READONLY, &nvs_h)) {
        return -1;
    }

    int result = (nvs_get_str(nvs_h, "uri", SERVER_URI,
                              &(size_t) { sizeof(SERVER_URI) })
                  || nvs_get_str(nvs_h, "endpoint_name", ENDPOINT_NAME,
                                 &(size_t) { sizeof(ENDPOINT_NAME) })
    #ifdef CONFIG_ANJAY_SECURITY_MODE_PSK
                  || nvs_get_str(nvs_h, "psk", PSK, &(size_t) { sizeof(PSK) })
                  || nvs_get_str(nvs_h, "identity", IDENTITY,
                                 &(size_t) { sizeof(IDENTITY) })
    #endif // CONFIG_ANJAY_SECURITY_MODE_PSK
                          )
                         ? -1
                         : 0;
    nvs_close(nvs_h);

    return result;
}

static int read_anjay_config(void) {
    int err = 0;
    TRACE_INFO("Opening Non-Volatile Storage (NVS) handle... ");
    if (read_nvs_anjay_config()) {
        TRACE_WARNING("Reading from NVS has failed, attempt with Kconfig");
        snprintf(ENDPOINT_NAME, sizeof(ENDPOINT_NAME), "%s",
                 CONFIG_ANJAY_CLIENT_ENDPOINT_NAME);
        snprintf(SERVER_URI, sizeof(SERVER_URI), "%s",
                 CONFIG_ANJAY_CLIENT_SERVER_URI);
        #ifdef CONFIG_ANJAY_SECURITY_MODE_PSK
        snprintf(PSK, sizeof(PSK), "%s", CONFIG_ANJAY_CLIENT_PSK_KEY);
        snprintf(IDENTITY, sizeof(IDENTITY), "%s",CONFIG_ANJAY_CLIENT_PSK_IDENTITY);
        #endif // CONFIG_ANJAY_SECURITY_MODE_PSK
                err = -1;
    }
    return err;
}

// static int read_nvs_wifi_config(const char *namespace,
//                                 wifi_config_t *wifi_config,
//                                 uint8_t *en) {
//     nvs_handle_t nvs_h;

//     if (nvs_open(namespace, NVS_READONLY, &nvs_h)) {
//         return -1;
//     }

//     int result =
//             (nvs_get_str(nvs_h, MAIN_NVS_WIFI_SSID_KEY,
//                          (char *) wifi_config->sta.ssid,
//                          &(size_t) { sizeof(wifi_config->sta.ssid) })
//              || nvs_get_str(nvs_h, MAIN_NVS_WIFI_PASSWORD_KEY,
//                             (char *) wifi_config->sta.password,
//                             &(size_t) { sizeof(wifi_config->sta.password) })
//              || nvs_get_u8(nvs_h, MAIN_NVS_ENABLE_KEY, en))
//                     ? -1
//                     : 0;
//     nvs_close(nvs_h);

//     return result;
// }

// static int read_wifi_config(void) {
//     wifi_config_t preconf_wifi_config = { 0 };
//     uint8_t preconf_en = 0;
//     wifi_config_t writable_wifi_config = { 0 };
//     uint8_t writable_en = 0;
//     int err = 0;

//     TRACE_INFO("Opening Non-Volatile Storage (NVS) handle... ");
//     if (read_nvs_wifi_config(MAIN_NVS_CONFIG_NAMESPACE, &preconf_wifi_config,
//                              &preconf_en)) {
//         TRACE_WARNING("Reading from NVS has failed, attempt with Kconfig");

//         snprintf((char *) preconf_wifi_config.sta.ssid,
//                  sizeof(preconf_wifi_config.sta.ssid), "%s",
//                  CONFIG_ANJAY_WIFI_SSID);
//         snprintf((char *) preconf_wifi_config.sta.password,
//                  sizeof(preconf_wifi_config.sta.password), "%s",
//                  CONFIG_ANJAY_WIFI_PASSWORD);

//         err = -1;
//     }

//     TRACE_INFO("Opening Non-Volatile Storage (NVS) with wifi writable ",
//             "configuration handle... ");
//     if (read_nvs_wifi_config(MAIN_NVS_WRITABLE_WIFI_CONFIG_NAMESPACE,
//                              &writable_wifi_config, &writable_en)) {
//         TRACE_WARNING("Reading from NVS has failed");

//         err = -1;
//     }
//     preconf_wifi_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
//     writable_wifi_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;

//     return err;
// }

// static int wifi_config_check(wifi_config_t *wifi_config) {
//     if ((strlen((char *) wifi_config->sta.ssid)) == 0) {
//         return -1;
//     }
//     return 0;
// }


void init(void) {
    const IWlsPort *port = hal_wls_get_port();

    anjay_init();

    port->init();
    //read_wifi_config();

    //wifi_config_t wifi_config = { 0 };

    port->connect();
}