#ifndef PW_APP_H_
#define PW_APP_H_

#include <stdbool.h>
#include "i_pw_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the power application.
 */
void power_app_init();

/**
 * @brief Checks for faults in the power application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, PW_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, PW_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, PW_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EPwTaskStatus_t power_app_check_faults();


#endif /* PW_APP_H_ */