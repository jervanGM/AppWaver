#ifndef BTN_APP_H_
#define BTN_APP_H_

#include <stdbool.h>
#include "i_btn_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the analog application.
 */
void btn_app_init();

EBtnCmd_t btn_app_process_cmd(EBtnPulse_t pulse);

/**
 * @brief Checks for faults in the analog application.
 * 
 * This function reads the error from the specified error slot and determines the task status based on the error value.
 * If the error falls within the range defined by MINOR_FAULT_THRESHOLD and MAYOR_FAULT_THRESHOLD, ANA_MINOR_FAULT is returned.
 * If the error is less than MAYOR_FAULT_THRESHOLD, ANA_MAYOR_FAULT is returned.
 * If the error is greater than or equal to MAYOR_FAULT_THRESHOLD, ANA_TASK_OK is returned.
 * 
 * @return The task status indicating the severity of faults.
 */
EBtnTaskStatus_t btn_app_check_faults();


#endif /* BTN_APP_H_ */