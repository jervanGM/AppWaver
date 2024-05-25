#ifndef CONTROL_APP_H_
#define CONTROL_APP_H_

#include <stdbool.h>
#include "i_control_data.h"

#include "analog_t_share.h"
#include "wireless_t_share.h"
#include "acc_it_t_share.h"
#include "mem_t_share.h"
#include "btn_t_share.h"
#include "pw_t_share.h"
#include "ind_t_share.h"
#include "srl_t_share.h"
#include "bus_t_share.h"
#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

#define DATA_BUFFER_SIZE 128
#define SIGNAL_THRESHOLD 200

/**
 * @brief Initializes the control application.
 */
void control_app_init();

SPPlantData_t control_app_process_plant_data(SAnalogSensMsg_t data_in);

#ifdef ADVANCED
SEnvData_t control_app_process_env_data(SAnalogSensMsg_t analog_env_data, SBusSensCtrlMsg_t digital_env_data);
SAxisData_t control_app_process_acc_data(SBusSensCtrlMsg_t axis_data, SAccItMsg_t it_data);
#endif
/**
 * @brief Checks for faults in the control application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, ANA_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, ANA_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, ANA_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
ECtrlTaskStatus_t control_app_check_faults();

#endif /* CONTROL_APP_H_ */