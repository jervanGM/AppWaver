#include "network_app.h"
#include "safe_memory.h"
#include "firmware_update.h"

static uint8_t size;
static uint8_t plant_data[DATA_BUFFER_SIZE];
/* Initializes the network application */
void network_app_init()
{
    size = 0;
    memset(plant_data, 0, DATA_BUFFER_SIZE * sizeof(uint8_t));
}

void update_app_data(SCtrlWlsSensMsg_t msg)
{
    if(size == DATA_BUFFER_SIZE)
    {
        memcpy(plant_data, msg._plant_signal, DATA_BUFFER_SIZE * sizeof(uint8_t));
        size = 0;
    }
}

uint8_t get_serialized_plant_data()
{
    return plant_data[size++];
}

/* Checks for faults in the network application */
EWlsTaskStatus_t network_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(WIRELESS_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return WLS_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return WLS_MAYOR_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return WLS_TASK_OK;
    }
}
