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
    SPPlantData_t plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    STime_t system_time)
{
    SCtrlMemMsg_t temp_msg;

    // Rellenar el mensaje temporal
    temp_msg._alarm = alarm;
    temp_msg._status = status;
    temp_msg._plant_signal = plant_signal;
    temp_msg._env_data = env_data;
    temp_msg._power_data = power_data;
    temp_msg._axis_buff = axis_buff;
    temp_msg._current_mode = current_mode;
    temp_msg._previous_mode = previous_mode;
    temp_msg._system_time = system_time;

    // Bloquear el mutex, copiar todo el mensaje y desbloquear
    mutex_lock(CTRL_MEM_M_ID);
    memcpy(&_ctrl_msg, &temp_msg, sizeof(SCtrlMemMsg_t));
    mutex_unlock(CTRL_MEM_M_ID);
}

void ctrl_mem_read(SCtrlMemMsg_t *msg)
{
    mutex_lock(CTRL_MEM_M_ID);
        memcpy(msg, &_ctrl_msg, sizeof(SCtrlMemMsg_t));
    mutex_unlock(CTRL_MEM_M_ID);
}