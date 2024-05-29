#ifndef BUS_APP_H_
#define BUS_APP_H_

#include <stdbool.h>
#include "i_bus_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the serial application.
 */
void bus_app_init();

void process_data(uint8_t *raw_data, size_t size);

SAxisDataBuffer_t get_axis_data_buffer();

SBufTime_t get_axis_buffer_time();

STemp_t get_buffer_average_temp();

SMoist_t get_buffer_average_moist();

/**
 * @brief Checks for faults in the serial application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, BUS_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, BUS_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, BUS_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EBusTaskStatus_t bus_app_check_faults();


#endif /* BUS_APP_H_ */