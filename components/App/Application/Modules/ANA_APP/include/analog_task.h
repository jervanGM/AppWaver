#ifndef ANALOG_TASK_H_
#define ANALOG_TASK_H_


/**
 * @brief Task function responsible for managing the analog task.
 * 
 * This function initializes the analog task and executes the analog state machine in an infinite loop.
 * 
 * @param pvParameters Pointer to task parameters.
 */
void task_analog(void *pvParameters);

/**
 * @brief Initializes the analog task.
 * 
 * @param task_info Pointer to the task information structure.
 * @param pvParams Pointer to task parameters.
 */
void task_analog_init(STaskInfo_t *task_info,void *pvParams);

/**
 * @brief Function executed when the analog state machine is in the initialization state.
 */
void on_ana_init();

/**
 * @brief Function executed when the analog state machine is in the ready state.
 */
void on_ana_ready();

/**
 * @brief Function executed when the analog state machine is in the execute state.
 */
void on_ana_execute();

/**
 * @brief Function executed when the analog state machine is in the breakdown state.
 */
void on_ana_breakdown();


#endif /* ANALOG_TASK_H_ */