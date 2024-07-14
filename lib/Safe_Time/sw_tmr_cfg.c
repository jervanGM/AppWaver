#include "sw_tmr_cfg.h"

/**
 * @brief Callback function for the FreeRTOS timer.
 *
 * @param[in] xTimer The handle of the timer that expired.
 */
static void timerCallback(TimerHandle_t xTimer);

c_int64_t get_sw_system_time(void)
{
    return (c_int64_t)xTaskGetTickCount() / (c_int64_t)configTICK_RATE_HZ;
}

ETimerCfgError_t sw_timer_init(STimer_t *timer)
{
    if (timer->rtos_timer.handler != NULL)
    {
        // Timer already initialized
        return TMR_BAD_STATE_ERR;
    }

    timer->rtos_timer.handler = xTimerCreate(timer->id,
                                             pdMS_TO_TICKS(timer->period),
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
    timer->rtos_timer.start_time = (c_uint32_t)xTaskGetTickCount();

    return TMR_OK;
}

ETimerCfgError_t sw_timer_restart(STimer_t *timer)
{
    if (xTimerIsTimerActive(timer->rtos_timer.handler) == pdFALSE)
    {
        return TMR_BAD_STATE_ERR;
    }

    if (xTimerChangePeriod(timer->rtos_timer.handler, pdMS_TO_TICKS(timer->period), portMAX_DELAY) != pdPASS)
    {
        return TMR_UNKNOWN_ERR;
    }

    return TMR_OK;
}

bool sw_timer_is_on(STimer_t *timer)
{
    if (timer->rtos_timer.handler != NULL)
    {
        return (xTimerIsTimerActive(timer->rtos_timer.handler) == pdTRUE);
    }
    else
    {
        return false;
    }
}

bool sw_timer_is_expired(STimer_t *timer)
{
    c_uint32_t current_time = (c_uint32_t)xTaskGetTickCount();
    if ((current_time - timer->rtos_timer.start_time) >= pdMS_TO_TICKS(timer->period))
    {
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
