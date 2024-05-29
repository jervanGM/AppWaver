#ifndef NETWORK_APP_H_
#define NETWORK_APP_H_

#include <stdbool.h>
#include "i_wireless_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the network application.
 */
void network_app_init();

SNetworkData_t update_app_data(SCtrlWlsMsg_t msg);

/**
 * @brief Checks for faults in the network application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, ANA_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, ANA_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, ANA_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EWlsTaskStatus_t network_app_check_faults();

#endif /* NETWORK_APP_H_ */