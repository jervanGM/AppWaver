#ifndef PW_TASK_H_
#define PW_TASK_H_

#include "i_pw_data.h"
/**
 * @brief Task function responsible for managing the analog task.
 * 
 * This function initializes the analog task and executes the analog state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_power(void *pvParameters);

/**
 * @brief Initializes the analog task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_pw_init(SPwTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when the analog state machine is in the initialization state.
 */
void on_pw_init();

/**
 * @brief Function executed when the analog state machine is in the ready state.
 */
void on_pw_ready();

/**
 * @brief Function executed when the analog state machine is in the execute state.
 */
void on_pw_execute();

/**
 * @brief Function executed when the analog state machine is in the breakdown state.
 */
void on_pw_breakdown();


#endif /* PW_TASK_H_ */