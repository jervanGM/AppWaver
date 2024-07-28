#include "dsp.h"
#include "analog_drv.h"
#include "safe_trace.h"
#include "safe_memory.h"

/* Initializes the analog module */
void analog_init()
{
    // Initialize the DSP port
    dsp_init_port();
}

/* Adds a value to the data buffer */
void add_to_buffer(SDataBuffer_t *buffer, SBufferTime_t *time, uint32_t value) {
    // Check if the buffer and time pointers are valid
    if (buffer == NULL || time == NULL) {
        // Log an error if the pointers are null
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_BUFFER_EMPTY);
        TRACE_ERROR("Analog sensor buffer is empty or not valid");
        return;
    }

    // Check for buffer overflow
    if (buffer->size < DATA_BUFFER_SIZE) {
        // Add the value to the buffer
        buffer->data[buffer->size] = value;

        // Update time if the buffer was empty
        if (buffer->size == 0) {
            time->start_time = get_system_time();
        }

        // Check if the buffer is full
        if (buffer->size == DATA_BUFFER_SIZE-1) {
            buffer->ready = true;
            time->end_time = get_system_time();
        }
        buffer->size++;
    }
}

/* Retrieves data from the data buffer */
void get_data_buffer(SDataBuffer_t *data_buffer, SBufferTime_t *data_time) {

    if (data_buffer == NULL || data_time == NULL) {
        // Log an error if the pointers are null
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_BUFFER_EMPTY);
        TRACE_ERROR("Analog sensor buffer is empty or not valid");
        return;
    }

    if (data_buffer->ready) {
        // Clear the data buffer if it's ready
        clear_data_buffer(data_buffer);
    }
    uint32_t data = get_dsp_data();
    data_buffer->instand_data = data;
    data_buffer->instant_time = get_system_time();
    // Add data to the buffer
    add_to_buffer(data_buffer, data_time, data);
}

#ifdef ADVANCED
void get_env_data(uint32_t *env_data, bool ready)
{
    static size_t count = 0;

    uint32_t i_solar, v_solar, s_data;
    if(env_data == NULL)
    {
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_ENV_DATA_EMPTY);
        TRACE_ERROR("Environment data buffer is empty or not valid");
        return;   
    }
    get_solar_data(&i_solar, &v_solar);
    s_data = get_soil_data();
    
    env_data[0] = i_solar;
    env_data[1] = v_solar;
    env_data[2] = s_data;
    
}
#endif

/* Clears the data buffer */
void clear_data_buffer(SDataBuffer_t *buffer) {
    if (buffer == NULL) {
        // Log an error if the pointer is null
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_BUFFER_EMPTY);
        TRACE_ERROR("Analog sensor buffer is empty or not valid");
        return;
    }

    // Reset buffer properties
    buffer->size = 0;
    buffer->ready = false;
}
