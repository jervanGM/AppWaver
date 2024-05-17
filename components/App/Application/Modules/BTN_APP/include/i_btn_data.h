#ifndef I_BTN_DATA_H_
#define I_BTN_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "SERIES_ID.h"

#define BUTTON_ERROR_SLOT 12
#define HAL_BTN_CONFIG_ERROR -127

#ifdef BASIC
#define BUTTON_PIN 21
#endif

#ifdef ADVANCED
#define BUTTON_PIN 18
#endif

typedef enum{
    BTN_TASK_OK,
    BTN_TASK_INIT_FAIL,
    BTN_MINOR_FAULT,
    BTN_MAYOR_FAULT
}EBtnTaskStatus_t;

typedef enum{
    BTN_CMD_NORMAL,
    BTN_CMD_MODE1,
    BTN_CMD_MODE2,
    BTN_CMD_MODE3,
    BTN_CMD_LONG1,
    BTN_CMD_PW_OFF,
    BTN_CMD_ERROR
}EBtnCmd_t;

typedef enum{
    NO_PULSE,
    SHORT_PRESS,
    LONG_PRESS,
    POWER_OFF,
    PULSE_ERR
}EBtnPulse_t;

typedef struct {
    uint8_t ID;
    EBtnTaskStatus_t status;
} SBtnTaskInfo_t;

typedef struct{
    SBtnTaskInfo_t _task_info;
    EBtnCmd_t _btn_cmd;
}SBtnMsg_t;

#endif /* I_BTN_DATA_H_ */