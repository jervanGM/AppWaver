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
 * @brief Initializes the analog application.
 *
 * This function initializes the analog application. Currently, no initialization is required.
 */
void control_app_init();

/**
 * @brief Processes plant data received from analog sensors.
 *
 * This function validates plant data and returns processed plant data.
 *
 * @param data_in Analog sensor message containing plant data.
 * @return Processed plant data structure.
 */
SPPlantData_t control_app_process_plant_data(SAnalogSensMsg_t data_in);

#ifdef ADVANCED
/**
 * @brief Processes environmental data received from analog and digital sensors.
 *
 * This function processes environmental data and returns the processed environment data structure.
 *
 * @param analog_env_data Analog sensor message containing environmental data.
 * @param digital_env_data Digital sensor message containing environmental data.
 * @return Processed environment data structure.
 */
SEnvData_t control_app_process_env_data(SAnalogSensMsg_t analog_env_data, SBusSensCtrlMsg_t digital_env_data);

/**
 * @brief Processes accelerometer data received from bus sensor control messages.
 *
 * This function processes accelerometer data and returns the processed accelerometer data structure.
 *
 * @param axis_data Bus sensor control message containing accelerometer data.
 * @param it_data Interrupt data message.
 * @return Processed accelerometer data structure.
 */
SAxisData_t control_app_process_acc_data(SBusSensCtrlMsg_t axis_data, SAccItMsg_t it_data);
#endif

/**
 * @brief Checks for faults in the analog application.
 *
 * This function reads the error from the specified error slot and determines the task status
 * based on the error value.
 *
 * @return Status of the control task based on fault detection.
 */
ECtrlTaskStatus_t control_app_check_faults();

#endif /* CONTROL_APP_H_ */