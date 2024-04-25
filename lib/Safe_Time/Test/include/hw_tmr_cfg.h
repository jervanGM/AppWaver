#ifndef HW_TMR_CFG_H_
#define HW_TMR_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "timer_types.h"
#include <stdbool.h>

#define SYS_TIME_DIV 1000000 //uSeconds to Seconds
#define MS_TO_US 1000

void set_stop_system_time();

c_int64_t get_hw_system_time(void);

ETimerCfgError_t hw_timer_init(STimer_t *timer);

ETimerCfgError_t hw_timer_restart(STimer_t *timer);

bool hw_timer_is_on(STimer_t *timer);

bool hw_timer_is_expired(STimer_t *timer);

ETimerCfgError_t hw_timer_delete(STimer_t *timer);

static ETimerCfgError_t hw_timer_init_internal(STimer_t *timer);

static ETimerCfgError_t hw_timer_restart_internal(STimer_t *timer);

static bool hw_timer_is_expired_internal(STimer_t *timer);

static ETimerCfgError_t hw_timer_delete_internal(STimer_t *timer);

#endif /* HW_TMR_CFG_H_ */