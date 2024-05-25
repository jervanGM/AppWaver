#ifndef I_PW_DATA_H_
#define I_PW_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "SERIES_ID.h"
#include "CONSTANTS.h"

#define POWER_ERROR_SLOT 8
#define POWER_HANDLER_ID 5

#define POWER_OFF_TIME 1000

#ifdef BASIC
#define POWER_OFF_PIN 20
#endif

#ifdef ADVANCED
#define POWER_OFF_PIN 16
#define SOIL_PWM_PIN 4
#define SENS_SW_PIN 5

#define SOIL_FREQ  5
#define SOIL_DUTY 50
#define SOIL_PWM_CHAN 0
#endif



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
    PW_MAIN_OFF,
    PW_MAIN_RESET
}EMainSwSts_t;

typedef enum{
    PW_SOIL_ON,
    PW_SOIL_OFF
}ESoilActSts_t;

typedef enum{
    PW_WIFI_ON,
    PW_WIFI_OFF
}EWifiActSts_t;

typedef enum{
    PW_MODE_FULL,
    PW_MODE_LOW
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
    EWifiActSts_t _wifi_act_sts;
    EPwMode_t _pw_mode;
}SCtrlPwMsg_t;

#endif /* I_PW_DATA_H_ */