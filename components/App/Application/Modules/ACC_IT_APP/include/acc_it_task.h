#ifndef ACC_IT_TASK_H_
#define ACC_IT_TASK_H_

#include "i_acc_it_data.h"

/**
 * @brief Main button task function.
 *
 * This function initializes the task information, verifies the initialization,
 * sets the task information, and initializes the ACC IT application. It then
 * enters an infinite loop where it waits for an event notification, handles
 * the pulse, and sends the information to another task.
 *
 * @param[in] pvParameters Pointer to the task parameters.
 */
void task_acc_it(void *pvParameters);

/**
 * @brief Initializes the ACC IT task.
 *
 * This function sets the task ID and status for the ACC IT task.
 *
 * @param[out] task_info Pointer to the task information structure.
 */
void task_acc_it_init(SAccItTaskInfo_t *task_info);

#endif // TASK_ACC_IT_H