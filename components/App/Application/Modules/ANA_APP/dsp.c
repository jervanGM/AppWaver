#include "dsp.h"
#include "ana_port.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "i_analog_data.h"

static const IAnaPort *ana_port;

/* Initializes the DSP port */
void dsp_init_port()
{
    // Retrieve the analog port interface
    ana_port = hal_ana_get_port();

    // Check if the port interface is valid
    if (ana_port != NULL)
    {
        if(ana_port->init() != ANA_DRV_OK) // Call the initialization function of the analog port
        {   
            store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_INIT_ERROR);
            TRACE_ERROR("A analog sensor task error has been produced during initialization");
            return;          
        }
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
    }
}

/* Retrieves data from the DSP module */
uint32_t get_dsp_data()
{
    uint32_t data;
    // Check if the analog port interface is valid
    if (ana_port != NULL)
    {
        #ifdef BASIC
        if(ana_port->read(2, &data) != ANA_DRV_OK) // Read data from the analog port channel 2
        {   
            store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_ON_READ_ERROR);
            TRACE_ERROR("A analog sensor task error has been produced during reading ADC");
            return 0;          
        }
        #endif
        #ifdef ADVANCED
        if(ana_port->read(0, &data) != ANA_DRV_OK) // Read data from the analog port channel 0
        {   
            store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_ON_READ_ERROR);
            TRACE_ERROR("A analog sensor task error has been produced during reading ADC");
            return 0;          
        }
        #endif
        // Apply filters and normalization
        iir_filter(&data); // Apply IIR filter
        return data;
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
    }
    return 0;
}

/* Applies an IIR filter to the input data */
void iir_filter(uint32_t *input)
{
    static float x[] = {0, 0, 0};
    static float y[] = {0, 0, 0};

    // Check if the input pointer is NULL
    if (input == NULL)
    {
        // Log a warning if the input pointer is NULL
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DSP_IIR_ERROR);
        TRACE_WARNING("Input from dsp filter has no value");
        return;
    }

    // Apply 1 Hz high pass filter
    x[0] = (float)(*input);
    float b[] = {1, -2, 1};
    float a[] = {1.992, -0.915};
    float z = 1.093;
    y[0] = (a[0] * y[1] + a[1] * y[2] +
            b[0] * x[0] + b[1] * x[1] + b[2] * x[2]) /
           z;

    *input = (uint32_t)y[0];
    for (int i = 1; i >= 0; i--)
    {
        x[i + 1] = x[i];
        y[i + 1] = y[i];
    }
}
#ifdef ADVANCED
void get_solar_data(uint32_t *i_solar, uint32_t *v_solar)
{
    uint32_t i_data;
    uint32_t v_data;
    int8_t error = 0;
    // Check if the analog port interface is valid
    if (ana_port != NULL)
    {
        error += ana_port->read(1, &v_data); // Read data from the analog port channel 1
        error += ana_port->read(2, &i_data); // Read data from the analog port channel 1
        if(error != ANA_DRV_OK || i_solar == NULL || v_solar == NULL)
        {
            store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_ON_READ_ERROR);
            TRACE_ERROR("A analog sensor task error has been produced during reading ADC");
            return;  
        }
        *i_solar = i_data;
        *v_solar = v_data;
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
        *i_solar = 0;
        *v_solar = 0;
    }
}

uint32_t get_soil_data()
{
    uint32_t s_data;
    // Check if the analog port interface is valid
    if (ana_port != NULL)
    {
        if(ana_port->read(3, &s_data) != ANA_DRV_OK)
        {
            store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_ON_READ_ERROR);
            TRACE_ERROR("A analog sensor task error has been produced during reading ADC");
            return 0;  
        }
        printf(">soil_data: %d\n",(int)s_data);
        return s_data;
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
    }
    return 0;
}
#endif
