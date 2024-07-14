/**
 * @file sw_tmr_cfg.h
 * @brief Software timer configuration and handling.
 */

#ifndef SW_TMR_CFG_H_
#define SW_TMR_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "timer_types.h"

#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#define TIMER_WAIT_TICK_NULL 0 

/**
 * @brief Get the current software system time.
 *
 * @return The current software system time in seconds.
 */
c_int64_t get_sw_system_time(void);

/**
 * @brief Initialize a software timer.
 *
 * @param[in] timer Pointer to the timer structure to initialize.
 * @return Timer configuration error code.
 */
ETimerCfgError_t sw_timer_init(STimer_t *timer);

/**
 * @brief Restart a software timer.
 *
 * @param[in] timer Pointer to the timer structure to restart.
 * @return Timer configuration error code.
 */
ETimerCfgError_t sw_timer_restart(STimer_t *timer);

/**
 * @brief Check if a software timer is active.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer is active, false otherwise.
 */
bool sw_timer_is_on(STimer_t *timer);

/**
 * @brief Check if a software timer has expired.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer has expired, false otherwise.
 */
bool sw_timer_is_expired(STimer_t *timer);

/**
 * @brief Delete a software timer.
 *
 * @param[in] timer Pointer to the timer structure to delete.
 * @return Timer configuration error code.
 */
ETimerCfgError_t sw_timer_delete(STimer_t *timer);

/**
 * @brief Callback function for the FreeRTOS timer.
 *
 * @param[in] xTimer The handle of the timer that expired.
 */
static void timerCallback(TimerHandle_t xTimer);

#endif /* SW_TMR_CFG_H_ */
