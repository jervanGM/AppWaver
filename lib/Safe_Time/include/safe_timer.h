#ifndef SAFE_TIMER_H_
#define SAFE_TIMER_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "sw_tmr_cfg.h"
#include "hw_tmr_cfg.h"

STime_t get_system_time(void);

STime_t encode_time_to_date(int64_t time);

ETimerCfgError_t safe_timer_init(STimer_t *timer);

ETimerCfgError_t safe_timer_restart(STimer_t *timer);

bool safe_timer_is_on(STimer_t *timer);

bool safe_timer_is_expired(STimer_t *timer);

ETimerCfgError_t safe_timer_delete(STimer_t *timer);

#endif /* SAFE_TIMER_H_ */