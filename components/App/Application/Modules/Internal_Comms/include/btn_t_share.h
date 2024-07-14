/**
 * @file btn_t_share.h
 * @brief Shared definitions and functions for Button controller tasks.
 */

#ifndef BTN_T_SHARE_H_
#define BTN_T_SHARE_H_

#include <stdbool.h>
#include "i_btn_data.h"

/**
 * @brief Mutex identifier for Button controller tasks.
 */
#define BTN_M_ID 4

/**
 * @brief Sets the task information for Button controller tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_button_info(SBtnTaskInfo_t task_info);

/**
 * @brief Sets the task status for Button controller tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_button_status(EBtnTaskStatus_t status);

/**
 * @brief Sends the button command to the Button controller.
 * 
 * @param btn_cmd The button command to be sent.
 */
void button_controller_send(EBtnCmd_t btn_cmd);

/**
 * @brief Reads the message from the Button controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void button_controller_read(SBtnMsg_t *msg);

#endif /* BTN_T_SHARE_H_ */
