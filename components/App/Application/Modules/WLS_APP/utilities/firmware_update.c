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

#include <anjay/anjay.h>
#include <anjay/fw_update.h>

#include "firmware_update.h"
#include "ota_port.h"
#include "sdkconfig.h"

static struct {
    anjay_t *anjay;
    atomic_bool update_requested;
} fw_state;

static int fw_stream_open(void *user_ptr,
                          const char *package_uri,
                          const struct anjay_etag *package_etag) {
    (void) user_ptr;
    (void) package_uri;
    (void) package_etag;

    const IOtaPort *port = hal_ota_get_port();
    return port->init();
}

static int fw_stream_write(void *user_ptr, const void *data, size_t length) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    int8_t result = port->write(data,length);
    if(result)
    {
        return ANJAY_FW_UPDATE_ERR_UNSUPPORTED_PACKAGE_TYPE;
    }
    return 0;
}

static int fw_stream_finish(void *user_ptr) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    int8_t result = port->finish();
    if(result)
    {
        return ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE;
    }
    return 0;
}

static void fw_reset(void *user_ptr) {
    (void) user_ptr;
    const IOtaPort *port = hal_ota_get_port();
    port->reset();
}

static int fw_perform_upgrade(void *user_ptr) {
    (void) user_ptr;

    const IOtaPort *port = hal_ota_get_port();
    int result = port->upgrade();

    if (result) 
    {
        return ANJAY_FW_UPDATE_ERR_INTEGRITY_FAILURE;
    }

    if (anjay_event_loop_interrupt(fw_state.anjay)) {
        return -1;
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

    if (!port->update_install()) {
        state.result = ANJAY_FW_UPDATE_INITIAL_SUCCESS;
    }

    // make sure this module is installed for single Anjay instance only
    assert(!fw_state.anjay);
    fw_state.anjay = anjay;

    return anjay_fw_update_install(anjay, &HANDLERS, NULL, &state);
}

bool fw_update_requested(void) {
    return atomic_load(&fw_state.update_requested);
}

void fw_update_reboot(void) {
    TRACE_INFO("Rebooting to perform a firmware upgrade...");
    const IOtaPort *port = hal_ota_get_port();
    port->update_reboot();
}
