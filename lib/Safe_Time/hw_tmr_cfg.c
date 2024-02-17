#include "hw_tmr_cfg.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "esp_timer.h"


int64_t get_hw_system_time(void)
{
    return esp_timer_get_time();
}

ETimerCfgError_t hw_timer_init(STimer_t *timer)
{
    return hw_timer_init_internal(timer);
}

ETimerCfgError_t hw_timer_restart(STimer_t *timer)
{
    return hw_timer_restart_internal(timer);
}

bool hw_timer_is_on(STimer_t *timer)
{
    return timer->rtc_timer.is_active;
}

bool hw_timer_is_expired(STimer_t *timer)
{
    return hw_timer_is_expired_internal(timer);
}

ETimerCfgError_t hw_timer_delete(STimer_t *timer)
{
    return hw_timer_delete_internal(timer);
}

static ETimerCfgError_t hw_timer_init_internal(STimer_t *timer)
{
    timer->rtc_timer.start_time = esp_timer_get_time();
    timer->rtc_timer.is_active = true;
    
    return (timer->rtc_timer.start_time == TIME_START) ? TMR_UNKNOWN_ERR : TMR_OK;
}


static ETimerCfgError_t hw_timer_restart_internal(STimer_t *timer)
{
    timer->rtc_timer.start_time = TIME_START;
    timer->rtc_timer.is_active = false;

    return (timer->rtc_timer.start_time != TIME_START) ? TMR_UNKNOWN_ERR : hw_timer_init_internal(timer);
}

static bool hw_timer_is_expired_internal(STimer_t *timer)
{
    int64_t time_delta = (timer->rtc_timer.start_time - esp_timer_get_time());
    if (time_delta >= timer->period)
    {
        if (timer->type == PERIODIC)
        {
            hw_timer_restart_internal(timer);
        }
        else if (timer->type == UNIQUE)
        {
            hw_timer_delete_internal(timer);
        }
        else
        {
            // ASSERT PANIC
        }
        return true;
    }
    return false;
}

static ETimerCfgError_t hw_timer_delete_internal(STimer_t *timer)
{
    timer->id = NULL;
    timer->rtc_timer.start_time = TIME_START;
    timer->rtc_timer.is_active = false;

    return (timer->rtc_timer.start_time != TIME_START) ? TMR_UNKNOWN_ERR : TMR_OK;
}