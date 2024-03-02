#ifndef I_WIRELESS_DATA_H_
#define I_WIRELESS_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define BUFFER_SIZE 128
#define WIRELESS_ERROR_SLOT 1
#define HAL_WLS_CONFIG_ERROR -127
#define WLS_DSP_IIR_ERROR -19
#define WLS_DSP_NORMALIZE_ERROR -18
#define WLS_DRV_BUFFER_EMPTY -17

typedef enum{
    WLS_TASK_OK,
    WLS_TASK_INIT_FAIL,
    WLS_TASK_SM_INIT_FAIL,
    WLS_MINOR_FAULT,
    WLS_MAYOR_FAULT
}EWlsTaskStatus_t;

typedef struct {
    uint8_t ID;
    EWlsTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SWlsTaskInfo_t;

#endif /* I_WIRELESS_DATA_H_ */