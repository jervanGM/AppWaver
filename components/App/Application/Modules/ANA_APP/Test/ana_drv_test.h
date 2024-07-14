#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test to verify error handling of the data buffer in `get_data_buffer`.
 *
 * This test checks for error conditions when passing NULL pointers to `get_data_buffer`.
 * It verifies that the appropriate error code is logged and stored when the buffer or time pointers are NULL.
 */
void test_ana_drv_data_buffer_error(); /**< \test */

/**
 * @brief Test to verify error handling when adding data to the buffer in `add_to_buffer`.
 *
 * This test verifies the behavior when passing NULL pointers to `add_to_buffer`.
 * It ensures that the appropriate error code is logged and stored when the buffer or time pointers are NULL.
 */
void test_ana_drv_add_data_buffer_error(); /**< \test */

/**
 * @brief Test to verify error handling when clearing the buffer in `clear_data_buffer`.
 *
 * This test checks the behavior when passing a NULL pointer to `clear_data_buffer`.
 * It ensures that the appropriate error code is logged and stored when the data buffer pointer is NULL.
 */
void test_ana_drv_clean_data_buffer_error(); /**< \test */

/**
 * @brief Test to verify the correct functionality of `get_data_buffer`.
 *
 * This test validates the behavior of `get_data_buffer` under normal operating conditions.
 * It ensures that the buffer is populated correctly with data from the DSP and the time stamps are updated accordingly.
 */
void test_get_data_buffer(); /**< \test */

/**
 * @brief Test to verify the behavior of `get_data_buffer` when clearing the buffer.
 *
 * This test checks the behavior of `get_data_buffer` after the buffer has been cleared.
 * It ensures that the buffer remains empty and the time stamps are reset after clearing.
 */
void test_get_data_clean_buffer(); /**< \test */

/**
 * @brief Test to verify the behavior of `get_data_buffer` with a random wave input.
 *
 * This test validates the behavior of `get_data_buffer` when receiving random wave input data.
 * It ensures that the buffer is filled with the correct number of samples, and the time stamps reflect the start and end times appropriately.
 */
void test_get_data_buffer_random_wave(); /**< \test */

/**
 * @brief Test for verifying environmental data retrieval.
 *
 * This test validates the `get_env_data` function under normal conditions.
 */
void test_ana_drv_get_env_data(); /**< \test */

/**
 * @brief Test for handling error when environmental data pointer is NULL.
 *
 * This test verifies error handling in `get_env_data` when the environmental data pointer is NULL.
 */
void test_ana_drv_get_env_data_null(); /**< \test */

#endif /* TRACE_TEST_H_ */
