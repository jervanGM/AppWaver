#ifndef PW_APP_TEST_H_
#define PW_APP_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for checking major faults in the power application.
 *
 * This test function simulates a major fault condition and verifies the
 * expected fault status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test function for checking minor faults in the power application.
 *
 * This test function simulates a minor fault condition and verifies the
 * expected fault status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_minor_faults(); /**< \test */

/**
 * @brief Test function for checking no faults in the power application.
 *
 * This test function simulates a normal operation condition and verifies the
 * expected status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_no_faults(); /**< \test */

/**
 * @brief Test function for checking the lower boundary of minor faults.
 *
 * This test function simulates the lower boundary condition of minor faults
 * and verifies the expected status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking the upper boundary of minor faults.
 *
 * This test function simulates the upper boundary condition of minor faults
 * and verifies the expected status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking the lower boundary of major faults.
 *
 * This test function simulates the lower boundary condition of major faults
 * and verifies the expected status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking the upper boundary of major faults.
 *
 * This test function simulates the upper boundary condition of major faults
 * and verifies the expected status returned by `power_app_check_faults()`.
 */
void test_pw_app_check_upper_major_fault_boundary(); /**< \test */

#endif /* PW_APP_TEST_H_ */
