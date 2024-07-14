#ifndef PROTOCOL_DRV_H_
#define PROTOCOL_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_wireless_data.h"
#define MAIN_NVS_CONFIG_NAMESPACE "config"
#define MAIN_NVS_WRITABLE_WIFI_CONFIG_NAMESPACE "writable_wifi"
#define MAIN_NVS_WIFI_SSID_KEY "wifi_ssid"
#define MAIN_NVS_WIFI_PASSWORD_KEY "wifi_pswd"
#define MAIN_NVS_ENABLE_KEY "wifi_inter_en"

/**
 * @brief Updates wireless data received from the network.
 *
 * Updates various LwM2M objects with data received over the network.
 *
 * @param net_data Network data received.
 */
void update_wireless_data(SNetworkData_t net_data);

/**
 * @brief Initializes the network communication.
 *
 * Initializes the wireless port and establishes connection with the LwM2M server,
 * initializing Anjay framework and scheduling necessary update jobs.
 */
void network_init(void);

/**
 * @brief Establishes connection with the LwM2M server.
 *
 * Establishes connection with the LwM2M server, initializes Anjay framework
 * if not already initialized, and schedules necessary update jobs.
 */
void network_connect(void);

/**
 * @brief Executes the main network communication loop.
 *
 * Runs the main network communication loop, serving Anjay, handling middleware failures,
 * and managing server connection status.
 */
void network_run(void);

/**
 * @brief Deinitializes network communication.
 *
 * Disconnects from the LwM2M server, deinitializes Anjay framework, and resets
 * the wireless port.
 */
void network_deinit(void);

/**
 * @brief Disconnects from the LwM2M server.
 *
 * Disconnects from the LwM2M server and cancels all scheduled jobs.
 */
void network_disconnect(void);

/**
 * @brief Initiates firmware over-the-air (FOTA) update and reboot.
 *
 * Initiates firmware over-the-air (FOTA) update process and triggers device reboot.
 */
void network_fota_reboot(void);

/**
 * @brief Checks if a firmware over-the-air (FOTA) update is requested.
 *
 * Checks if a firmware over-the-air (FOTA) update is requested by the server.
 *
 * @return True if FOTA update is requested, false otherwise.
 */
bool network_check_fota(void);


#endif /* PROTOCOL_DRV_H_ */