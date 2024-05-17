#ifndef I_BUS_DATA_H_
#define I_BUS_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "dev_constants.h"

#define BUS_HANDLER_ID 8

#define BUFFER_SIZE 128

#define BUS_DRV_OK 0

#define BUS_ERROR_SLOT 16
#define HAL_BUS_CONFIG_ERROR -127
#define BUS_DRV_INIT_ERROR -126
#define BUS_DRV_DEINIT_ERROR -125
#define BUS_DRV_ON_WRITE_FATAL_ERROR -124
#define BUS_DRV_ON_READ_FATAL_ERROR -123

#define BUS_DEVICE_NOT_INIT -19
#define BUS_APP_BUFFER_EMPTY -18
#define BUS_DRV_HEAT_CMD_INVALID -17


/** Optional pre-heater configuration setting */
typedef enum {
  SHT4X_NO_HEATER,
  SHT4X_HIGH_HEATER_1S,
  SHT4X_HIGH_HEATER_100MS,
  SHT4X_MED_HEATER_1S,
  SHT4X_MED_HEATER_100MS,
  SHT4X_LOW_HEATER_1S,
  SHT4X_LOW_HEATER_100MS,
} ESht4xHeaterCmd_t;

typedef enum{
    BUS_TASK_OK,
    BUS_TASK_INIT_FAIL,
    BUS_TASK_SM_INIT_FAIL,
    BUS_MINOR_FAULT,
    BUS_MAYOR_FAULT
}EBusTaskStatus_t;

typedef struct {
    uint8_t ID;
    EBusTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SBusTaskInfo_t;

typedef struct {
    STime_t start_time;
    STime_t end_time;
} SBufTime_t;

typedef struct
{
    float temperature;
}STemp_t;

typedef struct
{
    float moist;
}SMoist_t;

typedef struct {
    float x[BUFFER_SIZE];
    float y[BUFFER_SIZE];
    float z[BUFFER_SIZE];
    size_t size;
    bool ready;
} SAxisDataBuffer_t;

typedef struct{
    SBusTaskInfo_t _task_info;
    SAxisDataBuffer_t _axis_buff;
    STemp_t _temp_data;
    SMoist_t _moist_data;
    SBufTime_t _buff_time;
}SBusSensCtrlMsg_t;

typedef enum
{
    TEMP_HUM_SENS,
    ACCELEROMETER
}EDevID_t;

typedef struct
{
    ESht4xHeaterCmd_t heater_cmd;
    bool force;   
}SDevCmd_t;

typedef struct{
    EDevID_t _dev_id;
    SDevCmd_t _cmd;
}SCtrlBusSensMsg_t;

#endif /* I_BUS_DATA_H_ */