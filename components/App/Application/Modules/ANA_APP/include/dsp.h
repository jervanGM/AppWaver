#ifndef DSP_H_
#define DSP_H_

#include <stdlib.h>
#include "gen_types.h"
#include "SERIES_ID.h"

/*Normalization parameters*/
#define MAX_INPUT_VALUE 2048
#define MIN_INPUT_VALUE 0
#define NORMALIZED_MIN 0
#define NORMALIZED_MAX 255

/**
 * @brief Initializes the DSP port.
 *
 * This function retrieves the analog port interface and initializes it. 
 * If the initialization fails, it logs an error.
 */
void dsp_init_port();

/**
 * @brief Retrieves data from the DSP module.
 *
 * This function reads data from a specified analog port channel. It applies
 * filters and normalization to the data. In case of an error, it logs the error
 * and returns 0.
 *
 * @return The processed data from the DSP module.
 */
uint32_t get_dsp_data();

/**
 * @brief Applies an IIR filter to the input data.
 *
 * This function applies a 1 Hz high pass IIR filter to the input data. If the 
 * input pointer is NULL, it logs a warning.
 *
 * @param[in,out] input Pointer to the input data to be filtered.
 */
void iir_filter(uint32_t *input);

#ifdef ADVANCED
/**
 * @brief Retrieves solar data (current and voltage).
 *
 * This function reads the current and voltage data from the analog port. In case of 
 * an error or invalid input pointers, it logs the error and sets the output values to 0.
 *
 * @param[out] i_solar Pointer to store the solar current data.
 * @param[out] v_solar Pointer to store the solar voltage data.
 */
void get_solar_data(uint32_t *i_solar, uint32_t *v_solar);

/**
 * @brief Retrieves soil data.
 *
 * This function reads the soil data from the analog port. In case of an error, it logs 
 * the error and returns 0.
 *
 * @return The soil data.
 */
uint32_t get_soil_data();
#endif

#endif /* DSP_H_ */
