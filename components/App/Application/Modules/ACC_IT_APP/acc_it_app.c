#include "acc_it_app.h"
#include "safe_memory.h"

void acc_it_app_init()
{

}

EAccItTaskStatus_t acc_it_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(ACC_IT_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ACC_IT_MINOR_FAULT if the error falls within the defined range
        return ACC_IT_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ACC_IT_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return ACC_IT_MAYOR_FAULT;
    }
    else
    {
        // Return ACC_IT_TASK_OK if no faults are detected
        return ACC_IT_TASK_OK;
    }
}