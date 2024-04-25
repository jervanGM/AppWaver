#ifndef WIRELESS_T_SHARE_H_
#define WIRELESS_T_SHARE_H_

#include <stdbool.h>
#include "i_wireless_data.h"
#include "common_t_data.h"

#define WLS_CTRL_M_ID 2
#define CTRL_WLS_M_ID 3

void set_task_wireless_info(SWlsTaskInfo_t task_info);

void set_task_wireless_status(EWlsTaskStatus_t status);

void wireless_controller_send(SWlsCommand_t command);

void wireless_controller_read(SWlsCtrlMsg_t *msg);

void controller_wireless_send(
    SErrorInfo_t alarm,
    SSystemStatus_t status,
    uint32_t *plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t *axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    STime_t system_time);

void controller_wireless_read(SCtrlWlsMsg_t *msg);

#endif /* WIRELESS_T_SHARE_H_ */