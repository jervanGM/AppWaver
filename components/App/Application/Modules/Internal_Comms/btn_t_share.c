#include "btn_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SBtnMsg_t _btn_msg = {0};

void set_task_button_info(SBtnTaskInfo_t task_info)
{
    mutex_lock(BTN_M_ID);
        memcpy(&_btn_msg._task_info, &task_info, sizeof(SBtnTaskInfo_t));
    mutex_unlock(BTN_M_ID);
}

void set_task_button_status(EBtnTaskStatus_t status)
{
    mutex_lock(BTN_M_ID);
        _btn_msg._task_info.status = status;
    mutex_unlock(BTN_M_ID);
}

void button_controller_send(EBtnCmd_t btn_cmd)
{
    mutex_lock(BTN_M_ID);
        memcpy(&_btn_msg._btn_cmd, &btn_cmd, sizeof(EBtnCmd_t));
    mutex_unlock(BTN_M_ID);
}


void button_controller_read(SBtnMsg_t *msg)
{
    mutex_lock(BTN_M_ID);
        memcpy(msg, &_btn_msg, sizeof(SBtnMsg_t));
    mutex_unlock(BTN_M_ID);
}