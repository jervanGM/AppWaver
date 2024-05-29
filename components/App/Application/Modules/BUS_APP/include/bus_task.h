#ifndef BUS_TASK_H_
#define BUS_TASK_H_

#include "i_bus_data.h"
/**
 * @brief Task function responsible for managing the serial task.
 * 
 * This function initializes the serial task and executes the serial state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_bus(void *pvParameters);

/**
 * @brief Initializes the serial task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_bus_init(SBusTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when the serial state machine is in the initialization state.
 */
void on_bus_init();

/**
 * @brief Function executed when the serial state machine is in the ready state.
 */
void on_bus_ready();

/**
 * @brief Function executed when the serial state machine is in the execute state.
 */
void on_bus_execute();

/**
 * @brief Function executed when the serial state machine is in the breakdown state.
 */
void on_bus_breakdown();


#endif /* BUS_TASK_H_ */