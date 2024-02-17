#include "sw_tmr_cfg.h"


int64_t get_sw_system_time(void)
{
    return (int64_t)xTaskGetTickCount() / (int64_t)configTICK_RATE_HZ;
}

ETimerCfgError_t sw_timer_init(STimer_t *timer)
{
    if (timer->rtos_timer.handler != NULL)
    {
        // Timer ya inicializado
        return TMR_BAD_STATE_ERR;
    }

    timer->rtos_timer.handler = xTimerCreate(timer->id,
                                             timer->period * configTICK_RATE_HZ,
                                             (timer->type == PERIODIC) ? pdTRUE : pdFALSE,
                                             NULL,
                                             timerCallback);
    if (timer->rtos_timer.handler == NULL)
    {
        return TMR_MEM_ERR;
    }

    if (xTimerStart(timer->rtos_timer.handler, TIMER_WAIT_TICK_NULL) != pdPASS)
    {
        return TMR_BAD_STATE_ERR;
    }
    timer->rtos_timer.start_time = (int64_t)xTimerGetExpiryTime(timer->rtos_timer.handler);

    return TMR_OK;
}

ETimerCfgError_t sw_timer_restart(STimer_t *timer)
{
    if (xTimerIsTimerActive(timer->rtos_timer.handler) == pdFALSE)
    {
        return TMR_BAD_STATE_ERR;
    }

    if (xTimerChangePeriod(timer->rtos_timer.handler, timer->period * configTICK_RATE_HZ, portMAX_DELAY) != pdPASS)
    {
        return TMR_UNKNOWN_ERR;
    }

    return TMR_OK;
}

bool sw_timer_is_on(STimer_t *timer)
{
    return (xTimerIsTimerActive(timer->rtos_timer.handler) == pdTRUE);
}

bool sw_timer_is_expired(STimer_t *timer)
{
    uint32_t current_time = (uint32_t)xTaskGetTickCount();
    if (timer->rtos_timer.start_time < current_time)
    {
        if (current_time != portMAX_DELAY)
            timer->rtos_timer.start_time = current_time;
        return true;
    }
    return false;
}

ETimerCfgError_t sw_timer_delete(STimer_t *timer)
{
    if (xTimerDelete(timer->rtos_timer.handler, portMAX_DELAY) != pdPASS)
    {
        return TMR_UNKNOWN_ERR;
    }

    timer->rtos_timer.handler = NULL;

    return TMR_OK;
}

static void timerCallback(TimerHandle_t xTimer)
{
    (void)xTimer;
}

