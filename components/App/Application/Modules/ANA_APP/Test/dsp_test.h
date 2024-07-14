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
 * @brief Test to verify memory error handling when retrieving solar data from DSP module.
 *
 * This test checks the behavior of the DSP module when a memory error occurs during solar data retrieval.
 * It verifies if the error code is stored correctly in the designated error slot and if the retrieved data is zero.
 */
void test_dsp_solar_memory_error(); /**< \test */

/**
 * @brief Test to verify memory error handling when retrieving soil data from DSP module.
 *
 * This test checks the behavior of the DSP module when a memory error occurs during soil data retrieval.
 * It verifies if the error code is stored correctly in the designated error slot and if the retrieved data is zero.
 */
void test_dsp_soil_memory_error(); /**< \test */

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
 * and checks if the error slot remains 0, indicating successful data retrieval, and if the retrieved data is 24.
 */
void test_dsp_data(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during data read operation.
 *
 * This test verifies the error handling of the DSP module when a read error occurs during data retrieval.
 * It initializes the error slot, sets the ADC value, simulates a read error, retrieves DSP data,
 * and checks if the error slot reflects the expected error code and if the retrieved data is 0.
 */
void test_dsp_data_read_error(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during data filtering.
 *
 * This test verifies the error handling of the DSP module when a null pointer is passed
 * during data filtering. It initializes the error slot, attempts to filter data with a null pointer,
 * and checks if the proper error code is stored in the error slot.
 */
void test_dsp_data_filter_error(); /**< \test */

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

/**
 * @brief Test to verify data retrieval of solar data from the DSP module.
 *
 * This test verifies the proper retrieval of solar data from the DSP module.
 * It initializes the error slot, sets the ADC value, retrieves solar data,
 * and checks if the error slot remains 0, and if the retrieved data matches the expected value.
 */
void test_dsp_get_solar_data(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during solar data retrieval.
 *
 * This test verifies the error handling of the DSP module when a read error occurs during solar data retrieval.
 * It initializes the error slot, sets the ADC value, simulates a read error, retrieves solar data,
 * and checks if the error slot reflects the expected error code.
 */
void test_dsp_get_solar_data_read_error(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module when solar data pointers are NULL.
 *
 * This test verifies the error handling of the DSP module when solar data pointers are NULL during data retrieval.
 * It initializes the error slot, sets the ADC value, retrieves solar data with NULL pointers,
 * and checks if the error slot reflects the expected error code.
 */
void test_dsp_get_solar_data_null_error(); /**< \test */

/**
 * @brief Test to verify data retrieval of soil data from the DSP module.
 *
 * This test verifies the proper retrieval of soil data from the DSP module.
 * It initializes the error slot, sets the ADC value, retrieves soil data,
 * and checks if the error slot remains 0, and if the retrieved data matches the expected value.
 */
void test_dsp_get_soil_data(); /**< \test */

/**
 * @brief Test to verify the error handling of the DSP module during soil data retrieval.
 *
 * This test verifies the error handling of the DSP module when a read error occurs during soil data retrieval.
 * It initializes the error slot, sets the ADC value, simulates a read error, retrieves soil data,
 * and checks if the error slot reflects the expected error code.
 */
void test_dsp_get_soil_data_read_error(); /**< \test */

#endif /* TRACE_TEST_H_ */
