/*
 * Copyright 2021-2024 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FIRMWARE_UPDATE_H
#define FIRMWARE_UPDATE_H

#include <stdbool.h>

#include <anjay/anjay.h>

/**
 * @brief Function to install firmware update module.
 *
 * @param anjay Anjay object instance.
 * @return 0 on success, error code on failure.
 *
 * Installs firmware update module for the given Anjay instance.
 * Logs an error if OTA port is not properly configured or if already installed.
 */
int fw_update_install(anjay_t *anjay);

/**
 * @brief Checks if firmware update is requested.
 *
 * @return true if firmware update is requested, false otherwise.
 *
 * Checks if firmware update has been requested by setting a flag.
 */
bool fw_update_requested(void);

/**
 * @brief Reboots to perform a firmware upgrade.
 *
 * Initiates a system reboot to finalize firmware upgrade.
 * Logs an error if OTA port is not properly configured.
 */
void fw_update_reboot(void);

#endif // FIRMWARE_UPDATE_H
