#ifndef IND_APP_TEST_H_
#define IND_APP_TEST_H_

#include "test_suite.h"

/**
 * @brief Test case to verify the detection of a major fault.
 * 
 * This test stores an error value below the major fault threshold in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies a major fault.
 */
void test_ind_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test case to verify the detection of a minor fault.
 * 
 * This test stores an error value above the major fault threshold and below the minor fault threshold
 * in the indicator error slot, invokes the function to check faults, and verifies that it correctly
 * identifies a minor fault.
 */
void test_ind_app_check_minor_faults(); /**< \test */

/**
 * @brief Test case to verify the absence of faults.
 * 
 * This test stores an error value above the minor fault threshold in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies no faults.
 */
void test_ind_app_check_no_faults(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower minor fault boundary.
 * 
 * This test stores an error value equal to the minor fault threshold in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies no faults.
 */
void test_ind_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper minor fault boundary.
 * 
 * This test stores an error value one less than the major fault threshold in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies a major fault.
 */
void test_ind_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the lower major fault boundary.
 * 
 * This test stores an error value equal to the major fault threshold in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies no faults.
 */
void test_ind_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test case to verify the behavior at the upper major fault boundary.
 * 
 * This test stores an error value to the maximum possible value in the indicator error slot,
 * invokes the function to check faults, and verifies that it correctly identifies no faults.
 */
void test_ind_app_check_upper_major_fault_boundary(); /**< \test */

#endif /* IND_APP_TEST_H_ */
