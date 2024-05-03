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
#include <stdbool.h>

#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_memory.h>

#include <anjay/anjay.h>

#include "wls_port.h"

#include "../utilities/default_config.h"
#include "../utilities/utils.h"
#include "objects.h"
#include "OMA_id.h"

#define SUPPORTED_BINDING_MODES "UQ"

typedef struct device_object_struct {
    const anjay_dm_object_def_t *def;

    device_id_t serial_number;
    bool do_reboot;
} device_object_t;

static inline device_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, device_object_t, def);
}

static int list_resources(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *obj_ptr,
                          anjay_iid_t iid,
                          anjay_dm_resource_list_ctx_t *ctx) {
    (void) anjay;
    (void) obj_ptr;
    (void) iid;

    anjay_dm_emit_res(ctx, RID_MANUFACTURER, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_MODEL_NUMBER, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_SERIAL_NUMBER, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_FIRMWARE_VERSION, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_REBOOT, ANJAY_DM_RES_E, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_ERROR_CODE, ANJAY_DM_RES_RM,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_SUPPORTED_BINDING_AND_MODES, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_SOFTWARE_VERSION, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    return 0;
}

static int resource_read(anjay_t *anjay,
                         const anjay_dm_object_def_t *const *obj_ptr,
                         anjay_iid_t iid,
                         anjay_rid_t rid,
                         anjay_riid_t riid,
                         anjay_output_ctx_t *ctx) {
    (void) anjay;

    device_object_t *obj = get_obj(obj_ptr);
    assert(obj);
    assert(iid == 0);

    switch (rid) {
    case RID_MANUFACTURER:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, CONFIG_ANJAY_CLIENT_DEVICE_MANUFACTURER);

    case RID_MODEL_NUMBER:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, CONFIG_ANJAY_CLIENT_MODEL_NUMBER);

    case RID_SERIAL_NUMBER:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, obj->serial_number.value);

    case RID_FIRMWARE_VERSION:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, CLIENT_VERSION);

    case RID_ERROR_CODE:
        assert(riid == 0);
        return anjay_ret_i32(ctx, 0);

    case RID_SUPPORTED_BINDING_AND_MODES:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, SUPPORTED_BINDING_MODES);

    case RID_SOFTWARE_VERSION:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, anjay_get_version());

    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static int resource_write(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *obj_ptr,
                          anjay_iid_t iid,
                          anjay_rid_t rid,
                          anjay_riid_t riid,
                          anjay_input_ctx_t *ctx) {
    (void) anjay;
    (void) obj_ptr;

    assert(iid == 0);

    return ANJAY_ERR_METHOD_NOT_ALLOWED;
}

static int resource_execute(anjay_t *anjay,
                            const anjay_dm_object_def_t *const *obj_ptr,
                            anjay_iid_t iid,
                            anjay_rid_t rid,
                            anjay_execute_ctx_t *arg_ctx) {
    (void) arg_ctx;

    device_object_t *obj = get_obj(obj_ptr);
    assert(obj);
    assert(iid == 0);

    switch (rid) {
    case RID_REBOOT:
        obj->do_reboot = true;
        return 0;

    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static int list_resource_instances(anjay_t *anjay,
                                   const anjay_dm_object_def_t *const *obj_ptr,
                                   anjay_iid_t iid,
                                   anjay_rid_t rid,
                                   anjay_dm_list_ctx_t *ctx) {
    (void) anjay;
    (void) obj_ptr;

    assert(iid == 0);

    switch (rid) {
    case RID_ERROR_CODE:
        anjay_dm_emit(ctx, 0);
        return 0;
    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJ_DEF = {
    .oid = 3,
    .handlers = {
        .list_instances = anjay_dm_list_instances_SINGLE,

        .list_resources = list_resources,
        .resource_read = resource_read,
        .resource_write = resource_write,
        .resource_execute = resource_execute,
        .list_resource_instances = list_resource_instances,

        .transaction_begin = anjay_dm_transaction_NOOP,
        .transaction_validate = anjay_dm_transaction_NOOP,
        .transaction_commit = anjay_dm_transaction_NOOP,
        .transaction_rollback = anjay_dm_transaction_NOOP
    }
};

const anjay_dm_object_def_t **device_object_create(void) {
    device_object_t *obj =
            (device_object_t *) avs_calloc(1, sizeof(device_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = &OBJ_DEF;

    if (get_device_id(&obj->serial_number)) {
        obj->serial_number.value[0] = '\0';
    }

    return &obj->def;
}

void device_object_release(const anjay_dm_object_def_t **def) {
    if (def) {
        device_object_t *obj = get_obj(def);
        avs_free(obj);
    }
}

void device_object_update(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *def) {
    if (!anjay || !def) {
        return;
    }

    device_object_t *obj = get_obj(def);
    const IWlsPort *port = hal_wls_get_port();
    if (obj->do_reboot) {
        // This is a bit harsh, but this is the nicest way to ensure
        // the reboot using the public ESP32 API
        port->system_abort("Rebooting ...");
    }
}
