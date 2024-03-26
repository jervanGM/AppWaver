#ifndef WIRELESS_TASK_H_
#define WIRELESS_TASK_H_

#include "i_wireless_data.h"

/**
 * @brief Task function responsible for managing the wireless task.
 * 
 * This function initializes the wireless task and executes the wireless state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_wireless(void *pvParameters);

/**
 * @brief Initializes the wireless task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_wireless_init(SWlsTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when the wireless state machine is in the initialization state.
 */
void on_wls_init();

/**
 * @brief Function executed when the wireless state machine is in the ready state.
 */
void on_wls_ready();

/**
 * @brief Function executed when the wireless state machine is in the execute state.
 */
void on_wls_execute();

/**
 * @brief Function executed when the wireless state machine is in the update state.
 */
void on_wls_update();

/**
 * @brief Function executed when the wireless state machine is in the breakdown state.
 */
void on_wls_breakdown();

#endif /* WIRELESS_TASK_H_ */