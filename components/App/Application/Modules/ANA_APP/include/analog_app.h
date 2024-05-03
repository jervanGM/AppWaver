#ifndef ANALOG_APP_H_
#define ANALOG_APP_H_

#include <stdbool.h>
#include "i_analog_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the analog application.
 */
void analog_app_init();

/**
 * @brief Checks for faults in the analog application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, ANA_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, ANA_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, ANA_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EAnaTaskStatus_t analog_app_check_faults();


#endif /* ANALOG_APP_H_ */