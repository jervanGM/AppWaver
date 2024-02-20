#ifndef DATA_BUFFER_H_
#define DATA_BUFFER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "safe_timer.h"

#define BUFFER_SIZE 128

typedef struct {
    STime_t start_time;
    STime_t end_time;
} SBufferTime_t;

typedef struct {
    c_uint8_t data[BUFFER_SIZE];
    size_t size;
    SBufferTime_t buffer_timestamp;
    bool ready;
} SDataBuffer_t;

void addToBuffer(SDataBuffer_t *buffer, c_uint8_t value);

SDataBuffer_t getSDataBuffer_t();

void clearSDataBuffer_t(SDataBuffer_t *buffer);

#endif /* DATA_BUFFER_H_ */