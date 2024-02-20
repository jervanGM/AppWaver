#include "safe_timer.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include <inttypes.h>
STime_t get_system_time(void)
{
    static bool hw_sys_time_err = false;
    static c_int64_t prev_sys_time = TIME_START;
    c_int64_t sys_time = TIME_START;
    if (!hw_sys_time_err)
    {
        sys_time = get_hw_system_time();
        if ((sys_time == TIME_START) || (sys_time == prev_sys_time))
        {
            hw_sys_time_err = true;
            TRACE_ERROR("Hardware system time has failed, switching to software system time");
        }
        else
        {
            hw_sys_time_err = false;
        }
        sys_time /= SYS_TIME_DIV;
    }
    else
    {
        sys_time = get_sw_system_time();
        ASSERT_PANIC((sys_time == TIME_START) || (sys_time == prev_sys_time),
        "Hardware and software system time failure, rebooting");
    }

    prev_sys_time = sys_time;
    return encode_time_to_date(sys_time);
}

STime_t encode_time_to_date(c_int64_t time)
{
    STime_t date;

    date.sec = time % SEC_DIV;
    time /= SEC_DIV;
    date.min = time % MIN_DIV;
    time /= MIN_DIV;
    date.hour = time % HOUR_DIV;
    time /= HOUR_DIV;
    date.day = time % DAY_DIV;
    time /= DAY_DIV;
    date.month = time % MONTH_DIV;
    date.year = time / MONTH_DIV;

    return date;
}

ETimerCfgError_t safe_timer_init(STimer_t *timer)
{
    timer->redundant_timer_active = false;

    ETimerCfgError_t error = sw_timer_init(timer);
    if (error != TMR_OK)
    {
        timer->redundant_timer_active = true;
        error = hw_timer_init(timer);
        if (error != TMR_OK)
        {
            return TMR_UNKNOWN_ERR;
        }
        return TMR_WARNING;
    }

    return TMR_OK;
}

ETimerCfgError_t safe_timer_restart(STimer_t *timer)
{
    if (!timer->redundant_timer_active)
    {
        return sw_timer_restart(timer);
    }
    else
    {
        return hw_timer_restart(timer);
    }
}

bool safe_timer_is_on(STimer_t *timer)
{
    if (!timer->redundant_timer_active)
    {
        return sw_timer_is_on(timer);
    }
    else
    {
        return hw_timer_is_on(timer);
    }
}

bool safe_timer_is_expired(STimer_t *timer)
{
    if (!timer->redundant_timer_active)
    {
        return sw_timer_is_expired(timer);
    }
    else
    {
        return hw_timer_is_expired(timer);
    }
}

ETimerCfgError_t safe_timer_delete(STimer_t *timer)
{
    if (!timer->redundant_timer_active)
    {
        return sw_timer_delete(timer);
    }
    else
    {
        return hw_timer_delete(timer);
    }
}