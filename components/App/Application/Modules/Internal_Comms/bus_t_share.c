#include "bus_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SBusSensCtrlMsg_t _bus_ctrl_msg = {0};
static SCtrlBusSensMsg_t _ctrl_bus_msg = {0};

void set_task_bus_info(SBusTaskInfo_t task_info)
{
    mutex_lock(BUS_CTRL_M_ID);
        memcpy(&_bus_ctrl_msg._task_info, &task_info, sizeof(SBusTaskInfo_t));
    mutex_unlock(BUS_CTRL_M_ID);
}

void set_task_bus_status(EBusTaskStatus_t status)
{
    mutex_lock(BUS_CTRL_M_ID);
        _bus_ctrl_msg._task_info.status = status;
    mutex_unlock(BUS_CTRL_M_ID);
}

void bus_controller_send(
    SAxisDataBuffer_t axis_buff,
    STemp_t temp_data,
    SMoist_t moist_data,
    SBufTime_t buff_time
)
{
    mutex_lock(BUS_CTRL_M_ID);
        memcpy(&_bus_ctrl_msg._axis_buff, &axis_buff, sizeof(SAxisDataBuffer_t));
        memcpy(&_bus_ctrl_msg._temp_data, &temp_data, sizeof(STemp_t));
        memcpy(&_bus_ctrl_msg._moist_data, &moist_data, sizeof(SMoist_t));
        memcpy(&_bus_ctrl_msg._buff_time, &buff_time, sizeof(SBufTime_t));
    mutex_unlock(BUS_CTRL_M_ID);
}


void bus_controller_read(SBusSensCtrlMsg_t *msg)
{
    mutex_lock(BUS_CTRL_M_ID);
        memcpy(msg, &_bus_ctrl_msg, sizeof(SBusSensCtrlMsg_t));
    mutex_unlock(BUS_CTRL_M_ID);
}

void controller_bus_send(
    EDevID_t dev_id,
    SDevCmd_t cmd
)
{
    mutex_lock(CTRL_BUS_M_ID);
        memcpy(&_ctrl_bus_msg._dev_id, &dev_id, sizeof(EDevID_t));
        memcpy(&_ctrl_bus_msg._cmd, &cmd, sizeof(SDevCmd_t));
    mutex_unlock(CTRL_BUS_M_ID);
}


void controller_bus_read(SCtrlBusSensMsg_t *msg)
{
    mutex_lock(CTRL_BUS_M_ID);
        memcpy(msg, &_ctrl_bus_msg, sizeof(SCtrlBusSensMsg_t));
    mutex_unlock(CTRL_BUS_M_ID);
}