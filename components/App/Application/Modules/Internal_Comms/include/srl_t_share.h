/**
 * @file srl_t_share.h
 * @brief Shared definitions and functions for Serial tasks.
 */

#ifndef SRL_T_SHARE_H_
#define SRL_T_SHARE_H_

#include <stdbool.h>
#include "i_serial_data.h"

/**
 * @brief Mutex identifier for Serial Control tasks.
 */
#define SRL_CTRL_M_ID 12

/**
 * @brief Mutex identifier for Control Serial tasks.
 */
#define CTRL_SRL_M_ID 13

/**
 * @brief Sets the task information for Serial tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_serial_info(SSrlTaskInfo_t task_info);

/**
 * @brief Sets the task status for Serial tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_serial_status(ESrlTaskStatus_t status);

/**
 * @brief Sets the serial connection status.
 * 
 * @param status The serial connection status to be set.
 */
void set_serial_connection_status(ESrlConnStatus_t status);

/**
 * @brief Sets the serial command.
 * 
 * @param command The serial command to be set.
 */
void set_serial_command(SSerialCmd_t command);

/**
 * @brief Reads the message from the Serial controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void serial_controller_read(SSerialMsg_t *msg);

#endif /* SRL_T_SHARE_H_ */
