#ifndef PW_TASK_H_
#define PW_TASK_H_

#include "i_pw_data.h"
/**
 * @brief Task function responsible for managing the power task.
 * 
 * This function initializes the power task and executes the power state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_power(void *pvParameters);

/**
 * @brief Initializes the power task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_pw_init(SPwTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Init state execute function.
 * 
 * Executes actions during the initialization state.
 */
void on_pw_init();

/**
 * @brief Ready state execute function.
 * 
 * Executes actions during the full power state.
 */
void on_pw_full();

/**
 * @brief Operational state execute function.
 * 
 * Executes actions during the low power state.
 */
void on_pw_low();

/**
 * @brief Operational state execute function.
 * 
 * Executes actions during the power off state.
 */
void on_pw_off();

/**
 * @brief Breakdown state execute function.
 * 
 * Executes actions during the breakdown state.
 */
void on_pw_breakdown();


#endif /* PW_TASK_H_ */