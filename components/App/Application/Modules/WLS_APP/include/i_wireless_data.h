#ifndef I_WIRELESS_DATA_H_
#define I_WIRELESS_DATA_H_
#include <stdint.h>
#include "safe_timer.h"

#define WIRELESS_ERROR_SLOT 2
#define HAL_WLS_CONFIG_ERROR -127
#define WLS_ANJAY_LOOP_ERROR -126
#define WLS_ANJAY_OBJ_CREATE_ERROR -125
#define WLS_ANJAY_CORE_INSTALL_ERROR -124
#define WLS_DRV_INIT_ERROR -123
#define WLS_DRV_DISCONNECT_ERROR -121
#define WLS_DRV_RESET_ERROR -120

#define WLS_DEVICE_OBJ_INIT_ERROR -18
#define WLS_PLANT_OBJ_INIT_ERROR -17
#define WLS_ANJAY_SERVER_CONFIG_ERROR -16
#define WLS_DRV_GET_MAC_ERROR -15
#define WLS_DRV_RECONNECT_ERROR -14
#define WLS_DRV_CONNECT_ERROR -13

#define WLS_DRV_OK 0

#define WLS_RECONNECT_EVENT 5

#define FOTA_ERROR_SLOT 3
#define HAL_OTA_CONFIG_ERROR -127
#define OTA_NOT_CONFIGURED -126

#define DATA_BUFFER_SIZE 128

typedef enum{
    WLS_TASK_OK,
    WLS_TASK_INIT_FAIL,
    WLS_TASK_SM_INIT_FAIL,
    WLS_TASK_RECONNECT_FAULT,
    WLS_MINOR_FAULT,
    WLS_MAYOR_FAULT
}EWlsTaskStatus_t;

typedef enum{
    WLS_CMD_REBOOT
}EWlsCmd_t;

//Wireless to control task interfaces
typedef struct {
    uint8_t ID;
    EWlsTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SWlsTaskInfo_t;

typedef struct{
    EWlsCmd_t _cmd;
    bool _force;
}SWlsCommand_t;

typedef struct{
    SWlsTaskInfo_t _task_info;
    SWlsCommand_t _command;
}SWlsCtrlSensMsg_t;

//Control to wireless task interface

typedef enum {
    SYS_BUFFER_MODE
} ESysMode_t;

typedef enum {
    E_PW_NORMAL
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

typedef struct{
    SErrorInfo_t _alarm;
    SSystemStatus_t _status;
    uint32_t _plant_signal[DATA_BUFFER_SIZE];
    SEnvData_t _env_data;
    SPowerData_t _power_data;
    SAxisData_t _axis_buff[DATA_BUFFER_SIZE];
    ESysMode_t _current_mode;
    ESysMode_t _previous_mode;
    STime_t _system_time;
}SCtrlWlsSensMsg_t;



#endif /* I_WIRELESS_DATA_H_ */