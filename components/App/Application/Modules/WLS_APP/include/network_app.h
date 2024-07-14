#ifndef NETWORK_APP_H_
#define NETWORK_APP_H_

#include <stdbool.h>
#include "i_wireless_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the network application.
 * 
 * Initializes the network application by resetting data buffers.
 */
void network_app_init();

/**
 * @brief Updates application data based on the received message.
 * 
 * This function updates the application data based on the wireless control message
 * received. It processes plant signal data, axis data, environmental data, and 
 * system time from the provided message and stores them into the `SNetworkData_t`
 * structure.
 * 
 * @param msg Wireless control message containing plant, axis, environmental data,
 * and system time.
 * @return Updated network data structure (`SNetworkData_t`) containing processed data.
 */
SNetworkData_t update_app_data(SCtrlWlsMsg_t msg);

/**
 * @brief Checks for faults in the network application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, WLS_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, WLS_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, WLS_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EWlsTaskStatus_t network_app_check_faults();

#endif /* NETWORK_APP_H_ */