#ifndef SERIAL_APP_H_
#define SERIAL_APP_H_

#include <stdbool.h>
#include "i_serial_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the serial application.
 */
void serial_app_init();

bool cmd_exist(const char *str);

/**
 * @brief Checks for faults in the serial application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, SRL_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, SRL_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, SRL_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
ESrlTaskStatus_t serial_app_check_faults();


#endif /* SERIAL_APP_H_ */