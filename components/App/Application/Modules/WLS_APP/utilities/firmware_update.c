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

#include <assert.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include "safe_trace.h"
#include "safe_memory.h"

#include <anjay/anjay.h>
#include <anjay/fw_update.h>

#include "firmware_update.h"
#include "i_wireless_data.h"
#include "ota_port.h"
#include "sdkconfig.h"

static struct {
    anjay_t *anjay;
    atomic_bool update_requested;
} fw_state;

/**
 * @brief Handler for opening a firmware update stream.
 *
 * @param user_ptr User pointer (unused).
 * @param package_uri URI of the firmware package.
 * @param package_etag ETag of the firmware package.
 * @return 0 on success, -1 on failure to initialize OTA port.
 *
 * Initializes the OTA port for firmware update stream.
 * Logs an error if OTA port is not properly configured.
 */
static int fw_stream_open(void *user_ptr,
                          const char *package_uri,
                          const struct anjay_etag *package_etag) {
    (void) user_ptr;
    (void) package_uri;
    (void) package_etag;

    const IOtaPort *port = hal_ota_get_port();
    if (port != NULL)
    {
        return port->init();
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on initialization");
    }
    return -1;
}

/**
 * @brief Handler for writing data to a firmware update stream.
 *
 * @param user_ptr User pointer (unused).
 * @param data Pointer to data to write.
 * @param length Length of data to write.
 * @return 0 on success, ANJAY_FW_UPDATE_ERR_UNSUPPORTED_PACKAGE_TYPE if write fails.
 *
 * Writes data to the OTA port for firmware update stream.
 * Logs an error if OTA port is not properly configured.
 */
static int fw_stream_write(void *user_ptr, const void *data, size_t length) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    int8_t result = 0;
    if (port != NULL)
    {
        result = port->write(data,length);
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on stream write");
    }
    
    if(result)
    {
        return ANJAY_FW_UPDATE_ERR_UNSUPPORTED_PACKAGE_TYPE;
    }
    return 0;
}


/**
 * @brief Handler for finishing a firmware update stream.
 *
 * @param user_ptr User pointer (unused).
 * @return 0 on success, ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE if finish fails.
 *
 * Finalizes the OTA port for firmware update stream.
 * Logs an error if OTA port is not properly configured.
 */
static int fw_stream_finish(void *user_ptr) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    int8_t result = 0;
    if (port != NULL)
    {
        result = port->finish();
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on stream finish");
    }
    
    if(result)
    {
        return ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE;
    }
    return 0;
}

/**
 * @brief Handler for resetting after a firmware update.
 *
 * @param user_ptr User pointer (unused).
 *
 * Resets the OTA port after firmware update.
 * Logs an error if OTA port is not properly configured.
 */
static void fw_reset(void *user_ptr) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    if (port != NULL)
    {
        port->reset();
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on reset");
    }
    
}

/**
 * @brief Handler for performing firmware upgrade.
 *
 * @param user_ptr User pointer (unused).
 * @return 0 on success, ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE on upgrade failure.
 *
 * Initiates firmware upgrade using OTA port.
 * Logs an error if OTA port is not properly configured.
 */
static int fw_perform_upgrade(void *user_ptr) {
    (void) user_ptr;
    int result = 0;
    const IOtaPort *port = hal_ota_get_port();
    if (port != NULL)
    {
        result = port->upgrade();
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on upgrade");
    }

    if (result) 
    {
        return ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE;
    }

    atomic_store(&fw_state.update_requested, true);
    return 0;
}

static const anjay_fw_update_handlers_t HANDLERS = {
    .stream_open = fw_stream_open,
    .stream_write = fw_stream_write,
    .stream_finish = fw_stream_finish,
    .reset = fw_reset,
    .perform_upgrade = fw_perform_upgrade,
};

int fw_update_install(anjay_t *anjay) {
    anjay_fw_update_initial_state_t state = { 0 };
    const IOtaPort *port = hal_ota_get_port();
    if (port != NULL)
    {
        if (!port->update_install()) {
            state.result = ANJAY_FW_UPDATE_INITIAL_SUCCESS;
        }
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on install");
    }


    // make sure this module is installed for single Anjay instance only
    if(fw_state.anjay)
    {
        store_error_in_slot(FOTA_ERROR_SLOT,OTA_NOT_CONFIGURED);
        TRACE_ERROR("FOTA anjay instance has not been installed correctly");
    }
    fw_state.anjay = anjay;

    return anjay_fw_update_install(anjay, &HANDLERS, NULL, &state);
}

bool fw_update_requested(void) {
    return atomic_load(&fw_state.update_requested);
}

void fw_update_reboot(void) {
    TRACE_INFO("Rebooting to perform a firmware upgrade...");
    const IOtaPort *port = hal_ota_get_port();
    if (port != NULL)
    {
        port->update_reboot();
    }
    else
    {
        // Log an error if the wireless port is not properly configured
        store_error_in_slot(FOTA_ERROR_SLOT, HAL_OTA_CONFIG_ERROR);
        TRACE_ERROR("FOTA HAL port has not been configured correctly on reboot");
    }
}
