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
#include <anjay/lwm2m_send.h>

#include "wls_port.h"
#include "default_config.h"
#include "firmware_update.h"
#include "objects/objects.h"
#include "utils.h"
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
static const anjay_dm_object_def_t **PLANT_DATA_OBJ;
static const anjay_dm_object_def_t **TIME_BUF_OBJ;
static const anjay_dm_object_def_t **PER_DATA_OBJ;
static const anjay_dm_object_def_t **TEMP_DATA_OBJ;
static const anjay_dm_object_def_t **AIR_MOIST_DATA_OBJ;
static const anjay_dm_object_def_t **ACCELEROMETER_DATA_OBJ;
static const anjay_dm_object_def_t **BINARY_DATA_OBJ;

static anjay_t *anjay;
static avs_sched_handle_t sensors_job_handle;
static avs_sched_handle_t connection_status_job_handle;

static void read_anjay_config();

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
        .lifetime = 30,
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
    plant_object_update(anjay, PLANT_DATA_OBJ);
    time_object_update(anjay,TIME_BUF_OBJ);
    binary_object_update(anjay, BINARY_DATA_OBJ);
#ifdef ADVANCED
    accelerometer_object_update(anjay, ACCELEROMETER_DATA_OBJ);
    percentage_object_update(anjay,PER_DATA_OBJ);
    temperature_object_update(anjay,TEMP_DATA_OBJ);
    air_moist_object_update(anjay,AIR_MOIST_DATA_OBJ);
#endif

    AVS_SCHED_DELAYED(sched, &sensors_job_handle,
                      avs_time_duration_from_scalar(100, AVS_TIME_MS),
                      &update_objects_job, &anjay, sizeof(anjay));
}


static void update_connection_status_job(avs_sched_t *sched,
                                         const void *anjay_ptr) {
    anjay_t *anjay = *(anjay_t *const *) anjay_ptr;

    static bool connected_prev = true;
    bool err = false;

    if (connected_prev && err) {
        connected_prev = false;
        anjay_transport_enter_offline(anjay, ANJAY_TRANSPORT_SET_IP);
    } else if (!connected_prev && !err) {
        anjay_transport_exit_offline(anjay, ANJAY_TRANSPORT_SET_IP);
        connected_prev = true;
    }

    AVS_SCHED_DELAYED(sched, &connection_status_job_handle,
                      avs_time_duration_from_scalar(1, AVS_TIME_S),
                      update_connection_status_job, &anjay, sizeof(anjay));
}

static void read_anjay_config(void)
{
    TRACE_INFO("Getting server credentials... ");
    device_id_t id;
    get_device_id(id.value);
    snprintf(ENDPOINT_NAME, sizeof(ENDPOINT_NAME), "%s%s",
             CONFIG_ANJAY_CLIENT_ENDPOINT_NAME,id.value);
    if ((strstr(ENDPOINT_NAME, CONFIG_ANJAY_CLIENT_ENDPOINT_NAME) == NULL) ||
        (strstr(ENDPOINT_NAME, id.value) == NULL))
    {
        TRACE_ERROR("Endpoint name has not been configurated correctly");
        store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_ANJAY_SERVER_CONFIG_ERROR);
        return;
    }
    snprintf(SERVER_URI, sizeof(SERVER_URI), "%s",
             CONFIG_ANJAY_CLIENT_SERVER_URI);
    if (strcmp(SERVER_URI, CONFIG_ANJAY_CLIENT_SERVER_URI))
    {
        TRACE_ERROR("Server URI has not been configurated correctly");
        store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_ANJAY_SERVER_CONFIG_ERROR);
        return;
    }
#ifdef CONFIG_ANJAY_SECURITY_MODE_PSK
    snprintf(PSK, sizeof(PSK), "%s", CONFIG_ANJAY_CLIENT_PSK_KEY);
    if (strcmp(PSK, CONFIG_ANJAY_CLIENT_PSK_KEY))
    {
        TRACE_ERROR("Server psk key has not been configurated correctly");
        store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_ANJAY_SERVER_CONFIG_ERROR);
        return;
    }
    snprintf(IDENTITY, sizeof(IDENTITY), "%s", ENDPOINT_NAME);
    if (strcmp(IDENTITY, ENDPOINT_NAME))
    {
        TRACE_ERROR("Client psk identity has not been configurated correctly");
        store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_ANJAY_SERVER_CONFIG_ERROR);
        return; 
    }
