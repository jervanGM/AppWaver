#ifndef I_ANALOG_DATA_H_
#define I_ANALOG_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define BUFFER_SIZE 128

typedef enum{
    ANA_TASK_OK,
    ANA_TASK_INIT_FAIL,
    ANA_TASK_SM_INIT_FAIL,
}ETaskStatus_t;

typedef struct {
    STime_t start_time;
    STime_t end_time;
} SBufferTime_t;

typedef struct {
    uint8_t data[BUFFER_SIZE];
    size_t size;
    bool ready;
} SDataBuffer_t;

typedef struct {
    uint8_t ID;
    ETaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} STaskInfo_t;

typedef struct{
    STaskInfo_t _task_info;
    SDataBuffer_t _plant_buff;
    SBufferTime_t _buff_time;
}SAnalogSensMsg_t;

#endif /* I_ANALOG_DATA_H_ */