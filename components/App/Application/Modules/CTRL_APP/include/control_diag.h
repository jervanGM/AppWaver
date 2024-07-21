#ifndef CONTROL_DIAG_H_
#define CONTROL_DIAG_H_

#include <stdbool.h>
#include "i_control_data.h"
#include "control_task.h"
#include "analog_t_share.h"
#include "wireless_t_share.h"
#include "mem_t_share.h"
#include "bus_t_share.h"
#include "btn_t_share.h"
#include "pw_t_share.h"
#include "ind_t_share.h"
#include "srl_t_share.h"

/**
 * @brief Processes the change in control task based on wireless and memory status.
 *
 * This function determines the active control task based on the status of wireless (wls_status)
 * and memory (mem_status). It handles task switching and timer management.
 *
 * @param wls_status Wireless status
 * @param mem_status Memory status
 * @return Active control task after processing
 */
ECtrlTaskAct_t control_diag_process_change_task(EWlsTaskStatus_t wls_status,EMemTaskStatus_t mem_status);

#ifdef ADVANCED
/**
 * @brief Processes the bus command based on temperature and moisture readings.
 *
 * This function generates a control message for the bus sensor based on temperature and moisture
 * values. If temperature is below 20°C and moisture is above 70%, it sets a medium heater command
 * for the temperature and humidity sensor.
 *
 * @param temp Temperature structure containing temperature readings
 * @param moist Moisture structure containing moisture readings
 * @return Control message for bus sensor
 */
SCtrlBusSensMsg_t control_diag_process_bus_cmd(STemp_t temp, SMoist_t moist);
#endif

#endif /* CONTROL_DIAG_H_ */