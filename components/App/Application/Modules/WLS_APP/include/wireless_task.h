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
 * @brief Initialization state execution function.
 *
 * Initializes network components and checks for faults or software updates.
 */
void on_wls_init();

/**
 * @brief Ready state execution function.
 *
 * Connects to the network and checks for faults or software updates.
 */
void on_wls_ready();

/**
 * @brief Operational state execution function.
 *
 * Runs network operations, reads controller messages, updates application data,
 * and updates wireless data objects.
 */
void on_wls_execute();

/**
 * @brief Update state execution function.
 *
 * Deinitializes network components and performs FOTA reboot if necessary.
 */
void on_wls_update();

/**
 * @brief Breakdown state execution function.
 *
 * Handles breakdown scenarios, checks fault reasons, logs faults,
 * cleans error memory, and manages state transitions accordingly.
 */
void on_wls_breakdown();

#endif /* WIRELESS_TASK_H_ */