#ifndef ACC_IT_APP_H_
#define ACC_IT_APP_H_

#include <stdbool.h>
#include "i_acc_it_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the ACC IT application.
 *
 * This function performs the initialization for the ACC IT application.
 */
void acc_it_app_init();

/**
 * @brief Checks for faults in the ACC IT application.
 *
 * This function reads the error value from a specified error slot and determines
 * the task status based on the error value. It returns different status values
 * depending on the severity of the error.
 *
 * @return The status of the ACC IT task.
 * @retval ACC_IT_MINOR_FAULT if the error is between MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THESHOLD.
 * @retval ACC_IT_MAYOR_FAULT if the error is less than MAYOR_FAULT_THESHOLD.
 * @retval ACC_IT_TASK_OK if no faults are detected.
 */
EAccItTaskStatus_t acc_it_app_check_faults();


#endif /* ACC_IT_APP_H_ */