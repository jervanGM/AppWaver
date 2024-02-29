#ifndef SW_TMR_CFG_H_
#define SW_TMR_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "timer_types.h"

#include <stdint.h>
#include <stdbool.h>

#define TIMER_WAIT_TICK_NULL 0 

c_int64_t get_sw_system_time(void);

ETimerCfgError_t sw_timer_init(STimer_t *timer);

ETimerCfgError_t sw_timer_restart(STimer_t *timer);

bool sw_timer_is_on(STimer_t *timer);

bool sw_timer_is_expired(STimer_t *timer);

ETimerCfgError_t sw_timer_delete(STimer_t *timer);

static void timerCallback();

#endif /* SW_TMR_CFG_H_ */