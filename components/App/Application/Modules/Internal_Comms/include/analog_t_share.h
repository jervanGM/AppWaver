#ifndef ANALOG_T_SHARE_H_
#define ANALOG_T_SHARE_H_

#include <stdbool.h>
#include "i_analog_data.h"

#define ANALOG_M_ID 0

void analog_controller_send(
    STaskInfo_t task_info,
    SDataBuffer_t plant_buff,
    SBufferTime_t buff_time);

void analog_controller_read(SAnalogSensMsg_t *msg);

#endif /* ANALOG_T_SHARE_H_ */