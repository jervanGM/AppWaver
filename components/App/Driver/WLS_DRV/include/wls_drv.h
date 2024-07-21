#ifndef WLS_DRV_H_
#define WLS_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_err.h>
#include <esp_wifi.h>

/**
 * @brief Initialize the Wi-Fi subsystem.
 *
 * This function initializes the Wi-Fi subsystem, including NVS Flash,
 * network interfaces, and event loop creation.
 *
 * @return 0 if initialization is successful, -1 otherwise.
 */
int8_t wifi_initialize(void);

/**
 * @brief Connect to a Wi-Fi network.
 *
 * This function connects the ESP32 device to a specified Wi-Fi network.
 * It registers event handlers for connection status and IP acquisition.
 *
 * @return 0 if connection is successful, -1 otherwise.
 */
int8_t wifi_connect(void);

/**
 * @brief Disconnect from the current Wi-Fi network.
 *
 * This function disconnects the ESP32 device from the current Wi-Fi network.
 * It also unregisters event handlers and stops Wi-Fi operations.
 *
 * @return 0 if disconnection is successful, -1 otherwise.
 */
int8_t wifi_disconnect(void);

/**
 * @brief Deinitialize the Wi-Fi subsystem.
 *
 * This function deinitializes the Wi-Fi subsystem, including shutting down
 * Wi-Fi operations, clearing default Wi-Fi drivers, and destroying network
 * interfaces.
 *
 * @return 0 if deinitialization is successful, -1 otherwise.
 */
int8_t wifi_deinitialize(void);

int32_t get_last_wifi_event_id();

/**
 * @brief Get the default MAC address of the ESP32.
 *
 * This function retrieves the default MAC address programmed in the ESP32's
 * eFuses.
 *
 * @param[out] mac Pointer to store the retrieved MAC address.
 * @return 0 if MAC address retrieval is successful, -1 otherwise.
 */
int8_t mac_get_default(uint8_t *mac);

/**
 * @brief Abort the system with an error message.
 *
 * This function logs an error message and restarts the ESP32.
 *
 * @param msg Error message to log before restarting.
 */
void wireless_system_abort(const char *msg);

#endif /* WLS_DRV_H_ */