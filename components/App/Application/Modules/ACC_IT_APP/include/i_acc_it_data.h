#ifndef I_ACC_IT_DATA_H_
#define I_ACC_IT_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "SERIES_ID.h"

#define ACC_IT_ERROR_SLOT 18
#define HAL_ACC_IT_CONFIG_ERROR -127
#define ACC_IT_CMD_ERROR -126

#ifdef ADVANCED
#define ACC_IT1_PIN 14
#define ACC_IT2_PIN 15
#endif

#define IT_VAL_1 1
#define IT_VAL_2 2

#define IT1_THESHOLD 64
#define IT2_THESHOLD 64

#define LIS3DH_DEFAULT_ADDR 0x18
#define LIS3DH_INT1_SRC     0x31
#define LIS3DH_INT2_SRC     0x35

typedef enum{
    ACC_IT_TASK_OK,
    ACC_IT_TASK_INIT_FAIL,
    ACC_IT_MINOR_FAULT,
    ACC_IT_MAYOR_FAULT
}EAccItTaskStatus_t;

typedef enum{
    ACT_IT1,
    ACT_IT2,
    ACT_UNK,
    EV_FAIL
}EIntCmd_t;

typedef struct {
    uint8_t ID;
    EAccItTaskStatus_t status;
} SAccItTaskInfo_t;

typedef struct{
    SAccItTaskInfo_t _task_info;
    EIntCmd_t _int_cmd;
    STime_t _it_moment;
}SAccItMsg_t;

#endif /* I_ACC_IT_DATA_H_ */