#include <assert.h>
#include <stdbool.h>

#include <anjay/anjay.h>
#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_list.h>
#include "safe_trace.h"
#include <avsystem/commons/avs_memory.h>

#include "objects.h"
#include "OMA_id.h"



typedef struct accelerometer_object_struct {
    const anjay_dm_object_def_t *def;

    char units[64];
    float x_value;
    float y_value;
    float z_value;
} accelerometer_object_t;

static inline accelerometer_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, accelerometer_object_t, def);
}

static int accelerometer_list_resources(anjay_t *anjay,
                               const anjay_dm_object_def_t *const *obj_ptr,
                               anjay_iid_t iid,
                               anjay_dm_resource_list_ctx_t *ctx) {
    (void) anjay;   // unused
    (void) obj_ptr; // unused
    (void) iid;     // unused

    anjay_dm_emit_res(ctx, RID_SENSOR_UNITS, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_X_VALUE, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_Y_VALUE, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_Z_VALUE, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);

    return 0;
}

static int accelerometer_resource_read(anjay_t *anjay,
                              const anjay_dm_object_def_t *const *obj_ptr,
                              anjay_iid_t iid,
                              anjay_rid_t rid,
                              anjay_riid_t riid,
                              anjay_output_ctx_t *ctx) {
    // These arguments may seem superfluous now, but they will come in handy
    // while defining more complex objects
    (void) anjay;   // unused

    accelerometer_object_t *obj = get_obj(obj_ptr);
    assert(obj);

    switch (rid) {
    case RID_X_VALUE:
        return anjay_ret_float(ctx, obj->x_value);
    case RID_Y_VALUE:
        return anjay_ret_float(ctx, obj->y_value);
    case RID_Z_VALUE:
        return anjay_ret_float(ctx, obj->z_value);
    case RID_SENSOR_UNITS:
        return anjay_ret_string(ctx, obj->units);
    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJECT_DEF = {
    .oid = OID_ACCELERATOR,
    .handlers = {
        .list_instances = anjay_dm_list_instances_SINGLE,
        .list_resources = accelerometer_list_resources,
        .resource_read = accelerometer_resource_read
    }
};

static const anjay_dm_object_def_t *OBJ_DEF_PTR = &OBJECT_DEF;

const anjay_dm_object_def_t **accelerometer_data_object_create(void) {
    accelerometer_object_t *obj =
            (accelerometer_object_t *) avs_calloc(1,sizeof(accelerometer_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = OBJ_DEF_PTR;

    strcpy(obj->units, "m/s^2");
    obj->x_value = 0.0;
    obj->y_value = 0.0;
    obj->z_value = 0.0;

    return &obj->def;
}

void accelerometer_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def) 
{
    if (!anjay || !def) {
        return;
    }

    accelerometer_object_t *obj = get_obj(def);
    (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_X_VALUE);
    (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_Y_VALUE);
    (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_Z_VALUE);
}

void accelerometer_object_release(const anjay_dm_object_def_t **def) {

}

void accelerometer_object_value_update(float x, float y, float z,const anjay_dm_object_def_t *const *def)
{
    accelerometer_object_t *obj = get_obj(def);
    obj->x_value = x;
    obj->y_value = y;
    obj->z_value = z;
}

void accelerometer_object_send(anjay_send_batch_builder_t *builder,anjay_t *anjay, const anjay_dm_object_def_t **def) {
    if (!anjay || !def || !builder) {
        return;
    }
    accelerometer_object_t *obj = get_obj(def);

    // Add current values of resources from Time Object.
    if (anjay_send_batch_data_add_current(builder, anjay, obj->def->oid, OBJ_IID, RID_X_VALUE) &&
        anjay_send_batch_data_add_current(builder, anjay, obj->def->oid, OBJ_IID, RID_Y_VALUE) &&
        anjay_send_batch_data_add_current(builder, anjay, obj->def->oid, OBJ_IID, RID_Z_VALUE)) 
    {
        anjay_send_batch_builder_cleanup(&builder);
        TRACE_ERROR("Failed to add batch data");
        return;
    }

}