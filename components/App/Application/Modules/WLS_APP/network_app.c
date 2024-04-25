#include "network_app.h"
#include "safe_memory.h"
#include "firmware_update.h"

static uint8_t size;
static uint32_t plant_data[DATA_BUFFER_SIZE];
/* Initializes the network application */
void network_app_init()
{
    size = 0;
    memset(plant_data, 0, DATA_BUFFER_SIZE * sizeof(uint32_t));
}

void update_app_data(SCtrlWlsMsg_t msg)
{
    if(size == DATA_BUFFER_SIZE)
    {
        memcpy(plant_data, msg._plant_signal, DATA_BUFFER_SIZE * sizeof(uint32_t));
        size = 0;
    }
}

uint32_t get_serialized_plant_data()
{
    return plant_data[size++];
}

/* Checks for faults in the network application */
EWlsTaskStatus_t network_app_check_faults()
{
    int8_t wls_error = 0;
    int8_t ota_error = 0;
    // Read the error from the specified error slot
    wls_error = read_error_from_slot(WIRELESS_ERROR_SLOT);
    ota_error = read_error_from_slot(FOTA_ERROR_SLOT);

    // Determine the task status based on the error value
    if (((wls_error < MINOR_FAULT_THRESHOLD) && (wls_error > MAYOR_FAULT_THESHOLD)) ||
        ((ota_error < MINOR_FAULT_THRESHOLD) && (ota_error > MAYOR_FAULT_THESHOLD)))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return WLS_MINOR_FAULT;
    }
    else if ((wls_error < MAYOR_FAULT_THESHOLD) || (ota_error < MAYOR_FAULT_THESHOLD) )
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return WLS_MAYOR_FAULT;
    }
    else if(wls_error == WLS_DRV_RECONNECT_ERROR)
    {
        return WLS_TASK_RECONNECT_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return WLS_TASK_OK;
    }
}
