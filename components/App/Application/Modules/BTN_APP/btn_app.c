#include "btn_app.h"
#include "safe_memory.h"

EBtnCmd_t btn_cmd;

static void short_press_sm(void);

static void long_press_sm(void);

void btn_app_init()
{
    btn_cmd = BTN_CMD_NORMAL;
}

EBtnCmd_t btn_app_process_cmd(EBtnPulse_t pulse)
{
    switch (pulse)
    {
    case SHORT_PRESS:
        short_press_sm();
        break;
    case LONG_PRESS:
        long_press_sm();
        break;
    case POWER_OFF:
        btn_cmd = BTN_CMD_PW_OFF;
        break;
    case NO_PULSE:
        //Do nothing.
        break;
    default:
        btn_cmd = BTN_CMD_ERROR;
        break;
    }
    return btn_cmd;
}

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

EBtnTaskStatus_t btn_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(BUTTON_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return BTN_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return BTN_MAYOR_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return BTN_TASK_OK;
    }
}