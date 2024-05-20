#include "analog_app.h"
#include "safe_memory.h"

/* Initializes the analog application */
void analog_app_init()
{
    // Empty implementation as no initialization is currently required.
}

static uint8_t percentage_transform(uint32_t x, uint32_t in_min, uint32_t in_max) {
    uint32_t percentage = (x >= in_min) ? ((x - in_min) * (100) / (in_max - in_min)) : 0;
    if(percentage > 100) percentage = 100;
    else {}
    return (uint8_t)percentage;
}

SAnaEnvData_t process_enviromental_data(uint32_t *env_data)
{
    SAnaEnvData_t out_env_data = {0};
    if(env_data == NULL)
    {
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_APP_ENV_DATA_EMPTY);
        TRACE_ERROR("Analog environmental data buffer to process is empty or not valid");
        return out_env_data;
    }
    out_env_data.light_percentage = percentage_transform(env_data[0],MIN_I_SOLAR_VALUE_THRESHOLD,MAX_I_SOLAR_VALUE_THRESHOLD);
    out_env_data.direct_sun_percentage = percentage_transform(env_data[1],MIN_V_SOLAR_VALUE_THRESHOLD,MAX_V_SOLAR_VALUE_THRESHOLD);
    out_env_data.soil_moist_percentage = percentage_transform(env_data[2],MIN_SOIL_MOIST_THRESHOLD,MAX_SOIL_MOIST_THRESHOLD);
    

    return out_env_data;
}

/* Checks for faults in the analog application */
EAnaTaskStatus_t analog_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return ANA_MINOR_FAULT if the error falls within the defined range
        return ANA_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return ANA_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return ANA_MAYOR_FAULT;
    }
    else
    {
        // Return ANA_TASK_OK if no faults are detected
        return ANA_TASK_OK;
    }
}
