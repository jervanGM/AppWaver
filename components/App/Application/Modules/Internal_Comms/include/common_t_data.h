#ifndef COMMON_T_DATA_H_
#define COMMON_T_DATA_H_

typedef enum {
    SYS_BUFFER_MODE
} ESysMode_t;

typedef enum {
    E_PW_NORMAL,
    E_PW_OFF
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
    uint8_t soil_moist;
} SEnvData_t;

typedef struct {
    EPowerMode_t prev_pw_mode;
    EPowerMode_t currnt_pw_mode;
} SPowerData_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
    bool it1;
    bool it2;
} SAxisData_t;

#endif /* COMMON_T_DATA_H_ */