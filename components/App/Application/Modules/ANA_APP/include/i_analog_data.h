#ifndef I_ANALOG_DATA_H_
#define I_ANALOG_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "SERIES_ID.h"
#include "CONSTANTS.h"

#define ANA_HANDLER_ID 0

#define ANALOG_ENV_SENSORS 3

#define ANALOGIC_ERROR_SLOT 0
#define HAL_ANA_CONFIG_ERROR -127
#define ANA_DRV_INIT_ERROR -126
#define ANA_DRV_DEINIT_ERROR -125
#define ANA_DRV_ON_WRITE_FATAL_ERROR -124
#define ANA_DRV_ON_READ_FATAL_ERROR -123

#define ANA_DSP_IIR_ERROR -19
#define ANA_DSP_NORMALIZE_ERROR -18
#define ANA_DRV_BUFFER_EMPTY -17
#define ANA_DRV_ENV_DATA_EMPTY -16
#define ANA_APP_ENV_DATA_EMPTY -15
#define ANA_DRV_ON_WRITE_ERROR -14
#define ANA_DRV_ON_READ_ERROR -13

#define MAX_I_SOLAR_VALUE_THRESHOLD  2550
#define MIN_I_SOLAR_VALUE_THRESHOLD  0
#define MAX_V_SOLAR_VALUE_THRESHOLD 1250
#define MIN_V_SOLAR_VALUE_THRESHOLD  0

#define MIN_SOIL_MOIST_THRESHOLD 3769
#define MAX_SOIL_MOIST_THRESHOLD 3675

#define ANA_DRV_OK 0
#define ANA_DRV_FAIL -1

typedef enum{
    ANA_TASK_OK,
    ANA_TASK_INIT_FAIL,
    ANA_TASK_SM_INIT_FAIL,
    ANA_MINOR_FAULT,
    ANA_MAYOR_FAULT
}EAnaTaskStatus_t;

typedef struct {
    int64_t start_time;
    int64_t end_time;
} SBufferTime_t;

typedef struct {
    uint32_t data[DATA_BUFFER_SIZE];
    size_t size;
    bool ready;
} SDataBuffer_t;

typedef struct{
    uint8_t light_percentage;
    uint8_t direct_sun_percentage;
    uint8_t soil_moist_percentage;
}SAnaEnvData_t;

typedef struct {
    uint8_t ID;
    EAnaTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SAnaTaskInfo_t;

typedef struct{
    SAnaTaskInfo_t _task_info;
    SDataBuffer_t _plant_buff;
    SBufferTime_t _buff_time;
#ifdef ADVANCED
    SAnaEnvData_t _env_data;
#endif
}SAnalogSensMsg_t;

#endif /* I_ANALOG_DATA_H_ */