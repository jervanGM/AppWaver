#include "dsp.h"
#include "analog_drv.h"


void analog_init()
{
    dsp_init_port();
}

void add_to_buffer(SDataBuffer_t *buffer,SBufferTime_t *time, uint8_t value) {
    if (buffer->size < BUFFER_SIZE) {
        if(buffer->size == 0)
        {
            time->start_time = get_system_time();
        }        
        buffer->data[buffer->size++] = value;
        if (buffer->size == BUFFER_SIZE) {
            buffer->ready = true;
            time->end_time = get_system_time();
        }
    }
}

void get_data_buffer(SDataBuffer_t *data_buffer,SBufferTime_t *data_time) {
    uint8_t data = 0;
    if(data_buffer->ready)
    {
        clear_data_buffer(data_buffer);
    } 
    data = get_dsp_data();
    add_to_buffer(data_buffer,data_time, data);
}

void clear_data_buffer(SDataBuffer_t *buffer)
{
    buffer->size=0;
    buffer->ready = false;
}
