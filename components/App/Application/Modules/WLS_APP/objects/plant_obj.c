#include <assert.h>
#include <stdbool.h>

#include <anjay/anjay.h>
#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_list.h>
#include "safe_trace.h"
#include <avsystem/commons/avs_memory.h>

#include "objects.h"
#include "OMA_id.h"



typedef struct plant_object_struct {
    const anjay_dm_object_def_t *def;

    char object_name[64];
    uint32_t plant_value;
} plant_object_t;

static inline plant_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, plant_object_t, def);
}

static int plant_list_resources(anjay_t *anjay,
                               const anjay_dm_object_def_t *const *obj_ptr,
                               anjay_iid_t iid,
                               anjay_dm_resource_list_ctx_t *ctx) {
    (void) anjay;   // unused
    (void) obj_ptr; // unused
    (void) iid;     // unused

    anjay_dm_emit_res(ctx, RID_ANALOG_OUTPUT_CURRENT_VALUE, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_APPLICATION_TYPE, ANJAY_DM_RES_R, ANJAY_DM_RES_PRESENT);

    return 0;
}

static int plant_resource_read(anjay_t *anjay,
                              const anjay_dm_object_def_t *const *obj_ptr,
                              anjay_iid_t iid,
                              anjay_rid_t rid,
                              anjay_riid_t riid,
                              anjay_output_ctx_t *ctx) {
    // These arguments may seem superfluous now, but they will come in handy
    // while defining more complex objects
    (void) anjay;   // unused

    plant_object_t *obj = get_obj(obj_ptr);
    assert(obj);

    switch (rid) {
    case RID_ANALOG_OUTPUT_CURRENT_VALUE:
        return anjay_ret_u32(ctx, obj->plant_value);
    case RID_APPLICATION_TYPE:
        return anjay_ret_string(ctx, "PLANT INFO");
    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJECT_DEF = {
    .oid = OID_ANALOG_OUTPUT,
    .handlers = {
        .list_instances = anjay_dm_list_instances_SINGLE,
        .list_resources = plant_list_resources,
        .resource_read = plant_resource_read
    }
};

static const anjay_dm_object_def_t *OBJ_DEF_PTR = &OBJECT_DEF;

const anjay_dm_object_def_t **plant_data_object_create(void) {
    plant_object_t *obj =
            (plant_object_t *) avs_calloc(1,sizeof(plant_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = OBJ_DEF_PTR;

    strcpy(obj->object_name, "Plant analog data");
    obj->plant_value = 0;

    return &obj->def;
}

void plant_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def) 
{
    if (!anjay || !def) {
        return;
    }

    plant_object_t *obj = get_obj(def);
    (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_ANALOG_OUTPUT_CURRENT_VALUE);
}

void plant_object_release(const anjay_dm_object_def_t **def) {

}

void plant_object_value_update(uint32_t plant_data,const anjay_dm_object_def_t *const *def)
{
    plant_object_t *obj = get_obj(def);
    obj->plant_value = plant_data;
}

void plant_object_send(anjay_send_batch_builder_t *builder,anjay_t *anjay, const anjay_dm_object_def_t **def) {
    if (!anjay || !def || !builder) {
        return;
    }
    plant_object_t *obj = get_obj(def);

    // Add current values of resources from Time Object.
    if (anjay_send_batch_data_add_current(builder, anjay, obj->def->oid,
                                            OBJ_IID, RID_ANALOG_OUTPUT_CURRENT_VALUE)) 
    {
        anjay_send_batch_builder_cleanup(&builder);
        TRACE_ERROR("Failed to add batch data");
        return;
    }

}