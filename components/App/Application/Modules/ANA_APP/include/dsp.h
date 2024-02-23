#ifndef DSP_H_
#define DSP_H_

#include <stdlib.h>
#include "gen_types.h"

/*Normalization parameters*/
#define MAX_INPUT_VALUE 2048
#define MIN_INPUT_VALUE 0
#define NORMALIZED_MIN 0
#define NORMALIZED_MAX 255

/**
 * @brief Initializes the DSP port.
 * 
 * This function initializes the analog port used by the DSP module.
 * It retrieves the analog port interface, checks its validity, and then
 * calls the initialization function of the port.
 * If the port is not properly configured, an error is logged.
 */
void dsp_init_port();

/**
 * @brief Retrieves data from the DSP module.
 * 
 * This function retrieves data from the analog port connected to the DSP module.
 * It reads data from a specific channel of the analog port, applies filters and normalization,
 * and returns the normalized data.
 * If the analog port is not properly configured or if an error occurs during data retrieval,
 * an error is logged and a default value of 0 is returned.
 * 
 * @return Normalized value of the DSP data.
 */
uint8_t get_dsp_data();

/**
 * @brief Applies an IIR filter to the input data.
 * 
 * This function applies a 1Hz high pass Infinite Impulse Response (IIR) filter to the input data.
 * It implements a second-order IIR filter with predefined coefficients.
 * If the input pointer is NULL, an error is logged, and the input value is set to 0.
 * 
 * @param input Pointer to the input data.
 */
void iir_filter(uint32_t *input);

/**
 * @brief Normalizes input data.
 * 
 * This function normalizes input data within a specified range.
 * It ensures that the input data does not exceed the maximum allowed value,
 * and then normalizes it to fit within the specified range.
 * 
 * @param input Input data to be normalized.
 * @return Normalized value.
 */
uint8_t data_normalization(uint32_t input);

#endif /* DSP_H_ */
