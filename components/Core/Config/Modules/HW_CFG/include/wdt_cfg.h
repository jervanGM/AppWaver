#ifndef WDT_CFG_H_
#define WDT_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"

/**
 * @brief Disable the task watchdog timer (WDT) with specified timeout.
 * 
 * @details This function configures the task watchdog timer and disables panic triggering.
 */
void set_wdt_disable();

/**
 * @brief Enable the task watchdog timer (WDT) with panic triggering.
 * 
 * @details This function enables the task watchdog timer with panic triggering.
 *          Panic will occur if the timer is not refreshed within the configured timeout.
 */
void set_wdt_enable();

#endif /* WDT_CFG_H_ */