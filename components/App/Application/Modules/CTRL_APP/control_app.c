#include "control_app.h"
#include "safe_memory.h"
#include <string.h>

/* Initializes the analog application */
void control_app_init()
{
    // Empty implementation as no initialization is currently required.
}

SPPlantData_t control_app_process_plant_data(SAnalogSensMsg_t data_in)
{
    static bool prev_ready = false;
    static SPPlantData_t temp_msg = {0};
    bool ready = data_in._plant_buff.ready;
    size_t buf_size = data_in._plant_buff.size;

    // Process plant data if buffer size is valid and ready status changed
    if ((buf_size > 0) && ready && (ready != prev_ready))
    {
            // Copy valid plant data and associated timestamps
            memcpy(temp_msg.data, data_in._plant_buff.data, buf_size * sizeof(uint32_t));
            memcpy(&temp_msg.start_time, &data_in._buff_time.start_time, sizeof(STemp_t));
            memcpy(&temp_msg.end_time, &data_in._buff_time.end_time, sizeof(STemp_t));
            temp_msg.is_ready = true;

    }
    else{
        temp_msg.is_ready = false;
    }
    
    prev_ready = ready;
    return temp_msg;
}


#ifdef ADVANCED
SEnvData_t control_app_process_env_data(SAnalogSensMsg_t analog_env_data, SBusSensCtrlMsg_t digital_env_data)
{
    SEnvData_t temp_env = {0};

    // Extract relevant environmental data from analog and digital sensor messages
    temp_env.light = analog_env_data._env_data.light_percentage;
    temp_env.soil_moist = analog_env_data._env_data.soil_moist_percentage;
    temp_env.sun = analog_env_data._env_data.direct_sun_percentage;
    temp_env.temp = digital_env_data._temp_data.temperature;
    temp_env.air_moist = digital_env_data._moist_data.moist;

    return temp_env;
}

SAxisData_t control_app_process_acc_data(SBusSensCtrlMsg_t axis_data, SAccItMsg_t it_data)
{
    static SAxisData_t temp_buff = {0};

    // Process accelerometer data if buffer is ready
    if (axis_data._axis_buff.ready)
    {
        // Copy accelerometer data buffers and associated timestamps
        memcpy(temp_buff.x, axis_data._axis_buff.x, DATA_BUFFER_SIZE * sizeof(float));
        memcpy(temp_buff.y, axis_data._axis_buff.y, DATA_BUFFER_SIZE * sizeof(float));
        memcpy(temp_buff.z, axis_data._axis_buff.z, DATA_BUFFER_SIZE * sizeof(float));
        temp_buff.start_time = axis_data._buff_time.start_time;
        temp_buff.end_time = axis_data._buff_time.end_time;
    }

    // Set interrupt flags based on received interrupt command
    temp_buff.it1 = (it_data._int_cmd == ACT_IT1);
    temp_buff.it2 = (it_data._int_cmd == ACT_IT2);

    return temp_buff;
}
#endif

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