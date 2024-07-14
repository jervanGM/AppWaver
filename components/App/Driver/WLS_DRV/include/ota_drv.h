#ifndef OTA_DRV_H_
#define OTA_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_err.h>
#include <esp_wifi.h>

void ota_update_reboot();

/**
 * @brief Initialize OTA update process.
 * 
 * This function initializes the OTA update process by obtaining the next update partition.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t ota_init();

/**
 * @brief Install OTA update.
 * 
 * This function installs the OTA update and marks the new firmware as valid.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t ota_update_install();

/**
 * @brief Write data to OTA update partition.
 * 
 * This function writes data to the OTA update partition.
 * 
 * @param data Pointer to the data buffer.
 * @param length Length of the data to write.
 * @return 0 if successful, -1 otherwise.
 */
int8_t ota_write(const void *data, size_t length);

/**
 * @brief Upgrade to the OTA updated firmware.
 * 
 * This function sets the boot partition to the updated OTA partition.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t ota_upgrade();

/**
 * @brief Abort the OTA update process.
 * 
 * This function aborts the OTA update process and cleans up resources.
 */
void ota_abort();

/**
 * @brief End the OTA update process.
 * 
 * This function ends the OTA update process and cleans up resources.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t ota_end();

#endif /* OTA_DRV_H_ */