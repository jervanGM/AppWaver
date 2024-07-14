#ifndef MEM_TASK_H_
#define MEM_TASK_H_

#include "i_mem_data.h"

/**
 * @brief Task function responsible for managing the external memory task.
 * 
 * This function initializes the external memory task and executes the external memory state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_ext_memory(void *pvParameters);

/**
 * @brief Initializes the external memory task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_mem_init(SMemTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Execute function for the initialization state.
 * 
 * This function initializes the memory driver and application, checks for faults,
 * and sets the state machine event based on the initialization status.
 */
void on_mem_init();

/**
 * @brief Execute function for the operational state.
 * 
 * This function reads control messages, processes data to WAV format, saves WAV data if
 * conditions are met, and handles deinitialization based on the power mode.
 */
void on_mem_execute();

/**
 * @brief Execute function for the breakdown state.
 * 
 * This function handles breakdown scenarios, logs fault reasons, cleans error memory,
 * and sets appropriate state machine events.
 */
void on_mem_breakdown();

#endif /* MEM_TASK_H_ */