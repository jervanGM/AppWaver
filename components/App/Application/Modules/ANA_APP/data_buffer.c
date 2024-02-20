#include "dsp.h"
#include "data_buffer.h"

void addToBuffer(SDataBuffer_t *buffer, c_uint8_t value) {
    if (buffer->size < BUFFER_SIZE) {
        if(buffer->size == 0)
        {
            buffer->buffer_timestamp.start_time = get_system_time();
        }
        buffer->data[buffer->size++] = value;
        if (buffer->size == BUFFER_SIZE) {
            buffer->ready = true;
            buffer->buffer_timestamp.end_time = get_system_time();
        }
    }
}

SDataBuffer_t getSDataBuffer_t() {
    c_uint8_t data = 0;
    static SDataBuffer_t SDataBuffer_t = { .size = 0, .ready = false };
    if(SDataBuffer_t.ready) clearSDataBuffer_t(&SDataBuffer_t);
    data = getDSPData();
    addToBuffer(&SDataBuffer_t, data);
    return SDataBuffer_t;
}

void clearSDataBuffer_t(SDataBuffer_t *buffer)
{
    buffer->size=0;
    buffer->ready = false;
}
