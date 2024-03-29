#include "wireless_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SWlsCtrlSensMsg_t _wls_msg = {0};
static SCtrlWlsSensMsg_t _ctrl_msg = {0};


void set_task_wireless_info(SWlsTaskInfo_t task_info)
{
    mutex_lock(WLS_CTRL_M_ID);
        memcpy(&_wls_msg._task_info, &task_info, sizeof(SWlsTaskInfo_t));
    mutex_unlock(WLS_CTRL_M_ID);
}

void set_task_wireless_status(EWlsTaskStatus_t status)
{
    mutex_lock(WLS_CTRL_M_ID);
        _wls_msg._task_info.status = status;
    mutex_unlock(WLS_CTRL_M_ID);
}

void wireless_controller_send(SWlsCommand_t command)
{
    mutex_lock(WLS_CTRL_M_ID);
        memcpy(&_wls_msg._command, &command, sizeof(SWlsCommand_t));
    mutex_unlock(WLS_CTRL_M_ID);
}

void wireless_controller_read(SWlsCtrlSensMsg_t *msg)
{
    mutex_lock(WLS_CTRL_M_ID);
        memcpy(msg, &_wls_msg, sizeof(SWlsCtrlSensMsg_t));
    mutex_unlock(WLS_CTRL_M_ID);
}

void controller_wireless_send(
    SErrorInfo_t alarm,
    SSystemStatus_t status,
    uint32_t *plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t *axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    STime_t system_time)
    {
        mutex_lock(CTRL_WLS_M_ID);
            memcpy(&_ctrl_msg._alarm, &alarm, sizeof(SErrorInfo_t));
            memcpy(&_ctrl_msg._status, &status, sizeof(SSystemStatus_t));
            memcpy(_ctrl_msg._plant_signal, plant_signal,DATA_BUFFER_SIZE*sizeof(uint32_t));
            memcpy(&_ctrl_msg._env_data, &env_data, sizeof(SEnvData_t));
            memcpy(&_ctrl_msg._power_data, &power_data, sizeof(SPowerData_t));
            memcpy(_ctrl_msg._axis_buff, axis_buff,DATA_BUFFER_SIZE*sizeof(SAxisData_t));
            memcpy(&_ctrl_msg._current_mode, &current_mode, sizeof(ESysMode_t));
            memcpy(&_ctrl_msg._previous_mode, &previous_mode, sizeof(ESysMode_t));
            memcpy(&_ctrl_msg._system_time, &system_time, sizeof(STime_t));
        mutex_unlock(CTRL_WLS_M_ID);
    }

void controller_wireless_read(SCtrlWlsSensMsg_t *msg)
{
    mutex_lock(CTRL_WLS_M_ID);
        memcpy(msg, &_ctrl_msg, sizeof(SCtrlWlsSensMsg_t));
    mutex_unlock(CTRL_WLS_M_ID);
}