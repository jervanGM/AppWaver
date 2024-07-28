#ifndef COMMON_T_DATA_H_
#define COMMON_T_DATA_H_

#include "CONSTANTS.h"

typedef enum {
    SYS_NORMAL,
    SYS_RECORD
} ESysMode_t;

typedef enum {
    E_PW_NORMAL,
    E_PW_OFF,
    E_PW_RESET
} EPowerMode_t;

typedef enum {
    E_SEV_AV
} EErrorSeverity_t;

typedef enum {
    E_ANA_TASK
} EErrorOrigin_t;

typedef struct {
    uint16_t code;
    EErrorSeverity_t severity;
    EErrorOrigin_t origin;
} SErrorInfo_t;

typedef struct {
    char sd_sts[30];
    char gpio_sts[30];
    char acc_sts[30];
    char temp_moist_sts[30];
    char solar_sts[30];
    char plant_sts[30];
    char soil_sts[30];
    char main_timer_sts[30];
    char power_sts[30];
    char controller_sts[30];
    char device_sts[30];
} SSystemStatus_t;

typedef struct {
    uint8_t light;
    uint8_t sun;
    uint8_t soil_moist;
    uint32_t plant_inst_data;
    int64_t instant_analog_time;
    float x;
    float y;
    float z;
    float temp;
    float air_moist;
    int64_t instant_digital_time;
} SEnvData_t;

typedef struct {
    EPowerMode_t prev_pw_mode;
    EPowerMode_t curnt_pw_mode;
} SPowerData_t;

typedef struct {
    float x[DATA_BUFFER_SIZE];
    float y[DATA_BUFFER_SIZE];
    float z[DATA_BUFFER_SIZE];
    bool it1;
    bool it2;
    int64_t start_time;
    int64_t end_time;
} SAxisData_t;

typedef struct {
    uint32_t data[DATA_BUFFER_SIZE];
    int64_t start_time;
    int64_t end_time;
    bool is_ready;
    uint8_t record_counter;
} SPPlantData_t;

#endif /* COMMON_T_DATA_H_ */