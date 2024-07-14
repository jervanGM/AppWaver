#ifndef BTN_APP_H_
#define BTN_APP_H_

#include <stdbool.h>
#include "i_btn_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the button application.
 *
 * This function sets the initial button command to BTN_CMD_NORMAL.
 */
void btn_app_init(void);

/**
 * @brief Processes button commands based on pulses.
 *
 * This function processes the input pulse and updates the button command state machine.
 *
 * @param[in] pulse The input button pulse.
 * @return The updated button command.
 */
EBtnCmd_t btn_app_process_cmd(EBtnPulse_t pulse);

/**
 * @brief Checks for faults in the button application.
 *
 * This function reads the error slot and determines the task status based on the error value.
 *
 * @return The task status based on the error value.
 */
EBtnTaskStatus_t btn_app_check_faults(void);

#endif /* BTN_APP_H_ */