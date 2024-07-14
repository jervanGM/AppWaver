#ifndef EV_HANDLER_H_
#define EV_HANDLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_acc_it_data.h"

/**
 * @brief Handles an interrupt pulse.
 *
 * This function retrieves the bus port and reads interrupt source registers to determine
 * the type of interrupt that has been lauched. It returns different commands based on the
 * interrupt source and logs errors if the operations fail.
 *
 * @return The interrupt command based on the interrupt source.
 * @retval ACT_IT1 if the interrupt source 1 threshold is met.
 * @retval ACT_IT2 if the interrupt source 2 threshold is met.
 * @retval ACT_UNK if an unknown interrupt occurs.
 * @retval EV_FAIL if there is a failure in reading the interrupt source.
 */
EIntCmd_t acc_it_handle_pulse();

#endif // ACC_IT_HANDLER_H