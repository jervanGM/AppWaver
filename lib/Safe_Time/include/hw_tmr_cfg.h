/**
 * @file hw_tmr_cfg.h
 * @brief Hardware timer configuration and management functions.
 */

#ifndef HW_TMR_CFG_H_
#define HW_TMR_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "timer_types.h"

/** Conversion factor from microseconds to seconds. */
#define SYS_TIME_DIV 1000000

/** Conversion factor from milliseconds to microseconds. */
#define MS_TO_US 1000

/**
 * @brief Get the current system time.
 *
 * @return The current system time in microseconds.
 */
c_int64_t get_hw_system_time(void);

/**
 * @brief Initialize a hardware timer.
 *
 * @param[in] timer Pointer to the timer structure to initialize.
 * @return Timer configuration error code.
 */
ETimerCfgError_t hw_timer_init(STimer_t *timer);

/**
 * @brief Restart a hardware timer.
 *
 * @param[in] timer Pointer to the timer structure to restart.
 * @return Timer configuration error code.
 */
ETimerCfgError_t hw_timer_restart(STimer_t *timer);

/**
 * @brief Check if a hardware timer is active.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer is active, false otherwise.
 */
bool hw_timer_is_on(STimer_t *timer);

/**
 * @brief Check if a hardware timer has expired.
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer has expired, false otherwise.
 */
bool hw_timer_is_expired(STimer_t *timer);

/**
 * @brief Delete a hardware timer.
 *
 * @param[in] timer Pointer to the timer structure to delete.
 * @return Timer configuration error code.
 */
ETimerCfgError_t hw_timer_delete(STimer_t *timer);

/**
 * @brief Initialize a hardware timer (internal function).
 *
 * @param[in] timer Pointer to the timer structure to initialize.
 * @return Timer configuration error code.
 */
static ETimerCfgError_t hw_timer_init_internal(STimer_t *timer);

/**
 * @brief Restart a hardware timer (internal function).
 *
 * @param[in] timer Pointer to the timer structure to restart.
 * @return Timer configuration error code.
 */
static ETimerCfgError_t hw_timer_restart_internal(STimer_t *timer);

/**
 * @brief Check if a hardware timer has expired (internal function).
 *
 * @param[in] timer Pointer to the timer structure to check.
 * @return True if the timer has expired, false otherwise.
 */
static bool hw_timer_is_expired_internal(STimer_t *timer);

/**
 * @brief Delete a hardware timer (internal function).
 *
 * @param[in] timer Pointer to the timer structure to delete.
 * @return Timer configuration error code.
 */
static ETimerCfgError_t hw_timer_delete_internal(STimer_t *timer);

#endif /* HW_TMR_CFG_H_ */
