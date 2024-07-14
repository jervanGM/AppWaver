#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test case to verify the detection of a major fault in bus application.
 * 
 * This test sets an error value below the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_bus_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test case to verify the detection of a minor fault in bus application.
 * 
 * This test sets an error value above the major fault threshold
 * and below the minor fault threshold and checks if the function
 * correctly identifies it as a minor fault.
 */
void test_bus_app_check_minor_faults(); /**< \test */

/**
 * @brief Test case to verify the absence of faults in bus application.
 * 
 * This test sets an error value above the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_bus_app_check_no_faults(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower minor fault boundary in bus application.
 * 
 * This test sets an error value equal to the minor fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_bus_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper minor fault boundary in bus application.
 * 
 * This test sets an error value one less than the major fault threshold
 * and checks if the function correctly identifies it as a major fault.
 */
void test_bus_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower major fault boundary in bus application.
 * 
 * This test sets an error value equal to the major fault threshold
 * and checks if the function correctly identifies it as no fault.
 */
void test_bus_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper major fault boundary in bus application.
 * 
 * This test sets an error value to the maximum possible value
 * and checks if the function correctly identifies it as no fault.
 */
void test_bus_app_check_upper_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify data processing in bus application.
 * 
 * This test simulates data processing and verifies the correctness
 * of the processed data buffers and values.
 */
void test_bus_app_process_data(); /**< \test */

/**
 * @brief Test case to verify error handling in data processing in bus application.
 * 
 * This test simulates data processing with NULL data and verifies
 * if the correct error code is set.
 */
void test_bus_app_process_data_error(); /**< \test */

#endif /* TRACE_TEST_H_ */
