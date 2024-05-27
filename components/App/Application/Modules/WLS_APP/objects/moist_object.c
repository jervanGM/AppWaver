#include <assert.h>
#include <stdbool.h>

#include <anjay/anjay.h>
#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_list.h>
#include <avsystem/commons/avs_memory.h>

#include "objects.h"
#include "OMA_id.h"

typedef struct air_moist_object_struct {
    const anjay_dm_object_def_t *def;
    char application_type[64];
    float value;
    char unit[64];
} air_moist_object_t;

static inline air_moist_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, air_moist_object_t, def);
}

static int list_resources(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *obj_ptr,
                          anjay_iid_t iid,
                          anjay_dm_resource_list_ctx_t *ctx) {
    (void) anjay;
    (void) obj_ptr;
    (void) iid;

    anjay_dm_emit_res(ctx, RID_SENSOR_VALUE, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_SENSOR_UNITS, ANJAY_DM_RES_R,
                      ANJAY_DM_RES_PRESENT);
    anjay_dm_emit_res(ctx, RID_APPLICATION_TYPE, ANJAY_DM_RES_R,
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

    air_moist_object_t *obj = get_obj(obj_ptr);
    assert(obj);

    switch (rid) {
    case RID_SENSOR_VALUE: {
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_float(ctx, obj->value);
    }

    case RID_APPLICATION_TYPE:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, obj->application_type);

    case RID_SENSOR_UNITS:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, obj->unit);

    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJ_DEF = {
    .oid = OID_HUMIDITY,
    .handlers = {
        .list_instances = anjay_dm_list_instances_SINGLE,
        .list_resources = list_resources,
        .resource_read = resource_read,
    }
};

const anjay_dm_object_def_t **air_moist_object_create(void) {
    air_moist_object_t *obj = (air_moist_object_t *) avs_calloc(1, sizeof(air_moist_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = &OBJ_DEF;

    strcpy(obj->application_type, "Air moisture sensor");
    strcpy(obj->unit, "%");
    

    return &obj->def;
}

void air_moist_object_value_update(float air_moist_data,const anjay_dm_object_def_t *const *def)
{
    air_moist_object_t *obj = get_obj(def);
    obj->value = air_moist_data;
}

void air_moist_object_release(const anjay_dm_object_def_t **def) 
{
    if (def) {
        air_moist_object_t *obj = get_obj(def);
        avs_free(obj);
    }
}

void air_moist_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def) 
{
    if (!anjay || !def) {
        return;
    }

    air_moist_object_t *obj = get_obj(def);
    (void) anjay_notify_changed(anjay, obj->def->oid, OBJ_IID,
                                    RID_SENSOR_VALUE);
}