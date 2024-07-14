#ifndef BUS_APP_H_
#define BUS_APP_H_

#include <stdbool.h>
#include "i_bus_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the bus application.
 */
void bus_app_init();

/**
 * @brief Processes raw data received from the bus.
 *
 * This function processes raw data from a bus interface, calculates temperature,
 * moisture, accelerometer data, and ADC values, and stores them in respective buffers.
 *
 * @param[in] raw_data Pointer to the raw data buffer.
 * @param[in] size Size of the raw data buffer.
 */
void process_data(uint8_t *raw_data, size_t size);

/**
 * @brief Retrieves the axis data buffer.
 *
 * @return The current axis data buffer.
 */
SAxisDataBuffer_t get_axis_data_buffer();

/**
 * @brief Retrieves the time information of the axis data buffer.
 *
 * @return The time information of the axis data buffer.
 */
SBufTime_t get_axis_buffer_time();

/**
 * @brief Retrieves the average temperature data from the buffer.
 *
 * @return The average temperature data.
 */
STemp_t get_buffer_average_temp();

/**
 * @brief Retrieves the average moisture data from the buffer.
 *
 * @return The average moisture data.
 */
SMoist_t get_buffer_average_moist();

/**
 * @brief Checks for faults in the bus application.
 *
 * @return The status of the bus task.
 */
EBusTaskStatus_t bus_app_check_faults();


#endif /* BUS_APP_H_ */