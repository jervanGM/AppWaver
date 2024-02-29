#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test to verify the initialization error handling of DSP module.
 *
 * This test verifies the behavior of the DSP module when an initialization error occurs.
 * It initializes the DSP port and checks if the proper error code is stored in the error slot.
 */
void test_dsp_init_error(); /**< \test */

/**
 * @brief Test to verify the memory error handling of DSP data retrieval.
 *
 * This test verifies the behavior of the DSP module when a memory error occurs during data retrieval.
 * It attempts to retrieve DSP data and checks if the proper error code is stored in the error slot,
 * and if the retrieved data is set to 0.
 */
void test_dsp_data_memory_error(); /**< \test */
/**
 * @brief Test to verify the initialization of the DSP module.
 *
 * This test verifies the successful initialization of the DSP module.
 * It initializes the error slot, initializes the DSP port, and checks if the error slot remains 0,
 * indicating successful initialization.
 */
void test_dsp_init(); /**< \test */

/**
 * @brief Test to verify data retrieval from the DSP module.
 *
 * This test verifies the proper retrieval of data from the DSP module.
 * It initializes the error slot, sets the ADC value to 27 (simulated data), retrieves DSP data,
 * and checks if the error slot remains 0, indicating successful data retrieval, and if the retrieved data is 3.
 */
void test_dsp_data(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during data filtering.
 *
 * This test verifies the error handling of the DSP module when a null pointer is passed
 * during data filtering. It initializes the error slot, attempts to filter data with a null pointer,
 * and checks if the proper error code is stored in the error slot.
 */
void test_dsp_data_filter_error(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during data normalization with overflow.
 *
 * This test verifies the error handling of the DSP module when the input data exceeds the maximum value
 * during normalization. It initializes the error slot, sets the ADC value to UINT32_MAX (simulated data),
 * retrieves DSP data, and checks if the proper error code is stored in the error slot.
 */
void test_dsp_data_overflow_error(); /**< \test */

/**
 * @brief Test to verify data retrieval from the DSP module with low input.
 *
 * This test verifies the behavior of the DSP module when the input value is low.
 * It sets the ADC value to a low input, retrieves DSP data, and checks if the retrieved data
 * falls within the expected range.
 */
void test_dsp_data_with_low_input(); /**< \test */

/**
 * @brief Test to verify data retrieval from the DSP module with high input.
 *
 * This test verifies the behavior of the DSP module when the input value is high.
 * It sets the ADC value to a high input, retrieves DSP data, and checks if the retrieved data
 * falls within the expected range.
 */
void test_dsp_data_with_high_input(); /**< \test */

/**
 * @brief Test to verify data retrieval from the DSP module with random input.
 *
 * This test verifies the behavior of the DSP module with random input values.
 * It sets random ADC values, retrieves DSP data, and checks if the retrieved data
 * falls within the expected range for multiple iterations.
 */
void test_dsp_data_random_wave(); /**< \test */

#endif /* TRACE_TEST_H_ */