/**
 * @file wireless_t_share.h
 * @brief Shared definitions and functions for Wireless tasks.
 */

#ifndef WIRELESS_T_SHARE_H_
#define WIRELESS_T_SHARE_H_

#include <stdbool.h>
#include "i_wireless_data.h"
#include "common_t_data.h"

/**
 * @brief Mutex identifier for Wireless Control tasks.
 */
#define WLS_CTRL_M_ID 2

/**
 * @brief Mutex identifier for Control Wireless tasks.
 */
#define CTRL_WLS_M_ID 3

/**
 * @brief Sets the task information for Wireless tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_wireless_info(SWlsTaskInfo_t task_info);

/**
 * @brief Sets the task status for Wireless tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_wireless_status(EWlsTaskStatus_t status);

/**
 * @brief Sends a command to the Wireless controller.
 * 
 * @param command The command to be sent.
 */
void wireless_controller_send(SWlsCommand_t command);

/**
 * @brief Reads the message from the Wireless controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void wireless_controller_read(SWlsCtrlMsg_t *msg);

/**
 * @brief Sends a structured message to the Wireless controller.
 * 
 * @param alarm The alarms information to send.
 * @param status The system status to send.
 * @param plant_signal The plant signal data and time to send.
 * @param env_data The environmental data to send.
 * @param power_data The power data to send.
 * @param axis_buff The axis buffer adn time data to send.
 * @param current_mode The current system mode to send.
 * @param previous_mode The previous system mode to send.
 * @param system_time The system time to send.
 */
void controller_wireless_send(
    SErrorInfo_t alarm,
    SSystemStatus_t status,
    SPPlantData_t plant_signal,
    SEnvData_t env_data,
    SPowerData_t power_data,
    SAxisData_t axis_buff,
    ESysMode_t current_mode,
    ESysMode_t previous_mode,
    int64_t system_time);

/**
 * @brief Reads the structured message from the Control Wireless module.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void controller_wireless_read(SCtrlWlsMsg_t *msg);

#endif /* WIRELESS_T_SHARE_H_ */
