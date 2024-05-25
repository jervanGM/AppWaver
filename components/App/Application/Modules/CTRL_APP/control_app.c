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

SPPlantData_t control_app_process_plant_data(SAnalogSensMsg_t data_in)
{
    static bool prev_ready = false;
    static SPPlantData_t temp_msg;
    bool ready = data_in._plant_buff.ready;
    size_t buf_size = data_in._plant_buff.size;

    if((buf_size > 0) && ready && (ready != prev_ready))
    {
        if(plant_data_is_valid(data_in._plant_buff.data,buf_size))
        {
            memcpy(temp_msg.data,data_in._plant_buff.data,buf_size*sizeof(uint32_t));
            memcpy(&temp_msg.start_time,&data_in._buff_time.start_time,sizeof(STemp_t));
            memcpy(&temp_msg.end_time,&data_in._buff_time.end_time,sizeof(STemp_t));
        }

            // for(uint16_t i = 0;i<buf_size;i++)
            // {
            // TRACE_INFO("PLANT INFO:", TO_STRING(temp_msg._plant_buff.data[i]));
            // }
            // TRACE_INFO("TIME SEC:", TO_STRING(temp_msg._buff_time.start_time.sec));
            // TRACE_INFO("TIME SEC:", TO_STRING(temp_msg._buff_time.end_time.sec));
            // TRACE_INFO("LIGHT PERCENTAGE:", TO_STRING(temp_msg._env_data.light_percentage));
            // TRACE_INFO("SUN PERCENTAGE:", TO_STRING(temp_msg._env_data.direct_sun_percentage));
            // TRACE_INFO("SOIL PERCENTAGE:", TO_STRING(temp_msg._env_data.soil_moist_percentage));
    }
    
    prev_ready = ready;
    return temp_msg;
}


#ifdef ADVANCED
SEnvData_t control_app_process_env_data(SAnalogSensMsg_t analog_env_data, SBusSensCtrlMsg_t digital_env_data)
{
    SEnvData_t temp_env = {0};

    temp_env.light = analog_env_data._env_data.light_percentage;
    temp_env.soil_moist = analog_env_data._env_data.soil_moist_percentage;
    temp_env.sun = analog_env_data._env_data.direct_sun_percentage;
    temp_env.temp = digital_env_data._temp_data.temperature;
    temp_env.air_moist = digital_env_data._moist_data.moist;

    return temp_env;
}

SAxisData_t control_app_process_acc_data(SBusSensCtrlMsg_t axis_data, SAccItMsg_t it_data)
{
    SAxisData_t temp_buff;
    memcpy(temp_buff.x,axis_data._axis_buff.x,DATA_BUFFER_SIZE*sizeof(float));
    memcpy(temp_buff.y,axis_data._axis_buff.y,DATA_BUFFER_SIZE*sizeof(float));
    memcpy(temp_buff.z,axis_data._axis_buff.z,DATA_BUFFER_SIZE*sizeof(float));
    
    temp_buff.it1 = (it_data._int_cmd == ACT_IT1);
    temp_buff.it2 = (it_data._int_cmd == ACT_IT2);

    temp_buff.start_time = axis_data._buff_time.start_time;
    temp_buff.end_time = axis_data._buff_time.end_time;

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