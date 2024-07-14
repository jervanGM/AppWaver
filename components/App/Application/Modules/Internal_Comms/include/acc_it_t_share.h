/**
 * @file acc_it_t_share.h
 * @brief Shared definitions and functions for Accelerometer Interrupt (AccIt) tasks.
 */

#ifndef ACC_IT_T_SHARE_H_
#define ACC_IT_T_SHARE_H_

#include <stdbool.h>
#include "i_acc_it_data.h"

/**
 * @brief Mutex identifier for Accelerometer Interrupt (AccIt) tasks.
 */
#define ACC_IT_M_ID 16

/**
 * @brief Sets the task information for Accelerometer Interrupt (AccIt).
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_acc_it_info(SAccItTaskInfo_t task_info);

/**
 * @brief Sets the task status for Accelerometer Interrupt (AccIt).
 * 
 * @param status The task status to be set.
 */
void set_task_acc_it_status(EAccItTaskStatus_t status);

/**
 * @brief Sends a command and moment for Accelerometer Interrupt (AccIt) controller.
 * 
 * @param int_cmd The interrupt command to be sent.
 * @param it_moment The moment of the interrupt to be sent.
 */
void acc_it_controller_send(EIntCmd_t int_cmd, int64_t it_moment);

/**
 * @brief Reads the message from Accelerometer Interrupt (AccIt) controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void acc_it_controller_read(SAccItMsg_t *msg);

#endif /* ACC_IT_T_SHARE_H_ */
