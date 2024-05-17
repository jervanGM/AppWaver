#include "serial_app.h"
#include "safe_memory.h"
#include <string.h>

/* Initializes the serial application */

const char *srl_cmd_list[] = {
    "system_off",
    "system_on",
    "system_reset", //FUNCTIONALITY TBD
    "wifi_off", //FUNCTIONALITY TBD
    "wifi_on", //FUNCTIONALITY TBD
    "act_wls_task", //FUNCTIONALITY TBD
    "deact_wls_task", //FUNCTIONALITY TBD
    "act_sd_task", //FUNCTIONALITY TBD
    "deact_sd_task" //FUNCTIONALITY TBD
};

void serial_app_init()
{

}

bool cmd_exist(const char *str) 
{
    if(str != NULL)
    {
        for (int i = 0; i < sizeof(srl_cmd_list) / sizeof(srl_cmd_list[0]); i++) {
            if (strcmp(str, srl_cmd_list[i]) == 0) {
                return true;
            }
        }
        strcpy((char *)str, "cmd_none");
    }
    else
    {
        TRACE_WARNING("Cannot process a null serial command, instead the command will be processed as none");
    }
    return false;
}

/* Checks for faults in the serial application */
ESrlTaskStatus_t serial_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(SERIAL_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return SRL_MINOR_FAULT if the error falls within the defined range
        return SRL_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return SRL_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return SRL_MAYOR_FAULT;
    }
    else
    {
        // Return SRL_TASK_OK if no faults are detected
        return SRL_TASK_OK;
    }
}
