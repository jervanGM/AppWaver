#ifndef ANALOG_DRV_H_
#define ANALOG_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_analog_data.h"

void add_to_buffer(SDataBuffer_t *buffer,SBufferTime_t *time, uint8_t value);

void get_data_buffer(SDataBuffer_t *data_buffer,SBufferTime_t *data_time);

void clear_data_buffer(SDataBuffer_t *buffer);

void analog_init();

#endif /* ANALOG_DRV_H_ */