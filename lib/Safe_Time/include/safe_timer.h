#ifndef SAFE_TIMER_H_
#define SAFE_TIMER_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "sw_tmr_cfg.h"
#include "hw_tmr_cfg.h"

int64_t get_system_time(void);

STime_t encode_time_to_date(c_int64_t time);

int64_t encode_date_to_time(STime_t date);

ETimerCfgError_t safe_timer_init(STimer_t *timer);

ETimerCfgError_t safe_timer_restart(STimer_t *timer);

bool safe_timer_is_on(STimer_t *timer);

bool safe_timer_is_expired(STimer_t *timer);

ETimerCfgError_t safe_timer_delete(STimer_t *timer);

#endif /* SAFE_TIMER_H_ */