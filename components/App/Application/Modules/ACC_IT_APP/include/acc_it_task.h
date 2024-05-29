#ifndef ACC_IT_TASK_H_
#define ACC_IT_TASK_H_

#include "i_acc_it_data.h"

/**
 * @brief Task function responsible for managing the button task.
 * 
 * This function initializes the button task and executes the button state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_acc_it(void *pvParameters);

/**
 * @brief Initializes the button task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_acc_it_init(SAccItTaskInfo_t *task_info);



#endif /* ACC_IT_TASK_H_ */