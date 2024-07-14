#include "btn_app.h"
#include "safe_memory.h"

EBtnCmd_t btn_cmd;

/* Handles short press state machine transitions */
static void short_press_sm(void);

/* Handles long press state machine transitions */
static void long_press_sm(void);

/* Initializes the button application */
void btn_app_init()
{
    btn_cmd = BTN_CMD_NORMAL;
}

/* Processes button commands based on pulses */
EBtnCmd_t btn_app_process_cmd(EBtnPulse_t pulse)
{
    switch (pulse)
    {
    case SHORT_PRESS:
        short_press_sm();  // Handle short press
        break;
    case LONG_PRESS:
        long_press_sm();  // Handle long press
        break;
    case POWER_OFF:
        btn_cmd = BTN_CMD_PW_OFF;  // Set command to power off
        break;
    case NO_PULSE:
        // Do nothing if there is no pulse
        break;
    default:
        btn_cmd = BTN_CMD_ERROR;  // Handle unknown pulse
        break;
    }
    return btn_cmd;
}

/* Handles short press state machine transitions */
static void short_press_sm()
{
    switch (btn_cmd)
    {
    case BTN_CMD_NORMAL:
        btn_cmd = BTN_CMD_MODE1;
        break;
    case BTN_CMD_MODE1:
        btn_cmd = BTN_CMD_MODE2;
        break;
    case BTN_CMD_MODE2:
        btn_cmd = BTN_CMD_MODE3;
        break;
    default:
        btn_cmd = BTN_CMD_NORMAL;
        break;
    }
}

/* Handles long press state machine transitions */
static void long_press_sm()
{
    switch (btn_cmd)
    {
    case BTN_CMD_NORMAL:
        btn_cmd = BTN_CMD_LONG1;
        break;
    default:
        btn_cmd = BTN_CMD_NORMAL;
        break;
    }
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