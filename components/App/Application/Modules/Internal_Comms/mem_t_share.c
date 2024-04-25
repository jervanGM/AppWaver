#include "mem_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SMemCtrlMsg_t _mem_msg = {0};
static SCtrlMemMsg_t _ctrl_msg = {0};


void set_task_ext_mem_info(SMemTaskInfo_t task_info)
{
    mutex_lock(MEM_CTRL_M_ID);
        memcpy(&_mem_msg._task_info, &task_info, sizeof(SMemTaskInfo_t));
    mutex_unlock(MEM_CTRL_M_ID);
}

void set_task_ext_mem_status(EMemTaskStatus_t status)
{
    mutex_lock(MEM_CTRL_M_ID);
        _mem_msg._task_info.status = status;
    mutex_unlock(MEM_CTRL_M_ID);
}

void mem_ctrl_read(SMemCtrlMsg_t *msg)
{
    mutex_lock(MEM_CTRL_M_ID);
        memcpy(msg, &_mem_msg, sizeof(SMemCtrlMsg_t));
    mutex_unlock(MEM_CTRL_M_ID);
}

void ctrl_mem_send(
    SErrorInfo_t alarm,
    SSystemStatus_t status,
    uint32_t *plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t *axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    STime_t start_time,
    STime_t end_time,
    STime_t system_time)
    {
        mutex_lock(CTRL_MEM_M_ID);
            memcpy(&_ctrl_msg._alarm, &alarm, sizeof(SErrorInfo_t));
            memcpy(&_ctrl_msg._status, &status, sizeof(SSystemStatus_t));
            memcpy(_ctrl_msg._plant_signal, plant_signal,DATA_BUFFER_SIZE*sizeof(uint32_t));
            memcpy(&_ctrl_msg._env_data, &env_data, sizeof(SEnvData_t));
            memcpy(&_ctrl_msg._power_data, &power_data, sizeof(SPowerData_t));
            memcpy(_ctrl_msg._axis_buff, axis_buff,DATA_BUFFER_SIZE*sizeof(SAxisData_t));
            memcpy(&_ctrl_msg._current_mode, &current_mode, sizeof(ESysMode_t));
            memcpy(&_ctrl_msg._previous_mode, &previous_mode, sizeof(ESysMode_t));
            memcpy(&_ctrl_msg._start_time, &start_time, sizeof(STime_t));
            memcpy(&_ctrl_msg._end_time, &end_time, sizeof(STime_t));
            memcpy(&_ctrl_msg._system_time, &system_time, sizeof(STime_t));
        mutex_unlock(CTRL_MEM_M_ID);
    }

void ctrl_mem_read(SCtrlMemMsg_t *msg)
{
    mutex_lock(CTRL_MEM_M_ID);
        memcpy(msg, &_ctrl_msg, sizeof(SCtrlMemMsg_t));
    mutex_unlock(CTRL_MEM_M_ID);
}