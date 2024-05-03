#include "hw_tmr_cfg.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef _WIN32
static bool stop_hw_timer = false;
#else
static volatile bool stop_hw_timer = false;
#endif

c_int64_t get_hw_system_time(void)
{
#ifdef _WIN32
    if (!stop_hw_timer)
    {
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);

        // Convertir FILETIME a un valor de 64 bits en microsegundos
        ULARGE_INTEGER ul;
        ul.LowPart = ft.dwLowDateTime;
        ul.HighPart = ft.dwHighDateTime;

        return ul.QuadPart / 10; // Convertir a microsegundos
    }
    else
    {
        static int64_t time = 0;
        return time++;
    }
#else
    if (!stop_hw_timer)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);

        // Convertir timeval a un valor de 64 bits en microsegundos
        int64_t microseconds = tv.tv_sec * 1000000LL + tv.tv_usec;
        return microseconds;
    }
    else
    {
        static int64_t time = 0;
        return time++;
    }
#endif
}

void set_stop_system_time()
{
    stop_hw_timer = true;
}

void reset_stop_system_time()
{
    stop_hw_timer = false;
}

ETimerCfgError_t hw_timer_init(STimer_t *timer)
{
    return TMR_OK;
}

ETimerCfgError_t hw_timer_restart(STimer_t *timer)
{
    return TMR_OK;
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
    return TMR_OK;
}

static ETimerCfgError_t hw_timer_restart_internal(STimer_t *timer)
{
    timer->rtc_timer.start_time = TIME_START;
    timer->rtc_timer.is_active = false;

    return (timer->rtc_timer.start_time != TIME_START) ? TMR_UNKNOWN_ERR : hw_timer_init_internal(timer);
}

static bool hw_timer_is_expired_internal(STimer_t *timer)
{
    return false;
}

static ETimerCfgError_t hw_timer_delete_internal(STimer_t *timer)
{
    return TMR_OK;
}
