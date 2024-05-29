#ifndef BUS_T_SHARE_H_
#define BUS_T_SHARE_H_

#include <stdbool.h>
#include "i_bus_data.h"

#define BUS_CTRL_M_ID 14
#define CTRL_BUS_M_ID 15

void set_task_bus_info(SBusTaskInfo_t task_info);

void set_task_bus_status(EBusTaskStatus_t status);

void bus_controller_send(
    SAxisDataBuffer_t axis_buff,
    STemp_t temp_data,
    SMoist_t moist_data,
    SBufTime_t buff_time
);

void bus_controller_read(SBusSensCtrlMsg_t *msg);

void controller_bus_send(
    EDevID_t dev_id,
    SDevCmd_t cmd;
);

void controller_bus_read(SCtrlBusSensMsg_t *msg);

#endif /* BUS_T_SHARE_H_ */