#endif // CONFIG_ANJAY_SECURITY_MODE_PSK
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
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_ANJAY_OBJ_CREATE_ERROR  );
        return;
    }
    // Install Attribute storage and setup necessary objects
    if (setup_security_object(anjay) || setup_server_object(anjay)
            || fw_update_install(anjay)) {
        TRACE_ERROR("Failed to install core objects");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_ANJAY_CORE_INSTALL_ERROR);
        return;
    }

    if (!(DEVICE_OBJ = device_object_create())
            || anjay_register_object(anjay, DEVICE_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_DEVICE_OBJ_INIT_ERROR);
        return; 
    }

    if (!(PLANT_DATA_OBJ = plant_data_object_create())
            || anjay_register_object(anjay, PLANT_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_PLANT_OBJ_INIT_ERROR);
        return; 
    }

    if (!(TIME_BUF_OBJ = time_object_create())
            || anjay_register_object(anjay, TIME_BUF_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_TIME_OBJ_INIT_ERROR);
        return; 
    }

    if (!(BINARY_DATA_OBJ = binary_object_create())
            || anjay_register_object(anjay, BINARY_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_BINARY_OBJ_INIT_ERROR);
        return; 
    }
#ifdef ADVANCED
    if (!(ACCELEROMETER_DATA_OBJ = accelerometer_data_object_create())
            || anjay_register_object(anjay, ACCELEROMETER_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_ACC_OBJ_INIT_ERROR);
        return; 
    }

    if (!(PER_DATA_OBJ = percentage_object_create())
            || anjay_register_object(anjay, PER_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_PER_OBJ_INIT_ERROR);
        return; 
    }

    if (!(TEMP_DATA_OBJ = temperature_object_create())
            || anjay_register_object(anjay, TEMP_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_TEMP_OBJ_INIT_ERROR);
        return; 
    }

    if (!(AIR_MOIST_DATA_OBJ = air_moist_object_create())
            || anjay_register_object(anjay, AIR_MOIST_DATA_OBJ)) {
        TRACE_ERROR("Could not register Device object");
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_AIR_MOIST_OBJ_INIT_ERROR);
        return; 
    }
#endif

}
void update_wireless_data(SNetworkData_t net_data)
{
    int64_t time_instances[4]={net_data.plant_time_start,net_data.plant_time_end,
                               net_data.axis_time_start,net_data.axis_time_end};
    uint8_t binary_data[4][DATA_BUFFER_SIZE*4];
    for (int i = 0; i < DATA_BUFFER_SIZE*4; i++) {
        binary_data[0][i] = net_data.serialized_plant_data[i];
        binary_data[1][i] = net_data.serialized_x_data[i];
        binary_data[2][i] = net_data.serialized_y_data[i];
        binary_data[3][i] = net_data.serialized_z_data[i];
    }

    plant_object_value_update(net_data.act_plant_data,PLANT_DATA_OBJ);
    time_object_value_update(time_instances,TIME_BUF_OBJ);
    device_object_time_update(net_data.current_time,DEVICE_OBJ);
    binary_object_value_update(binary_data,BINARY_DATA_OBJ);
#ifdef ADVANCED
    float per_instances[3]={net_data.av_light,net_data.av_sun,net_data.av_soil_moist};
    accelerometer_object_value_update(net_data.x_act_data,net_data.y_act_data,net_data.z_act_data,ACCELEROMETER_DATA_OBJ);
    percentage_object_value_update(per_instances,PER_DATA_OBJ);
    temperature_object_value_update(net_data.av_temp,TEMP_DATA_OBJ);
    air_moist_object_value_update(net_data.av_air_moist,AIR_MOIST_DATA_OBJ);
#endif
}

