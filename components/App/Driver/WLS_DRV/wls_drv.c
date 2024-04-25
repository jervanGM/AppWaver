#include "wls_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <esp_err.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_netif_ip_addr.h>
#include <esp_netif_types.h>
#include <esp_wifi.h>
#include <esp_wifi_default.h>
#include <esp_wifi_types.h>
#include <esp_system.h>
#include <esp_mac.h>
#include <nvs_flash.h>
#include "sdkconfig.h"

static wifi_config_t wifi_config;

#ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6
#    define MAX_IP6_ADDRS_PER_NETIF (5)
#    define NO_OF_IP_ADDRESSES_TO_WAIT_FOR (2)

#    if defined(CONFIG_ANJAY_WIFI_CONNECT_IPV6_PREF_LOCAL_LINK)
#        define ANJAY_CONNECT_PREFERRED_IPV6_TYPE ESP_IP6_ADDR_IS_LINK_LOCAL
#    elif defined(CONFIG_ANJAY_WIFI_CONNECT_IPV6_PREF_GLOBAL)
#        define ANJAY_CONNECT_PREFERRED_IPV6_TYPE ESP_IP6_ADDR_IS_GLOBAL
#    elif defined(CONFIG_ANJAY_WIFI_CONNECT_IPV6_PREF_SITE_LOCAL)
#        define ANJAY_CONNECT_PREFERRED_IPV6_TYPE ESP_IP6_ADDR_IS_SITE_LOCAL
#    elif defined(CONFIG_ANJAY_WIFI_CONNECT_IPV6_PREF_UNIQUE_LOCAL)
#        define ANJAY_CONNECT_PREFERRED_IPV6_TYPE ESP_IP6_ADDR_IS_UNIQUE_LOCAL
#    endif // if-elif ANJAY_WIFI_CONNECT_IPV6_PREF_...

#else
#    define NO_OF_IP_ADDRESSES_TO_WAIT_FOR (1)
#endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6

#define MAX_WAITING_TIME_FOR_IP 15000 // in ms

static bool ip_obtained = false;
static esp_netif_t *s_anjay_esp_netif = NULL;

#ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6
static esp_ip6_addr_t s_ipv6_addr;

/* types of ipv6 addresses to be displayed on ipv6 events */
static const char *s_ipv6_addr_types[] = { "ESP_IP6_ADDR_IS_UNKNOWN",
                                           "ESP_IP6_ADDR_IS_GLOBAL",
                                           "ESP_IP6_ADDR_IS_LINK_LOCAL",
                                           "ESP_IP6_ADDR_IS_SITE_LOCAL",
                                           "ESP_IP6_ADDR_IS_UNIQUE_LOCAL",
                                           "ESP_IP6_ADDR_IS_IPV4_MAPPED_IPV6" };
#endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6

static const char *TAG = "wireless_connect";

static void disconnect(void);
static void deinit(void);

/**
 * @brief Checks the netif description if it contains specified prefix.
 * All netifs created withing common connect component are prefixed with the
 * module TAG, so it returns true if the specified netif is owned by this module
 */
static bool is_our_netif(const char *prefix, esp_netif_t *netif) {
    return strncmp(prefix, esp_netif_get_desc(netif), strlen(prefix) - 1) == 0;
}

/* tear down connection, release resources */
static void stop(void) {
    disconnect();
    deinit();
}

static esp_ip4_addr_t s_ip_addr;
static int32_t last_wifi_event_id;

static void on_got_ip(void *arg,
                      esp_event_base_t event_base,
                      int32_t event_id,
                      void *event_data) {
    ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
    last_wifi_event_id = event_id;
    if (!is_our_netif(TAG, event->esp_netif)) {
        ESP_LOGW(TAG, "Got IPv4 from another interface \"%s\": ignored",
                 esp_netif_get_desc(event->esp_netif));
        return;
    }
    ESP_LOGI(TAG, "Got IPv4 event: Interface \"%s\" address: " IPSTR,
             esp_netif_get_desc(event->esp_netif), IP2STR(&event->ip_info.ip));
    memcpy(&s_ip_addr, &event->ip_info.ip, sizeof(s_ip_addr));
    ip_obtained = true;
}

#ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6

static void on_got_ipv6(void *arg,
                        esp_event_base_t event_base,
                        int32_t event_id,
                        void *event_data) {
    ip_event_got_ip6_t *event = (ip_event_got_ip6_t *) event_data;
    last_wifi_event_id = event_id;
    if (!is_our_netif(TAG, event->esp_netif)) {
        ESP_LOGW(TAG, "Got IPv6 from another netif: ignored");
        return;
    }
    esp_ip6_addr_type_t ipv6_type =
            esp_netif_ip6_get_addr_type(&event->ip6_info.ip);
    ESP_LOGI(TAG,
             "Got IPv6 event: Interface \"%s\" address: " IPV6STR ", type: %s",
             esp_netif_get_desc(event->esp_netif), IPV62STR(event->ip6_info.ip),
             s_ipv6_addr_types[ipv6_type]);
    if (ipv6_type == ANJAY_CONNECT_PREFERRED_IPV6_TYPE) {
        memcpy(&s_ipv6_addr, &event->ip6_info.ip, sizeof(s_ipv6_addr));
        ip_obtained = true;
    }
}

#endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6

static void on_wifi_disconnect(void *arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_data) {
    ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect...");
    last_wifi_event_id = event_id;
    esp_err_t err = esp_wifi_connect();
    if (err == ESP_ERR_WIFI_NOT_STARTED) {
        return;
    }
    ESP_ERROR_CHECK(err);
}

#ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6

static void on_wifi_connect(void *esp_netif,
                            esp_event_base_t event_base,
                            int32_t event_id,
                            void *event_data) {
    last_wifi_event_id = event_id;
    esp_netif_create_ip6_linklocal(esp_netif);
}

#endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6

int32_t get_last_wifi_event_id() {
    return last_wifi_event_id;
}

static esp_err_t connect() {
    snprintf((char *) wifi_config.sta.ssid,
                 sizeof(wifi_config.sta.ssid), "%s",
                 CONFIG_ANJAY_WIFI_SSID);
    snprintf((char *) wifi_config.sta.password,
                 sizeof(wifi_config.sta.password), "%s",
                 CONFIG_ANJAY_WIFI_PASSWORD);
    wifi_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT,
                                               WIFI_EVENT_STA_DISCONNECTED,
                                               &on_wifi_disconnect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                               &on_got_ip, NULL));
    #ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6
    ESP_ERROR_CHECK(
            esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED,
                                       &on_wifi_connect, s_anjay_esp_netif));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_GOT_IP6,
                                               &on_got_ipv6, NULL));
    #endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_LOGI(TAG, "Connecting to %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_connect();

    //ESP_ERROR_CHECK(esp_register_shutdown_handler(&stop));
    ESP_LOGI(TAG, "Waiting for IP(s)");
    // Obtener el tiempo actual en milisegundos
    uint32_t start_time = esp_log_timestamp();

    // Esperar hasta que se obtenga la dirección IP o se agote el tiempo de espera
    while (!ip_obtained && (esp_log_timestamp() - start_time < MAX_WAITING_TIME_FOR_IP)) {
        // Aquí puedes realizar otras tareas si es necesario
    }

    // Verificar si se ha obtenido la dirección IP o se ha agotado el tiempo de espera
    if (!ip_obtained) {
        ESP_LOGE(TAG, "Failed to obtain IP address within the timeout period");
        return ESP_FAIL;
    }
    // iterate over active interfaces, and print out IPs of "our" netifs
    esp_netif_t *netif = NULL;
    esp_netif_ip_info_t ip;
    for (int i = 0; i < esp_netif_get_nr_of_ifs(); ++i) {
        netif = esp_netif_next(netif);
        if (is_our_netif(TAG, netif)) {
            ESP_LOGI(TAG, "Connected to %s", esp_netif_get_desc(netif));
            ESP_ERROR_CHECK(esp_netif_get_ip_info(netif, &ip));

            ESP_LOGI(TAG, "- IPv4 address: " IPSTR, IP2STR(&ip.ip));
        #ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6
            esp_ip6_addr_t ip6[MAX_IP6_ADDRS_PER_NETIF];
            int ip6_addrs = esp_netif_get_all_ip6(netif, ip6);
            for (int j = 0; j < ip6_addrs; ++j) {
                esp_ip6_addr_type_t ipv6_type =
                        esp_netif_ip6_get_addr_type(&(ip6[j]));
                ESP_LOGI(TAG, "- IPv6 address: " IPV6STR ", type: %s",
                         IPV62STR(ip6[j]), s_ipv6_addr_types[ipv6_type]);
            }
        #endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6
        }
    }
    return ESP_OK;
}

