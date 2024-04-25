#ifndef MEM_TASK_H_
#define MEM_TASK_H_

#include "i_mem_data.h"

/**
 * @brief Task function responsible for managing the button task.
 * 
 * This function initializes the button task and executes the button state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_ext_memory(void *pvParameters);

/**
 * @brief Initializes the button task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_mem_init(SMemTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when the external memory state machine is in the initialization state.
 */
void on_mem_init();

/**
 * @brief Function executed when the external memory state machine is in the execute state.
 */
void on_mem_execute();

/**
 * @brief Function executed when the external memory state machine is in the breakdown state.
 */
void on_mem_breakdown();

#endif /* MEM_TASK_H_ */