#ifndef CTRL_APP_TEST_H_
#define CTRL_APP_TEST_H_
#include "test_suite.h"

void fft_test_task();

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

void test_controller_app_process_plant_data_random();

void test_controller_app_process_plant_data_random_low_level();

void test_controller_app_process_plant_data_random_sim_real();

void test_controller_app_process_plant_data_random_sim_low();

#endif /* CTRL_APP_TEST_H_ */