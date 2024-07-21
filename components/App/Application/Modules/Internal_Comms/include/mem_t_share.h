/**
 * @file mem_t_share.h
 * @brief Shared definitions and functions for Memory tasks.
 */

#ifndef MEM_T_SHARE_H_
#define MEM_T_SHARE_H_

#include <stdbool.h>
#include "i_mem_data.h"
#include "common_t_data.h"

/**
 * @brief Mutex identifier for Memory Control tasks.
 */
#define MEM_CTRL_M_ID 10

/**
 * @brief Mutex identifier for Control Memory tasks.
 */
#define CTRL_MEM_M_ID 11

/**
 * @brief Sets the task information for external Memory tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_ext_mem_info(SMemTaskInfo_t task_info);

/**
 * @brief Sets the task status for external Memory tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_ext_mem_status(EMemTaskStatus_t status);

/**
 * @brief Reads the message from the Memory control.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void mem_ctrl_read(SMemCtrlMsg_t *msg);

/**
 * @brief Sends the control message to Memory.
 * 
 * @param alarm The alarms information to be sent.
 * @param status The system status to be sent.
 * @param plant_signal The plant signal data and time to be sent.
 * @param env_data The environmental data and time to be sent.
 * @param power_data The power data to be sent.
 * @param axis_buff The axis buffer data to be sent.
 * @param current_mode The current system mode.
 * @param previous_mode The previous system mode.
 * @param system_time The system current time to be sent.
 */
void ctrl_mem_send(
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
 * @brief Reads a message from Control Memory.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void ctrl_mem_read(SCtrlMemMsg_t *msg);

#endif /* MEM_T_SHARE_H_ */