static void send_job(avs_sched_t *sched, const void *anjay_ptr) {
    anjay_t *anjay = *(anjay_t *const *) anjay_ptr;
    const anjay_ssid_t server_ssid = 1;

    // Allocate new batch builder.
    anjay_send_batch_builder_t *builder = anjay_send_batch_builder_new();

    if (!builder) {
        TRACE_ERROR("Failed to allocate batch builder");
        return;
    }

    int32_t res = 0;

    plant_object_send(builder,anjay, PLANT_DATA_OBJ);
    accelerometer_object_send(builder,anjay, ACCELEROMETER_DATA_OBJ);

    // After adding all values, compile our batch for sending.
    anjay_send_batch_t *batch = anjay_send_batch_builder_compile(&builder);

    if (!batch) {
        anjay_send_batch_builder_cleanup(&builder);
        TRACE_ERROR("Batch compile failed");
        return;
    }

    // Schedule our send to be run on next `anjay_sched_run()` call.
    res = (int32_t)anjay_send(anjay, server_ssid, batch, NULL, NULL);

    if (res) {
        TRACE_ERROR("Failed to send, result:", TO_STRING(res));
    }

    // After scheduling, we can release our batch.
    anjay_send_batch_release(&batch);

    // Schedule run of the same function after 10 seconds
    AVS_SCHED_DELAYED(sched, NULL,
                      avs_time_duration_from_scalar(1, AVS_TIME_S), send_job,
                      &anjay, sizeof(anjay));
}

void network_init(void) {
    const IWlsPort *port = hal_wls_get_port();
    if (port != NULL)
    {
        if(port->init() != WLS_DRV_OK)
        {
            store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_DRV_INIT_ERROR);
            TRACE_ERROR("A wireless communication task error has been produced during initialization");
            return; 
        }
        else
        {
            //TBD
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on init");
        return; 
    }
    

}

void network_connect(void)
{
    const IWlsPort *port = hal_wls_get_port();

    if (port != NULL)
    {
        if(port->connect() != WLS_DRV_OK)
        {
            store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_DRV_CONNECT_ERROR);
            TRACE_ERROR("A wireless communication task error has been produced during connection");
            return; 
        }
        else
        {
            //TBD
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on connection");
    }
    anjay_init();
    update_connection_status_job(anjay_get_scheduler(anjay), &anjay);
    update_objects_job(anjay_get_scheduler(anjay), &anjay);
    send_job(anjay_get_scheduler(anjay), &anjay);
    TRACE_INFO("Connecting endpoint",ENDPOINT_NAME,"to server",SERVER_URI);
}

void network_run() {

    const IWlsPort *port = hal_wls_get_port();

    if (port != NULL)
    {
        if(port->get_wifi_event() == WLS_RECONNECT_EVENT)
        {
          store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_DRV_RECONNECT_ERROR);
          TRACE_ERROR("Wireless communication task is trying to reconnect, check connections and credentials");
          return;           
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on network deinitialization");
        return; 
    }

    if(anjay_serve_any(anjay, avs_time_duration_from_scalar(1, AVS_TIME_S)))
    {
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_ANJAY_LOOP_ERROR);
        TRACE_ERROR("A failure was handle by middleware");
        return; 
    }
    if(anjay_all_connections_failed(anjay))
    {
        store_error_in_slot(WIRELESS_ERROR_SLOT,WLS_DRV_CONNECT_ERROR); 
        TRACE_ERROR("Connection failure with server");
        return; 
    }
    anjay_sched_run(anjay);
}

void network_deinit()
{
    const IWlsPort *port = hal_wls_get_port();
    network_disconnect();
    if (port != NULL)
    {
        if(port->reset() != WLS_DRV_OK)
        {
            store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_DRV_RESET_ERROR);
            TRACE_ERROR("A wireless communication task error has been produced during reset");
            return;
        }
        else
        {
            //TBD
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on network deinitialization");
    }

}

void network_disconnect()
{
    const IWlsPort *port = hal_wls_get_port();

    if (port != NULL)
    {
        if(port->disconnect() != WLS_DRV_OK)
        {
            store_error_in_slot(WIRELESS_ERROR_SLOT, WLS_DRV_DISCONNECT_ERROR);
            TRACE_ERROR("A wireless communication task error has been produced during disconnection");
            return;
        }
        else
        {
            //TBD
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on network deinitialization");
    }
    avs_sched_del(&sensors_job_handle);
    avs_sched_del(&connection_status_job_handle);
    anjay_delete(anjay);
}

void network_fota_reboot()
{
    fw_update_reboot();
}

bool network_check_fota()
{
    return fw_update_requested();
}

