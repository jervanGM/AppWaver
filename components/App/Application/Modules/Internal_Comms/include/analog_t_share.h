/**
 * @file analog_t_share.h
 * @brief Shared definitions and functions for Analog sensor tasks.
 */

#ifndef ANALOG_T_SHARE_H_
#define ANALOG_T_SHARE_H_

#include <stdbool.h>
#include "i_analog_data.h"

/**
 * @brief Mutex identifier for Analog sensor tasks.
 */
#define ANALOG_M_ID 0

/**
 * @brief Mutex identifier for Analog sensor tasks in controller context.
 */
#define CTRL_ANALOG_M_ID 1

/**
 * @brief Sets the task information to Analog sensor tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_analog_info(SAnaTaskInfo_t task_info);

/**
 * @brief Sets the task status to Analog sensor tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_analog_status(EAnaTaskStatus_t status);

/**
 * @brief Sends the plant buffer and buffer time to Analog sensor controller.
 * 
 * @param plant_buff The plant buffer data to be sent.
 * @param buff_time The buffer time data to be sent.
 */
void analog_controller_send(SDataBuffer_t plant_buff, SBufferTime_t buff_time);

#ifdef ADVANCED
/**
 * @brief Sends environmental data to Analog sensor controller (Advanced version).
 * 
 * @param env_data The environmental data to be sent.
 */
void analog_controller_send_env_data(SAnaEnvData_t env_data);
#endif

/**
 * @brief Reads the message from Analog sensor controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void analog_controller_read(SAnalogSensMsg_t *msg);

#endif /* ANALOG_T_SHARE_H_ */
