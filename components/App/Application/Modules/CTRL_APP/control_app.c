#include "control_app.h"
#include "safe_memory.h"
#include <string.h>

/* Initializes the analog application */
void control_app_init()
{
    // Empty implementation as no initialization is currently required.
}

static bool plant_data_is_valid(uint32_t *signal, int length) {
    uint32_t msv = 0.0;

    // Calcula la suma de los cuadrados de los valores absolutos de las muestras
    for (int i = 0; i < length; i++) {
        msv += signal[i] * signal[i];
    }

    // Divide por el número total de muestras para obtener el MSV
    msv /= length;
    if(msv > SIGNAL_THRESHOLD)
    {
        return true;
    }
    return false;
}

void control_app_process_plant_data(uint32_t *data_in,uint32_t *data_out,size_t buf_size,bool ready)
{
    if(buf_size >0 && ready == true)
    {
        if(plant_data_is_valid(data_in,buf_size))
        {
            memcpy(data_out,data_in,buf_size*sizeof(uint32_t));

        }
        else
        {
            memset(data_out, 0, buf_size * sizeof(uint32_t));
        }
        // for(uint16_t i = 0;i<buf_size;i++)
        // {
        //     TRACE_INFO("PLANT INFO:", TO_STRING(data_in[i]));
        // }
        
    }
}

/* Checks for faults in the analog application */
ECtrlTaskStatus_t control_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(CONTROL_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return CTRL_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return CTRL_MAYOR_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return CTRL_TASK_OK;
    }
}