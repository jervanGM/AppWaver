#include "dsp.h"
#include "ana_port.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "i_analog_data.h"

/* Initializes the DSP port */
void dsp_init_port()
{
    // Retrieve the analog port interface
    const IAnaPort *port = hal_ana_get_port();

    // Check if the port interface is valid
    if (port != NULL)
    {
        port->init(); // Call the initialization function of the analog port
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
    }
}

/* Retrieves data from the DSP module */
uint8_t get_dsp_data()
{
    uint32_t data;
    // Get data from the analog port
    const IAnaPort *port = hal_ana_get_port();

    // Check if the analog port interface is valid
    if (port != NULL)
    {
        port->read(2, &data); // Read data from the analog port channel 2
        // Apply filters and normalization
        iir_filter(&data);                                  // Apply IIR filter
        uint8_t normalized_data = data_normalization(data); // Normalize data
        return normalized_data;
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(ANALOGIC_ERROR_SLOT, HAL_ANA_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on read");
        return 0;
    }
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

/* Normalizes input data */
uint8_t data_normalization(uint32_t input)
{
    // Check if the input value exceeds the threshold
    if (input > MAX_INPUT_VALUE)
    {
        // Log a warning if the input value exceeds the threshold
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DSP_NORMALIZE_ERROR);
        TRACE_WARNING("Input from DSP normalization is higher than the established threshold");
        input = MAX_INPUT_VALUE;
    }

    // Normalize the input data
    uint8_t normalized_data = (uint8_t)(((input - MIN_INPUT_VALUE) *
                                             (NORMALIZED_MAX - NORMALIZED_MIN) +
                                         (MAX_INPUT_VALUE - 1) / 2) /
                                        (MAX_INPUT_VALUE - MIN_INPUT_VALUE));

    return normalized_data;
}
