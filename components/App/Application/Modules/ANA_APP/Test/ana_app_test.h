#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_

#include "test_suite.h"

/**
 * @brief Test case to verify the detection of a major fault.
 * 
 * This test sets an error value below the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_analog_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test case to verify the detection of a minor fault.
 * 
 * This test sets an error value above the major fault threshold
 * and below the minor fault threshold and checks if the function
 * correctly identifies it as a minor fault.
 */
void test_analog_app_check_minor_faults(); /**< \test */

/**
 * @brief Test case to verify the absence of faults.
 * 
 * This test sets an error value above the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_analog_app_check_no_faults(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower minor fault boundary.
 * 
 * This test sets an error value equal to the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_analog_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper minor fault boundary.
 * 
 * This test sets an error value one less than the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_analog_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower major fault boundary.
 * 
 * This test sets an error value equal to the major fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_analog_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper major fault boundary.
 * 
 * This test sets an error value to the maximum possible value
 * and checks if the function correctly identifies it as no fault.
 */
void test_analog_app_check_upper_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the processing of environmental data.
 * 
 * This test processes environmental data and checks if the
 * function correctly processes the data.
 */
void test_analog_app_process_enviromental_data(); /**< \test */

/**
 * @brief Test case to verify the processing of null environmental data.
 * 
 * This test processes null environmental data and checks if the
 * function correctly handles null data.
 */
void test_analog_app_process_null_enviromental_data(); /**< \test */

/**
 * @brief Test case to verify the processing of environmental data with maximum values.
 * 
 * This test processes environmental data with maximum values and checks if the
 * function correctly processes the data.
 */
void test_analog_app_process_enviromental_data_max_values(); /**< \test */

/**
 * @brief Test case to verify the processing of environmental data within maximum limits.
 * 
 * This test processes environmental data within maximum limits and checks if the
 * function correctly processes the data.
 */
void test_analog_app_process_enviromental_data_max_limits(); /**< \test */

/**
 * @brief Test case to verify the processing of environmental data with minimum values.
 * 
 * This test processes environmental data with minimum values and checks if the
 * function correctly processes the data.
 */
void test_analog_app_process_enviromental_data_min_values(); /**< \test */

/**
 * @brief Test case to verify the processing of environmental data within minimum limits.
 * 
 * This test processes environmental data within minimum limits and checks if the
 * function correctly processes the data.
 */
void test_analog_app_process_enviromental_data_min_limits(); /**< \test */

#endif /* TRACE_TEST_H_ */
