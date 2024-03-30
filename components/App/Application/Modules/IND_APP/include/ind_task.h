#ifndef IND_TASK_H_
#define IND_TASK_H_

#include "i_ind_data.h"

/**
 * @brief Task function responsible for managing the button task.
 * 
 * This function initializes the button task and executes the button state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_indicator(void *pvParameters);

/**
 * @brief Initializes the button task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_indicator_init(SIndTaskInfo_t *task_info,void *pvParams);



#endif /* IND_TASK_H_ */