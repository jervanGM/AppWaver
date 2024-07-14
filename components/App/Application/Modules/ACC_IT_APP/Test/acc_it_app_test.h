#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test for checking major faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application when a major fault is detected.
 * It initializes the error slot with a value indicating a major fault, calls the function to check faults,
 * and asserts that the returned fault status matches `ACC_IT_MAYOR_FAULT`.
 */
void test_acc_it_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test for checking minor faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application when a minor fault is detected.
 * It initializes the error slot with a value indicating a minor fault, calls the function to check faults,
 * and asserts that the returned fault status matches `ACC_IT_MINOR_FAULT`.
 */
void test_acc_it_app_check_minor_faults(); /**< \test */

/**
 * @brief Test for checking no faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application when no faults are detected.
 * It initializes the error slot with a value indicating no faults, calls the function to check faults,
 * and asserts that the returned fault status matches `ACC_IT_TASK_OK`.
 */
void test_acc_it_app_check_no_faults(); /**< \test */

/**
 * @brief Test for checking the lower boundary of minor faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application at the lower boundary of minor faults.
 * It initializes the error slot with a value just below the minor fault threshold,
 * calls the function to check faults, and asserts that the returned fault status matches `ACC_IT_TASK_OK`.
 */
void test_acc_it_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test for checking the upper boundary of minor faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application at the upper boundary of minor faults.
 * It initializes the error slot with a value just below the major fault threshold,
 * calls the function to check faults, and asserts that the returned fault status matches `ACC_IT_MAYOR_FAULT`.
 */
void test_acc_it_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test for checking the lower boundary of major faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application at the lower boundary of major faults.
 * It initializes the error slot with a value equal to the major fault threshold,
 * calls the function to check faults, and asserts that the returned fault status matches `ACC_IT_TASK_OK`.
 */
void test_acc_it_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test for checking the upper boundary of major faults in ACC IT application.
 *
 * This test verifies the behavior of the ACC IT application at the upper boundary of major faults.
 * It initializes the error slot with the maximum allowed value (INT8_MAX),
 * calls the function to check faults, and asserts that the returned fault status matches `ACC_IT_TASK_OK`.
 */
void test_acc_it_app_check_upper_major_fault_boundary(); /**< \test */

#endif /* TRACE_TEST_H_ */
