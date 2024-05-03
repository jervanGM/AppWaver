#include "srl_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SSerialMsg_t _srl_msg = {0};

void set_task_serial_info(SSrlTaskInfo_t task_info)
{
    mutex_lock(SRL_CTRL_M_ID);
        memcpy(&_srl_msg._task_info, &task_info, sizeof(SSrlTaskInfo_t));
    mutex_unlock(SRL_CTRL_M_ID);
}

void set_task_serial_status(ESrlTaskStatus_t status)
{
    mutex_lock(SRL_CTRL_M_ID);
        _srl_msg._task_info.status = status;
    mutex_unlock(SRL_CTRL_M_ID);
}

void set_serial_connection_status(ESrlConnStatus_t status)
{
    mutex_lock(SRL_CTRL_M_ID);
        _srl_msg._serial_status = status;
    mutex_unlock(SRL_CTRL_M_ID);    
}

void set_serial_command(SSerialCmd_t command)
{
    mutex_lock(SRL_CTRL_M_ID);
        _srl_msg._command = command;
    mutex_unlock(SRL_CTRL_M_ID);       
}

void serial_controller_read(SSerialMsg_t *msg)
{
    mutex_lock(SRL_CTRL_M_ID);
        memcpy(msg, &_srl_msg, sizeof(SSerialMsg_t));
    mutex_unlock(SRL_CTRL_M_ID);
}