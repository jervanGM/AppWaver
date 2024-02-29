#include "sw_tmr_cfg.h"


c_int64_t get_sw_system_time(void)
{
    static c_int64_t time = 0;
    return ++time;
}

ETimerCfgError_t sw_timer_init(STimer_t *timer)
{
    return TMR_OK;
}

ETimerCfgError_t sw_timer_restart(STimer_t *timer)
{
    return TMR_OK;
}

bool sw_timer_is_on(STimer_t *timer)
{
    return true;
}

bool sw_timer_is_expired(STimer_t *timer)
{
    return false;
}

ETimerCfgError_t sw_timer_delete(STimer_t *timer)
{
    return TMR_OK;
}

static void timerCallback()
{
    return;
}

