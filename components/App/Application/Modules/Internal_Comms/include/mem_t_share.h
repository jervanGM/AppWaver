#ifndef MEM_T_SHARE_H_
#define MEM_T_SHARE_H_

#include <stdbool.h>
#include "i_mem_data.h"
#include "common_t_data.h"

#define MEM_CTRL_M_ID 10
#define CTRL_MEM_M_ID 11

void set_task_ext_mem_info(SMemTaskInfo_t task_info);

void set_task_ext_mem_status(EMemTaskStatus_t status);

void mem_ctrl_read(SMemCtrlMsg_t *msg);

void ctrl_mem_send(
    SErrorInfo_t alarm,
    SSystemStatus_t status,
    SPPlantData_t plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    STime_t system_time);

void ctrl_mem_read(SCtrlMemMsg_t *msg);

#endif /* MEM_T_SHARE_H_ */