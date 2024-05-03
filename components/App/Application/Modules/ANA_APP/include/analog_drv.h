#ifndef ANALOG_DRV_H_
#define ANALOG_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_analog_data.h"

/**
 * @brief Initializes the analog module.
 * 
 * This function initializes the analog module by initializing the DSP port.
 */
void analog_init();

/**
 * @brief Adds a value to the data buffer.
 * 
 * This function adds a value to the specified data buffer along with updating
 * the buffer time information. It also checks for buffer overflow conditions.
 * 
 * @param buffer Pointer to the data buffer.
 * @param time Pointer to the buffer time structure.
 * @param value Value to be added to the buffer.
 */
void add_to_buffer(SDataBuffer_t *buffer, SBufferTime_t *time, uint32_t value);

/**
 * @brief Retrieves data from the data buffer.
 * 
 * This function retrieves data from the DSP module, normalizes it, and then
 * adds it to the specified data buffer. If the buffer is full, it clears the
 * buffer before adding new data.
 * 
 * @param data_buffer Pointer to the data buffer.
 * @param data_time Pointer to the buffer time structure.
 */
void get_data_buffer(SDataBuffer_t *data_buffer, SBufferTime_t *data_time);

/**
 * @brief Clears the data buffer.
 * 
 * This function clears the specified data buffer by resetting its size and
 * ready flags.
 * 
 * @param buffer Pointer to the data buffer.
 */
void clear_data_buffer(SDataBuffer_t *buffer);

#endif /* ANALOG_DRV_H_ */