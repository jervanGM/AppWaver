#ifndef ANALOG_DRV_H_
#define ANALOG_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_analog_data.h"

/**
 * @brief Initializes the analog module.
 *
 * This function initializes the DSP port used by the analog module.
 */
void analog_init();

/**
 * @brief Adds a value to the data buffer.
 *
 * This function adds a specified value to the data buffer. It also updates
 * the buffer's size and manages the buffer's time properties.
 *
 * @param[in,out] buffer Pointer to the data buffer structure.
 * @param[in,out] time Pointer to the buffer time structure.
 * @param[in] value The value to be added to the buffer.
 */
void add_to_buffer(SDataBuffer_t *buffer, SBufferTime_t *time, uint32_t value);

/**
 * @brief Retrieves data from the data buffer.
 *
 * This function retrieves data from the data buffer and adds new data from
 * the DSP. If the buffer is ready, it clears the buffer before adding new data.
 *
 * @param[in,out] data_buffer Pointer to the data buffer structure.
 * @param[in,out] data_time Pointer to the buffer time structure.
 */
void get_data_buffer(SDataBuffer_t *data_buffer, SBufferTime_t *data_time);

#ifdef ADVANCED
/**
 * @brief Retrieves environmental data and calculates averages.
 *
 * This function retrieves solar and soil data, accumulates the values,
 * and calculates their averages when the data is ready. If not ready,
 * it returns the previous average values.
 *
 * @param[out] env_data Pointer to the array storing environmental data.
 * @param[in] ready Boolean indicating if the data is ready to be averaged.
 */
void get_env_data(uint32_t *env_data, bool ready);
#endif

/**
 * @brief Clears the data buffer.
 *
 * This function resets the properties of the data buffer, including size and readiness.
 *
 * @param[in,out] buffer Pointer to the data buffer structure.
 */
void clear_data_buffer(SDataBuffer_t *buffer);

#endif // ANALOG_DRV_H