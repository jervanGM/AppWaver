#ifndef ANALOG_T_SHARE_H_
#define ANALOG_T_SHARE_H_

#include <stdbool.h>
#include "i_analog_data.h"

#define ANALOG_M_ID 0
#define CTRL_ANALOG_M_ID 1

void set_task_analog_info(SAnaTaskInfo_t task_info);

void set_task_analog_status(EAnaTaskStatus_t status);

void analog_controller_send(
    SDataBuffer_t plant_buff,
    SBufferTime_t buff_time);

#ifdef ADVANCED
void analog_controller_send_env_data(SAnaEnvData_t env_data);
#endif

void analog_controller_read(SAnalogSensMsg_t *msg);

#endif /* ANALOG_T_SHARE_H_ */