/**
 * @file pw_t_share.h
 * @brief Shared definitions and functions for Power tasks.
 */

#ifndef PW_T_SHARE_H_
#define PW_T_SHARE_H_

#include <stdbool.h>
#include "i_pw_data.h"

/**
 * @brief Mutex identifier for Power Control tasks.
 */
#define CTRL_PW_M_ID 8

/**
 * @brief Mutex identifier for Control Power tasks.
 */
#define PW_CTRL_M_ID 9

/**
 * @brief Sets the task information for Power tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_power_info(SPwTaskInfo_t task_info);

/**
 * @brief Sets the task status for Power tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_power_status(EPwTaskStatus_t status);

/**
 * @brief Reads the message from the Power control.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void pw_ctrl_read(SPwCtrlMsg_t *msg);

/**
 * @brief Sends the control message to Power.
 * 
 * @param sens_sw_sts The sensor switch status to be sent.
 * @param main_sw_sts The main switch status to be sent.
 * @param soil_act_sts The soil sensor activation status to be sent.
 * @param wifi_act_sts The WiFi module activation status to be sent.
 * @param pw_mode The system power mode to be sent.
 */
void ctrl_pw_send(
    ESensSwSts_t sens_sw_sts,
    EMainSwSts_t main_sw_sts,
    ESoilActSts_t soil_act_sts,
    EWifiActSts_t wifi_act_sts,
    EPwMode_t pw_mode);

/**
 * @brief Reads a message from Control Power.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void ctrl_pw_read(SCtrlPwMsg_t *msg);

#endif /* PW_T_SHARE_H_ */