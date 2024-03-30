#include "ind_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SIndCtrlMsg_t _ind_msg = {0};
static SCtrlIndMsg_t _ctrl_msg = {0};

void set_task_indicator_info(SIndTaskInfo_t task_info)
{
    mutex_lock(IND_CTRL_M_ID);
        memcpy(&_ind_msg._task_info, &task_info, sizeof(SIndTaskInfo_t));
    mutex_unlock(IND_CTRL_M_ID);
}

void set_task_indicator_status(EIndTaskStatus_t status)
{
    mutex_lock(IND_CTRL_M_ID);
        _ind_msg._task_info.status = status;
    mutex_unlock(IND_CTRL_M_ID);
}

void ind_ctrl_read(SIndCtrlMsg_t *msg)
{
    mutex_lock(IND_CTRL_M_ID);
        memcpy(msg, &_ind_msg, sizeof(SIndCtrlMsg_t));
    mutex_unlock(IND_CTRL_M_ID);
}

void ctrl_ind_send(EIndId_t ind_id, EIndSts_t ind_state)
{
    mutex_lock(CTRL_IND_M_ID);
        memcpy(&_ctrl_msg._ind_id, &ind_id, sizeof(EIndId_t));
        memcpy(&_ctrl_msg._ind_state, &ind_state, sizeof(EIndSts_t));
    mutex_unlock(CTRL_IND_M_ID);
}

void ctrl_ind_read(SCtrlIndMsg_t *msg)
{
    mutex_lock(CTRL_IND_M_ID);
        memcpy(msg, &_ctrl_msg, sizeof(SCtrlIndMsg_t));
    mutex_unlock(CTRL_IND_M_ID);
}