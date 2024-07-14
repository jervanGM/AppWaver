/**
 * @file bus_t_share.h
 * @brief Shared definitions and functions for Bus controller tasks.
 */

#ifndef BUS_T_SHARE_H_
#define BUS_T_SHARE_H_

#include <stdbool.h>
#include "i_bus_data.h"

/**
 * @brief Mutex identifier for Bus controller tasks.
 */
#define BUS_CTRL_M_ID 14

/**
 * @brief Mutex identifier for Controller Bus tasks.
 */
#define CTRL_BUS_M_ID 15

/**
 * @brief Sets the task information for Bus controller tasks.
 * 
 * @param task_info The task information structure to be copied.
 */
void set_task_bus_info(SBusTaskInfo_t task_info);

/**
 * @brief Sets the task status for Bus controller tasks.
 * 
 * @param status The task status to be set.
 */
void set_task_bus_status(EBusTaskStatus_t status);

/**
 * @brief Sends the bus controller message.
 * 
 * @param axis_buff The axis data buffer to be sent.
 * @param temp_data The temperature data to be sent.
 * @param moist_data The moisture data to be sent.
 * @param buff_time The buffer time to be sent.
 */
void bus_controller_send(
    SAxisDataBuffer_t axis_buff,
    STemp_t temp_data,
    SMoist_t moist_data,
    SBufTime_t buff_time
);

/**
 * @brief Reads the message from the Bus controller.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void bus_controller_read(SBusSensCtrlMsg_t *msg);

/**
 * @brief Sends a command to the Controller Bus.
 * 
 * @param dev_id The device ID to which the command is directed.
 * @param cmd The command to be sent.
 */
void controller_bus_send(
    EDevID_t dev_id,
    SDevCmd_t cmd
);

/**
 * @brief Reads a message from the Controller Bus.
 * 
 * @param msg Pointer to the structure where the read message will be copied.
 */
void controller_bus_read(SCtrlBusSensMsg_t *msg);

#endif /* BUS_T_SHARE_H_ */
