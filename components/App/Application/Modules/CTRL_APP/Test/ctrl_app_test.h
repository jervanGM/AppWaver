#ifndef CTRL_APP_TEST_H_
#define CTRL_APP_TEST_H_

#include "test_suite.h"

/**
 * @brief Task to test FFT analysis and MFCC coefficient calculation.
 * 
 * This function initializes an FFT configuration, fills its input with random values,
 * performs FFT analysis, computes MFCC coefficients, and validates the results.
 */
void fft_test_task(); /**< \test */

/**
 * @brief Test case to verify the detection of a major fault.
 * 
 * This test sets an error value below the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_controller_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test case to verify the detection of a minor fault.
 * 
 * This test sets an error value above the major fault threshold
 * and below the minor fault threshold and checks if the function
 * correctly identifies it as a minor fault.
 */
void test_controller_app_check_minor_faults(); /**< \test */

/**
 * @brief Test case to verify the absence of faults.
 * 
 * This test sets an error value above the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_controller_app_check_no_faults(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower minor fault boundary.
 * 
 * This test sets an error value equal to the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_controller_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper minor fault boundary.
 * 
 * This test sets an error value one less than the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_controller_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower major fault boundary.
 * 
 * This test sets an error value equal to the major fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_controller_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper major fault boundary.
 * 
 * This test sets an error value to the maximum possible value
 * and checks if the function correctly identifies it as no fault.
 */
void test_controller_app_check_upper_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to process plant data with random values.
 * 
 * This test initializes plant data with random values, processes it using
 * the control application function, and validates that the output matches
 * the input data.
 */
void test_controller_app_process_plant_data_random(); /**< \test */

/**
 * @brief Test case to process plant data with low-level random values.
 * 
 * This test initializes plant data with low-level random values, processes
 * it using the control application function, and validates the output against
 * a comparison array of zeros.
 */
void test_controller_app_process_plant_data_random_low_level(); /**< \test */

/**
 * @brief Test case to process plant data with simulated real-world conditions.
 * 
 * This test initializes plant data with a mix of zeros, low values, and high values,
 * processes it using the control application function, and validates that the output
 * matches the input data.
 */
void test_controller_app_process_plant_data_random_sim_real(); /**< \test */

/**
 * @brief Test case to process plant data with simulated low-level conditions.
 * 
 * This test initializes plant data with a mix of zeros, low values, and lower high values,
 * processes it using the control application function, and validates the output against
 * a comparison array of zeros.
 */
void test_controller_app_process_plant_data_random_sim_low(); /**< \test */

#endif /* CTRL_APP_TEST_H_ */
