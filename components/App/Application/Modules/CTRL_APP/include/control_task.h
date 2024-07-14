#ifndef CONTROL_TASK_H_
#define CONTROL_TASK_H_


/**
 * @brief Task function for the controller task.
 *
 * This function initializes the control task, state machine, and manages control operations
 * based on sensor data and external commands.
 *
 * @param pvParameters Pointer to task parameters
 */
void task_control(void *pvParameters);

/**
 * @brief Initializes the control task.
 *
 * Initializes task ID, delay, last wake time, and status.
 *
 * @param task_info Pointer to control task information structure
 * @param pvParams Pointer to task parameters
 */
void task_control_init(SAnaTaskInfo_t *task_info,void *pvParams);

/**
 * @brief Handler for initialization state in control state machine.
 *
 * Checks for faults during initialization and sets state machine event accordingly.
 */
void on_ctrl_init();

/**
 * @brief Handler for ready state in control state machine.
 *
 * Checks for faults during ready state and sets state machine event accordingly.
 */
void on_ctrl_ready();

/**
 * @brief Handler for execution state in control state machine.
 *
 * Reads sensor data, processes commands, manages power modes, and handles task switching.
 */
void on_ctrl_execute();

/**
 * @brief Handler for breakdown state in control state machine.
 *
 * Handles fault reasons, cleans error memory, and sets state machine event accordingly.
 */
void on_ctrl_breakdown();

#endif /* CONTROL_TASK_H_ */