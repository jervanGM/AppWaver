#ifndef I_SERIAL_DATA_H_
#define I_SERIAL_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define SRL_HANDLER_ID 7

#define BUFFER_SIZE 128

#define SRL_DRV_OK 0

#define SERIAL_ERROR_SLOT 12
#define HAL_SRL_CONFIG_ERROR -127
#define SRL_DRV_INIT_ERROR -126
#define SRL_DRV_DEINIT_ERROR -125
#define SRL_DRV_ON_CONNECTED_FATAL_ERROR -124
#define SRL_DRV_ON_READ_FATAL_ERROR -123

#define SRL_DRV_CMD_BUFFER_OVERFLOW -19

typedef enum{
    SRL_TASK_OK,
    SRL_TASK_INIT_FAIL,
    SRL_TASK_SM_INIT_FAIL,
    SRL_MINOR_FAULT,
    SRL_MAYOR_FAULT
}ESrlTaskStatus_t;

typedef enum{
    SRL_CONNECTED,
    SRL_DISCONNECTED
}ESrlConnStatus_t;

typedef struct{
    char cmd[BUFFER_SIZE];
    bool force;
}SSerialCmd_t;

typedef struct {
    uint8_t ID;
    ESrlTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SSrlTaskInfo_t;

typedef struct{
    SSrlTaskInfo_t _task_info;
    ESrlConnStatus_t _serial_status;
    SSerialCmd_t _command;
}SSerialMsg_t;

#endif /* I_SERIAL_DATA_H_ */