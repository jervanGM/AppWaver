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
void add_to_buffer(SDataBuffer_t *buffer, SBufferTime_t *time, uint8_t value) {
    // Check if the buffer and time pointers are valid
    if (buffer == NULL || time == NULL) {
        // Log an error if the pointers are null
        store_error_in_slot(ANALOGIC_ERROR_SLOT, ANA_DRV_BUFFER_EMPTY);
        TRACE_ERROR("Analog sensor buffer is empty or not valid");
        return;
    }

    // Check for buffer overflow
    if (buffer->size < BUFFER_SIZE) {
        // Add the value to the buffer
        buffer->data[buffer->size++] = value;

        // Update time if the buffer was empty
        if (buffer->size == 1) {
            time->start_time = get_system_time();
        }

        // Check if the buffer is full
        if (buffer->size == BUFFER_SIZE) {
            buffer->ready = true;
            time->end_time = get_system_time();
        }
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

    uint8_t data = get_dsp_data();

    // Add data to the buffer
    add_to_buffer(data_buffer, data_time, data);
}

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
