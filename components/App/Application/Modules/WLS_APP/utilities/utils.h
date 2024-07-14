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

#pragma once

typedef struct {
    // 48 bits as hex + NULL-byte
    char value[13];
} device_id_t;

/**
 * @brief Retrieves the device ID based on the wireless MAC address.
 *
 * @param[out] out_id Pointer to a structure where the device ID will be stored.
 * @return 0 on success, non-zero error code on failure.
 *
 * Retrieves the device ID using the wireless MAC address obtained from the
 * wireless port interface. The device ID is hex-encoded and stored in the
 * provided output structure.
 *
 * If the wireless port is not properly configured, logs an error and sets
 * an appropriate error code.
 */
int get_device_id(device_id_t *out_id);
