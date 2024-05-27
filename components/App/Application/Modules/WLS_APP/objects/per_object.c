/**
 * Generated by anjay_codegen.py on 2020-03-19 14:13:34
 *
 * LwM2M Object: Time
 * ID: 3333, URN: urn:oma:lwm2m:ext:3333, Optional, Multiple
 *
 * This IPSO object is used to report the current percentage in seconds since
 * January 1, 1970 UTC. There is also a fractional percentage counter that has
 * a range of less than one second.
 */

#include <assert.h>
#include <stdbool.h>

#include <anjay/anjay.h>
#include <avsystem/commons/avs_defs.h>
#include <avsystem/commons/avs_list.h>
#include <avsystem/commons/avs_memory.h>

#include "objects.h"
#include "OMA_id.h"

typedef struct percentage_instance_struct {
    anjay_iid_t iid;
    char application_type[64];
    float value;
    char unit[64];
} percentage_instance_t;


typedef struct percentage_object_struct {
    const anjay_dm_object_def_t *def;
    AVS_LIST(percentage_instance_t) instances;
} percentage_object_t;

static inline percentage_object_t *
get_obj(const anjay_dm_object_def_t *const *obj_ptr) {
    assert(obj_ptr);
    return AVS_CONTAINER_OF(obj_ptr, percentage_object_t, def);
}

static percentage_instance_t *find_instance(const percentage_object_t *obj,
                                      anjay_iid_t iid) {
    AVS_LIST(percentage_instance_t) it;
    AVS_LIST_FOREACH(it, obj->instances) {
        if (it->iid == iid) {
            return it;
        } else if (it->iid > iid) {
            break;
        }
    }

    return NULL;
}

static int list_instances(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *obj_ptr,
                          anjay_dm_list_ctx_t *ctx) {
    (void) anjay;

    AVS_LIST(percentage_instance_t) it;
    AVS_LIST_FOREACH(it, get_obj(obj_ptr)->instances) {
        anjay_dm_emit(ctx, it->iid);
    }

    return 0;
}

static int init_instance(percentage_instance_t *inst, anjay_iid_t iid) {
    assert(iid != ANJAY_ID_INVALID);

    inst->iid = iid;
    inst->application_type[0] = '\0';

    return 0;
}

static void release_instance(percentage_instance_t *inst) {
    (void) inst;
}

static percentage_instance_t *add_instance(percentage_object_t *obj, anjay_iid_t iid) {
    assert(find_instance(obj, iid) == NULL);

    AVS_LIST(percentage_instance_t) created = AVS_LIST_NEW_ELEMENT(percentage_instance_t);
    if (!created) {
        return NULL;
    }

    int result = init_instance(created, iid);
    if (result) {
        AVS_LIST_CLEAR(&created);
        return NULL;
    }

    AVS_LIST(percentage_instance_t) *ptr;
    AVS_LIST_FOREACH_PTR(ptr, &obj->instances) {
        if ((*ptr)->iid > created->iid) {
            break;
        }
    }

    AVS_LIST_INSERT(ptr, created);
    return created;
}

static int instance_create(anjay_t *anjay,
                           const anjay_dm_object_def_t *const *obj_ptr,
                           anjay_iid_t iid) {
    (void) anjay;
    percentage_object_t *obj = get_obj(obj_ptr);

    return add_instance(obj, iid) ? 0 : ANJAY_ERR_INTERNAL;
}

static int instance_remove(anjay_t *anjay,
                           const anjay_dm_object_def_t *const *obj_ptr,
                           anjay_iid_t iid) {
    (void) anjay;
    percentage_object_t *obj = get_obj(obj_ptr);

    AVS_LIST(percentage_instance_t) *it;
    AVS_LIST_FOREACH_PTR(it, &obj->instances) {
        if ((*it)->iid == iid) {
            release_instance(*it);
            AVS_LIST_DELETE(it);
            return 0;
        } else if ((*it)->iid > iid) {
            break;
        }
    }

    assert(0);
    return ANJAY_ERR_NOT_FOUND;
}

static int instance_reset(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *obj_ptr,
                          anjay_iid_t iid) {
    (void) anjay;

    percentage_object_t *obj = get_obj(obj_ptr);
    percentage_instance_t *inst = find_instance(obj, iid);
    assert(inst);

    inst->application_type[0] = '\0';

    return 0;
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

    percentage_object_t *obj = get_obj(obj_ptr);
    percentage_instance_t *inst = find_instance(obj, iid);
    assert(inst);

    switch (rid) {
    case RID_SENSOR_VALUE: {
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_float(ctx, inst->value);
    }

    case RID_APPLICATION_TYPE:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, inst->application_type);

    case RID_SENSOR_UNITS:
        assert(riid == ANJAY_ID_INVALID);
        return anjay_ret_string(ctx, inst->unit);

    default:
        return ANJAY_ERR_METHOD_NOT_ALLOWED;
    }
}

static const anjay_dm_object_def_t OBJ_DEF = {
    .oid = OID_PERCENTAGE,
    .handlers = {
        .list_instances = list_instances,
        .instance_create = instance_create,
        .instance_remove = instance_remove,
        .instance_reset = instance_reset,

        .list_resources = list_resources,
        .resource_read = resource_read,
    }
};

const anjay_dm_object_def_t **percentage_object_create(void) {
    percentage_object_t *obj = (percentage_object_t *) avs_calloc(1, sizeof(percentage_object_t));
    if (!obj) {
        return NULL;
    }
    obj->def = &OBJ_DEF;
    char application_names[3][64] = {"Light percentage",
                                     "Direct sunlight percentage",
                                     "Soil moisture percentage",
                                    };

    for(int i=0;i<MAX_PERCENTAGE_INTANCES;i++)
    {
        percentage_instance_t *inst = add_instance(obj, i);

        if (inst) {
            strcpy(inst->application_type, application_names[i]);
            strcpy(inst->unit, "%");
        } else {
            avs_free(obj);
            return NULL;
        }
    }

    return &obj->def;
}

void percentage_object_value_update(float *percentage_data,const anjay_dm_object_def_t *const *def)
{
    percentage_object_t *obj = get_obj(def);

    AVS_LIST(percentage_instance_t) it;
    if(percentage_data != NULL)
    {
        AVS_LIST_FOREACH(it, obj->instances) {
            it->value = percentage_data[it->iid];
        }
    }
}

void percentage_object_release(const anjay_dm_object_def_t **def) 
{
    if (def) {
        percentage_object_t *obj = get_obj(def);
        AVS_LIST_CLEAR(&obj->instances) {
            release_instance(obj->instances);
        }

        avs_free(obj);
    }
}


void percentage_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def) 
{
    if (!anjay || !def) {
        return;
    }
    percentage_object_t *obj = get_obj(def);

    AVS_LIST(percentage_instance_t) it;
    AVS_LIST_FOREACH(it, obj->instances) 
    {
        anjay_notify_changed(anjay, obj->def->oid, it->iid, RID_SENSOR_VALUE);
    }
}
