#ifndef SERIAL_TASK_H_
#define SERIAL_TASK_H_

#include "i_serial_data.h"
/**
 * @brief Task function responsible for managing the serial task.
 * 
 * This function initializes the serial task and executes the serial state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_serial(void *pvParameters);

/**
 * @brief Initializes the serial task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_serial_init(SSrlTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when entering the initialization state.
 * 
 * Initializes serial components and checks for faults.
 */
void on_srl_init();

/**
 * @brief Function executed when entering the ready state.
 * 
 * Checks for faults and establishes serial connection if available.
 */
void on_srl_ready();

/**
 * @brief Function executed when entering the execution state.
 * 
 * Processes incoming serial command and checks faults.
 */
void on_srl_execute();

/**
 * @brief Function executed when entering the breakdown state.
 * 
 * Handles faults detected during serial task execution.
 */
void on_srl_breakdown();


#endif /* SERIAL_TASK_H_ */