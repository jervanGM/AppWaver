#ifndef BUS_TASK_H_
#define BUS_TASK_H_

#include "i_bus_data.h"
/**
 * @brief Main function for the bus task.
 *
 * This function initializes the bus task, sets up the bus state machine,
 * and runs an infinite loop to execute the bus state machine at regular intervals.
 *
 * @param pvParameters Pointer to task parameters.
 */
void task_bus(void *pvParameters);

/**
 * @brief Initializes the bus task.
 *
 * This function initializes the bus task information, including ID, delay, last wake time,
 * and status.
 *
 * @param task_info Pointer to the bus task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_bus_init(SBusTaskInfo_t *task_info, void *pvParams);

/**
 * @brief Callback function for the initialization state of the bus state machine.
 *
 * This function initializes bus components and checks for faults.
 */
void on_bus_init();

/**
 * @brief Callback function for the ready state of the bus state machine.
 *
 * This function initializes devices and checks for faults.
 */
void on_bus_ready();

/**
 * @brief Callback function for the operational state of the bus state machine.
 *
 * This function performs data measurement, processing, communication with the controller task,
 * and handles fault checking.
 */
void on_bus_execute();

/**
 * @brief Callback function for the breakdown state of the bus state machine.
 *
 * This function handles fault conditions, logs errors, and cleans error memory.
 */
void on_bus_breakdown();


#endif /* BUS_TASK_H_ */