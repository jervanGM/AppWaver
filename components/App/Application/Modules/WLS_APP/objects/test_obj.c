#include <assert.h>
#include <stdbool.h>

#include <anjay/anjay.h>
#include <anjay/lwm2m_send.h>
#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_list.h>
#include "safe_trace.h"
#include <avsystem/commons/avs_memory.h>

#include "objects.h"

#define RID_OBJECT_STRING 5500

#define RID_DIGITAL_TIME 5501

#define OBJ_IID 0

typedef struct custom_object_struct {
    const anjay_dm_object_def_t *def;

    char object_name[64];
    int64_t time;
    int64_t prev_time;
} custom_object_t;

static inline custom_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, custom_object_t, def);
}

static int test_list_resources(anjay_t *anjay,
                               const anjay_dm_object_def_t *const *obj_ptr,
                               anjay_iid_t iid,
                               anjay_dm_resource_list_ctx_t *ctx) {
    (void) anjay;   // unused
    (void) obj_ptr; // unused
    (void) iid;     // unused

    anjay_dm_emit_res(ctx, RID_OBJECT_STRING, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_DIGITAL_TIME, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    return 0;
}

static int test_resource_read(anjay_t *anjay,
                              const anjay_dm_object_def_t *const *obj_ptr,
                              anjay_iid_t iid,
                              anjay_rid_t rid,
                              anjay_riid_t riid,
                              anjay_output_ctx_t *ctx) {
    // These arguments may seem superfluous now, but they will come in handy
    // while defining more complex objects
    (void) anjay;   // unused

    custom_object_t *obj = get_obj(obj_ptr);
    assert(obj);

    switch (rid) {
    case RID_OBJECT_STRING:
        return anjay_ret_string(ctx, obj->object_name);
    case RID_DIGITAL_TIME:
        return anjay_ret_i64(ctx, obj->time);
    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJECT_DEF = {
    .oid = 1234,
    .handlers = {
        .list_instances = anjay_dm_list_instances_SINGLE,
        .list_resources = test_list_resources,
        .resource_read = test_resource_read

    }
};

static const anjay_dm_object_def_t *OBJ_DEF_PTR = &OBJECT_DEF;

const anjay_dm_object_def_t **custom_object_create(void) {
    custom_object_t *obj =
            (custom_object_t *) avs_calloc(1,sizeof(custom_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = OBJ_DEF_PTR;

    strcpy(obj->object_name, "Test Object");
    obj->time = 0;
    obj->prev_time = 0;

    return &obj->def;
}

void custom_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def) 
{
    if (!anjay || !def) {
        return;
    }

    custom_object_t *obj = get_obj(def);
    obj->time = avs_time_real_now().since_real_epoch.seconds;
    if (obj->time != obj->prev_time) {
        (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_DIGITAL_TIME);
        obj->prev_time = obj->time;
    }
}

void custom_object_release(const anjay_dm_object_def_t **def) {

}

static void send_finished_handler(anjay_t *anjay,
                                anjay_ssid_t ssid,
                                const anjay_send_batch_t *batch,
                                int result,
                                void *data) {
    (void) anjay;
    (void) ssid;
    (void) batch;
    (void) data;

    if (result != ANJAY_SEND_SUCCESS) {
        TRACE_ERROR("Send failed, result: %d", result);
    } else {
        TRACE_INFO("Send successful");
    }
}

void custom_object_send(anjay_t *anjay, const anjay_dm_object_def_t **def) {
    if (!anjay || !def) {
        return;
    }
    custom_object_t *obj = get_obj(def);
    const anjay_ssid_t server_ssid = 1;

    // Allocate new batch builder.
    anjay_send_batch_builder_t *builder = anjay_send_batch_builder_new();

    if (!builder) {
        TRACE_ERROR("Failed to allocate batch builder");
        return;
    }

    int res = 0;

    // Add current values of resources from Time Object.
    if (anjay_send_batch_data_add_current(builder, anjay, obj->def->oid,
                                            OBJ_IID, RID_DIGITAL_TIME)) 
    {
        anjay_send_batch_builder_cleanup(&builder);
        TRACE_ERROR("Failed to add batch data, result:",TO_STRING(res));
        return;
    }

    // After adding all values, compile our batch for sending.
    anjay_send_batch_t *batch = anjay_send_batch_builder_compile(&builder);

    if (!batch) {
        anjay_send_batch_builder_cleanup(&builder);
        TRACE_ERROR("Batch compile failed");
        return;
    }

    // Schedule our send to be run on next `anjay_sched_run()` call.
    res = anjay_send(anjay, server_ssid, batch, send_finished_handler, NULL);

    if (res) {
        TRACE_ERROR("Failed to send, result:", TO_STRING(res));
    }

    // After scheduling, we can release our batch.
    anjay_send_batch_release(&batch);
}
