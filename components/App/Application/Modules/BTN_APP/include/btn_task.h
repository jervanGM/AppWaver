#ifndef BTN_TASK_H_
#define BTN_TASK_H_

#include "i_btn_data.h"

/**
 * @brief Task function responsible for managing the button task.
 * 
 * This function initializes the button task and executes the button state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_button(void *pvParameters);

/**
 * @brief Initializes the button task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_btn_init(SBtnTaskInfo_t *task_info);



#endif /* BTN_TASK_H_ */