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
 * @brief Initializes the analog task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_wireless_init(SWlsTaskInfo_t *task_info,void *pvParams);




#endif /* WIRELESS_TASK_H_ */