static void disconnect(void) 
{
    ESP_ERROR_CHECK(esp_event_handler_unregister(
            WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &on_wifi_disconnect));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                                 &on_got_ip));
    #ifdef CONFIG_ANJAY_WIFI_CONNECT_IPV6
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_GOT_IP6,
                                                 &on_got_ipv6));
    ESP_ERROR_CHECK(esp_event_handler_unregister(
            WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &on_wifi_connect));
    #endif // CONFIG_ANJAY_WIFI_CONNECT_IPV6
    esp_err_t err = esp_wifi_stop();
    if (err == ESP_ERR_WIFI_NOT_INIT) {
        return;
    }
    ESP_ERROR_CHECK(err);
}

static void deinit(void) 
{
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_ERROR_CHECK(
            esp_wifi_clear_default_wifi_driver_and_handlers(s_anjay_esp_netif));
    esp_netif_destroy(s_anjay_esp_netif);
    s_anjay_esp_netif = NULL;
}

int8_t wifi_initialize(void) 
{
    ESP_LOGI(TAG, "Wifi initialization");
    if((nvs_flash_init() != ESP_OK) ||
       (esp_netif_init() != ESP_OK) ||
       (esp_event_loop_create_default() != ESP_OK)){
        return -1;
    }
    char *desc;

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    if(esp_wifi_init(&cfg) != ESP_OK){
        return -1;
    }

    esp_netif_inherent_config_t esp_netif_config =
            ESP_NETIF_INHERENT_DEFAULT_WIFI_STA();
    // Prefix the interface description with the module TAG
    // Warning: the interface desc is used in tests to capture actual
    // connection details (IP, gw, mask)
    asprintf(&desc, "%s: %s", TAG, esp_netif_config.if_desc);
    esp_netif_config.if_desc = desc;
    esp_netif_config.route_prio = 128;
    s_anjay_esp_netif = esp_netif_create_wifi(WIFI_IF_STA, &esp_netif_config);
    free(desc);
    esp_wifi_set_default_wifi_sta_handlers();
    return 0;
}

int8_t wifi_connect() {
    if(connect() != ESP_OK)
    {
        return -1;
    }
    return 0;
}

int8_t wifi_disconnect(void) {
    disconnect();
    if(esp_unregister_shutdown_handler(&stop) != ESP_OK)
    {
        return -1;
    }
    return 0;
}

int8_t wifi_deinitialize(void) {
    deinit();
    if(esp_unregister_shutdown_handler(&stop) != ESP_OK)
    {
        return -1;
    }
    return 0;
}


int8_t mac_get_default(uint8_t *mac) {
    if(esp_efuse_mac_get_default(mac) != ESP_OK)
    {
        return -1;
    }
    return 0;
}

void wireless_system_abort(const char *msg)
{
    esp_system_abort(msg);
}
