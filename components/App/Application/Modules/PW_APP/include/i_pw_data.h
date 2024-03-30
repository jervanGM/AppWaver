#ifndef I_PW_DATA_H_
#define I_PW_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define POWER_ERROR_SLOT 8

#define POWER_OFF_PIN 20

#define HAL_PW_CONFIG_ERROR -127

typedef enum{
    PW_TASK_OK,
    PW_TASK_INIT_FAIL,
    PW_TASK_SM_INIT_FAIL,
    PW_MINOR_FAULT,
    PW_MAYOR_FAULT
}EPwTaskStatus_t;

typedef enum{
    PW_SENS_ON,
    PW_SENS_OFF
}ESensSwSts_t;

typedef enum{
    PW_MAIN_ON,
    PW_MAIN_OFF
}EMainSwSts_t;

typedef enum{
    PW_SOIL_ON,
    PW_SOIL_OFF
}ESoilActSts_t;

typedef enum{
    PW_FULL,
    PW_LOW
}EPwMode_t;

typedef struct {
    uint8_t ID;
    EPwTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SPwTaskInfo_t;

typedef struct{
    SPwTaskInfo_t _task_info;
}SPwCtrlMsg_t;

typedef struct{
    ESensSwSts_t _sens_sw_sts;
    EMainSwSts_t _main_sw_sts;
    ESoilActSts_t _soil_act_sts;
    EPwMode_t _pw_mode;
}SCtrlPwMsg_t;

#endif /* I_PW_DATA_H_ */