#ifndef I_CONTROL_DATA_H_
#define I_CONTROL_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define CONTROL_ERROR_SLOT 4

typedef enum{
    CTRL_TASK_OK,
    CTRL_TASK_INIT_FAIL,
    CTRL_TASK_SM_INIT_FAIL,
    CTRL_MINOR_FAULT,
    CTRL_MAYOR_FAULT
}ECtrlTaskStatus_t;

typedef struct {
    uint8_t ID;
    ECtrlTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SCtrlTaskInfo_t;


#endif /* I_CONTROL_DATA_H_ */