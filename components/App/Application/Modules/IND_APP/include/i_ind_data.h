#ifndef I_IND_DATA_H_
#define I_IND_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "CONSTANTS.h"

#define INDICATOR_ERROR_SLOT 6
#define INDICATOR_HANDLER_ID 4

#define HAL_IND_CONFIG_ERROR -127

#ifdef BASIC
#define IND_LED1_PIN 10
#define IND_UNK_PIN 255
#endif

#ifdef ADVANCED
#define IND_LED1_PIN 17
#define IND_UNK_PIN 255
#endif


typedef enum{
    IND_TASK_OK,
    IND_TASK_INIT_FAIL,
    IND_MINOR_FAULT,
    IND_MAYOR_FAULT
}EIndTaskStatus_t;

typedef enum{
    IND_LED1
}EIndId_t;

typedef enum{
    FIXED_ON,
    FIXED_OFF,
    BLINK_500_MS,
    BLINK_1_S,
    BLINK_2_S,
    BLINK_4_S,
    BLINK_TASK_ERROR,
}EIndSts_t;

typedef struct {
    uint8_t ID;
    EIndTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SIndTaskInfo_t;

typedef struct{
    SIndTaskInfo_t _task_info;
}SIndCtrlMsg_t;

typedef struct{
    EIndId_t _ind_id;
    EIndSts_t _ind_state;
}SCtrlIndMsg_t;

#endif /* I_IND_DATA_H_ */