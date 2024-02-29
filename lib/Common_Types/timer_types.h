#ifndef TIMER_TYPES_H_
#define TIMER_TYPES_H_

#define TIME_START 0 
#include <stdlib.h>
#include <stdbool.h>
#include "gen_types.h"

#define SEC_DIV 60
#define MIN_DIV 60
#define HOUR_DIV 24
#define DAY_DIV 30
#define MONTH_DIV 12

typedef enum{
    UNIQUE,
    PERIODIC
} ETypeTimer_t;

typedef enum{
    TMR_OK,                 /*!< esp_err_t value indicating success (no error) */
    TMR_MEM_ERR,           /*!< Out of memory */
    TMR_INVALID_ARG_ERR,   /*!< Invalid argument */
    TMR_BAD_STATE_ERR,     /*!< Invalid state */
    TMR_BAD_SIZE_ERR,      /*!< Invalid size */
    TMR_UNSUPPORTED_OP,     /*!< Operation or feature not supported */
    TMR_UNKNOWN_ERR,
    TMR_WARNING
} ETimerCfgError_t;

typedef struct {
    c_uint32_t start_time;
    void *handler;
} SSwTimer_t;

typedef struct {
    c_int64_t start_time;
    bool is_active;
} SHwTimer_t;

typedef struct {
    char *id;
    c_uint64_t period;
    ETypeTimer_t type;
    SSwTimer_t rtos_timer;
    SHwTimer_t rtc_timer;
    bool redundant_timer_active;
} STimer_t;

typedef struct{
    c_uint8_t sec;
    c_uint8_t min;
    c_uint8_t hour;
    c_uint8_t day;
    c_uint8_t month;
    c_uint8_t year;
} STime_t;

#endif /* TIMER_TYPES_H_ */