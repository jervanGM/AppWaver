/**
 * @file ind_t_share.h
 * @brief Shared definitions and functions for Indicator tasks.
 */

#ifndef IND_T_SHARE_H_
#define IND_T_SHARE_H_

#include <stdbool.h>
#include "i_ind_data.h"

/**
 * @brief Mutex identifier for Control Indicator tasks.
 */
#define CTRL_IND_M_ID 6

/**
 * @brief Mutex identifier for Indicator Control tasks.
 */
#define IND_CTRL_M_ID 7

/**
 * @brief Sets the task information for Indicator tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_indicator_info(SIndTaskInfo_t task_info);

/**
 * @brief Sets the task status for Indicator tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_indicator_status(EIndTaskStatus_t status);

/**
 * @brief Reads the message from the Indicator control.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void ind_ctrl_read(SIndCtrlMsg_t *msg);

/**
 * @brief Sends the indicator control message.
 * 
 * @param ind_id The indicator ID to which the state command is directed.
 * @param ind_state The state of the indicator to be set.
 */
void ctrl_ind_send(EIndId_t ind_id, EIndSts_t ind_state);

/**
 * @brief Reads a message from the Control Indicator.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void ctrl_ind_read(SCtrlIndMsg_t *msg);

#endif /* IND_T_SHARE_H_ */
