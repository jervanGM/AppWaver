#include "acc_it_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SAccItMsg_t _acc_it_msg = {0};

void set_task_acc_it_info(SAccItTaskInfo_t task_info)
{
    mutex_lock(ACC_IT_M_ID);
        memcpy(&_acc_it_msg._task_info, &task_info, sizeof(SAccItTaskInfo_t));
    mutex_unlock(ACC_IT_M_ID);
}

void set_task_acc_it_status(EAccItTaskStatus_t status)
{
    mutex_lock(ACC_IT_M_ID);
        _acc_it_msg._task_info.status = status;
    mutex_unlock(ACC_IT_M_ID);
}

void acc_it_controller_send(EIntCmd_t int_cmd,STime_t it_moment)
{
    mutex_lock(ACC_IT_M_ID);
        memcpy(&_acc_it_msg._int_cmd, &int_cmd, sizeof(EIntCmd_t));
        memcpy(&_acc_it_msg._it_moment, &it_moment, sizeof(STime_t));
    mutex_unlock(ACC_IT_M_ID);
}


void acc_it_controller_read(SAccItMsg_t *msg)
{
    mutex_lock(ACC_IT_M_ID);
        memcpy(msg, &_acc_it_msg, sizeof(SAccItMsg_t));
    mutex_unlock(ACC_IT_M_ID);
}