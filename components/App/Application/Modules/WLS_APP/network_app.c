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

SNetworkData_t update_app_data(SCtrlWlsMsg_t msg)
{
    // Variables to store start and end times
    int64_t start_secs = msg._plant_signal.start_time;
    int64_t end_secs = msg._plant_signal.end_time;

    // Static variables to keep track of previous times and data
    static int64_t prev_start_secs = 0;
    static int64_t prev_end_secs = 0;
    static uint8_t size;
    static uint32_t plant_data[DATA_BUFFER_SIZE];

    // Update plant data if times have changed
    if ((prev_start_secs != start_secs) && (prev_end_secs != end_secs))
    {
        memcpy(plant_data, msg._plant_signal.data, DATA_BUFFER_SIZE * sizeof(uint32_t));
    }

    // Update previous start and end times
    prev_start_secs = start_secs;
    prev_end_secs = end_secs;

    // Ensure circular buffer behavior
    if (size >= DATA_BUFFER_SIZE)
        size = 0;

    // Prepare network data structure
    SNetworkData_t network_data;

    // Add actual plant data and serialize it
    network_data.act_plant_data = plant_data[size];
    for (int i = 0; i < DATA_BUFFER_SIZE; i++)
    {
        network_data.serialized_plant_data[i * 4] = (uint8_t)(plant_data[i] & 0xFF);
        network_data.serialized_plant_data[i * 4 + 1] = (uint8_t)((plant_data[i] >> 8) & 0xFF);
        network_data.serialized_plant_data[i * 4 + 2] = (uint8_t)((plant_data[i] >> 16) & 0xFF);
        network_data.serialized_plant_data[i * 4 + 3] = (uint8_t)((plant_data[i] >> 24) & 0xFF);
    }

    // Add plant start and end times
    network_data.plant_time_start = start_secs;
    network_data.plant_time_end = end_secs;

    // Add X axis data and serialize it
    network_data.x_act_data = msg._axis_buff.x[size];
    for (int i = 0; i < DATA_BUFFER_SIZE; i++)
    {
        uint32_t float_bits = *((uint32_t *)&msg._axis_buff.x[i]);
        memcpy(&network_data.serialized_x_data[i * 4], &float_bits, 4);
    }

    // Add Y axis data and serialize it
    network_data.y_act_data = msg._axis_buff.y[size];
    for (int i = 0; i < DATA_BUFFER_SIZE; i++)
    {
        uint32_t float_bits = *((uint32_t *)&msg._axis_buff.y[i]);
        memcpy(&network_data.serialized_y_data[i * 4], &float_bits, 4);
    }

    // Add Z axis data and serialize it
    network_data.z_act_data = msg._axis_buff.z[size];
    for (int i = 0; i < DATA_BUFFER_SIZE; i++)
    {
        uint32_t float_bits = *((uint32_t *)&msg._axis_buff.z[i]);
        memcpy(&network_data.serialized_z_data[i * 4], &float_bits, 4);
    }

    // Add axis start and end times
    network_data.axis_time_start = msg._axis_buff.start_time;
    network_data.axis_time_end = msg._axis_buff.end_time;

    // Add environmental data
    network_data.av_light = msg._env_data.light;
    network_data.av_air_moist = msg._env_data.air_moist;
    network_data.av_soil_moist = msg._env_data.soil_moist;
    network_data.av_sun = msg._env_data.sun;
    network_data.av_temp = msg._env_data.temp;

    // Add current system time
    network_data.current_time = msg._system_time;

    // Increment size for circular buffer
    size++;

    // Return updated network data structure
    return network_data;
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
