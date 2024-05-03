#include "pw_app.h"
#include "safe_memory.h"

/* Initializes the analog application */
void power_app_init()
{
    // Empty implementation as no initialization is currently required.
}

/* Checks for faults in the analog application */
EPwTaskStatus_t power_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(POWER_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return PW_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return PW_MAYOR_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return PW_TASK_OK;
    }
}
