#include "analog_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

SAnalogSensMsg_t _msg;


void analog_controller_send(
    STaskInfo_t task_info,
    SDataBuffer_t plant_buff,
    SBufferTime_t buff_time
)
{
    mutex_lock(ANALOG_M_ID);
        
        memcpy(&_msg._task_info, &task_info, sizeof(STaskInfo_t));
        memcpy(&_msg._plant_buff, &plant_buff, sizeof(SDataBuffer_t));
        memcpy(&_msg._buff_time, &buff_time, sizeof(SBufferTime_t));
    mutex_unlock(ANALOG_M_ID);
}


void analog_controller_read(SAnalogSensMsg_t *msg)
{
    mutex_lock(ANALOG_M_ID);
        memcpy(msg, &_msg, sizeof(SAnalogSensMsg_t));
    mutex_unlock(ANALOG_M_ID);
}