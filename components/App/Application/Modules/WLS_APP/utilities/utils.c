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

#include <stdint.h>
#include <string.h>

#include "wls_port.h"
#include "i_wireless_data.h"
#include <avsystem/commons/avs_utils.h>
#include "safe_memory.h"
#include "safe_trace.h"

#include "utils.h"

int get_device_id(device_id_t *out_id) {
    memset(out_id->value, 0, sizeof(out_id->value));
    const IWlsPort *port = hal_wls_get_port();
    uint8_t mac[6];
    if (port != NULL)
    {
        port->get_mac(mac);
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(WIRELESS_ERROR_SLOT, HAL_WLS_CONFIG_ERROR);
        TRACE_ERROR("Wireless communication HAL port has not been configured correctly on device id");
    }
    

    return avs_hexlify(out_id->value, sizeof(out_id->value), NULL, mac,
                       sizeof(mac));
}
