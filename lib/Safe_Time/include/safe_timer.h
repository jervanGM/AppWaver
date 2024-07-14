/**
 * @file safe_timer.h
 * @brief Safe timer functions for handling timers with redundancy.
 */

#ifndef SAFE_TIMER_H_
#define SAFE_TIMER_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "sw_tmr_cfg.h"
#include "hw_tmr_cfg.h"

/**
 * @brief Get the current system time.
 *
 * @return The current system time in seconds.
 */
int64_t get_system_time(void);

/**
 * @brief Encode a time value to a date structure.
 *
 * @param[in] time The time value in seconds.
 * @return The encoded date structure.
 */
STime_t encode_time_to_date(c_int64_t time);

/**
 * @brief Encode a date structure to a time value.
 *
 * @param[in] date The date structure.
 * @return The encoded time value in seconds.
 */
int64_t encode_date_to_time(STime_t date);

/**
 * @brief Initialize a safe timer with redundancy.
 *
 * @param[in] timer Pointer to the timer structure to initialize.
 * @return Timer configuration error code.
 */
ETimerCfgError_t safe_timer_init(STimer_t *timer);

/**
 * @brief Restart a safe timer with redundancy.
 *
 * @param[in] timer Pointer to the timer structure to restart.
 * @return Timer configuration error code.
 */
ETimerCfgError_t safe_timer_restart(STimer_t *timer);

/**
 * @brief Check if a safe timer is active.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer is active, false otherwise.
 */
bool safe_timer_is_on(STimer_t *timer);

/**
 * @brief Check if a safe timer has expired.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer has expired, false otherwise.
 */
bool safe_timer_is_expired(STimer_t *timer);

/**
 * @brief Delete a safe timer with redundancy.
 *
 * @param[in] timer Pointer to the timer structure to delete.
 * @return Timer configuration error code.
 */
ETimerCfgError_t safe_timer_delete(STimer_t *timer);

#endif /* SAFE_TIMER_H_ */
