#include "btn_app.h"
#include "safe_memory.h"

EBtnCmd_t btn_cmd;

/* Initializes the button application */
void btn_app_init()
{
    btn_cmd = BTN_CMD_NONE;
}

/* Processes button commands based on pulses */
EBtnCmd_t btn_app_process_cmd(EBtnPulse_t pulse)
{
    switch (pulse)
    {
    case SHORT_PRESS:
        btn_cmd = BTN_CMD_SHORT_PRESS;
        break;
    case LONG_PRESS:
        btn_cmd = BTN_CMD_LONG_PRESS;
        break;
    case POWER_OFF:
        btn_cmd = BTN_CMD_PW_OFF;  // Set command to power off
        break;
    case NO_PULSE:
        btn_cmd = BTN_CMD_NONE;
        break;
    default:
        btn_cmd = BTN_CMD_ERROR;  // Handle unknown pulse
        break;
    }
    return btn_cmd;
}

/* Checks for faults in the button application */
EBtnTaskStatus_t btn_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(BUTTON_ERROR_SLOT);

    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return BTN_MINOR_FAULT if the error falls within the defined range
        return BTN_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return BTN_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return BTN_MAYOR_FAULT;
    }
    else
    {
        // Return BTN_TASK_OK if no faults are detected
        return BTN_TASK_OK;
    }
}