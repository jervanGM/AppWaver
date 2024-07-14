#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test for handling pulse in ACC IT.
 *
 * This test verifies the behavior of handling pulses in the ACC IT module.
 * It sets up initial registers and simulates various scenarios such as button presses,
 * threshold readings, and error conditions. Depending on the simulated conditions,
 * it asserts the expected command (`ACT_IT1`, `ACT_IT2`, `ACT_UNK`, or `EV_FAIL`).
 */
void test_acc_it1_handle_pulse(); /**< \test */

/**
 * @brief Test for handling pulse in ACC IT.
 *
 * Similar to `test_acc_it1_handle_pulse`, this test verifies the behavior of handling pulses in the ACC IT module.
 * It sets up initial registers and simulates scenarios specific to INT2.
 * It asserts the expected command (`ACT_IT2`, `ACT_IT1`, `ACT_UNK`, or `EV_FAIL`) depending on the conditions.
 */
void test_acc_it2_handle_pulse(); /**< \test */

/**
 * @brief Test for handling pulse in ACC IT with unknown condition.
 *
 * This test verifies the behavior of handling pulses in the ACC IT module when no specific condition is met.
 * It sets up initial registers and simulates scenarios where no valid pulse condition is detected.
 * It asserts the expected command (`ACT_UNK`).
 */
void test_acc_unk_handle_pulse(); /**< \test */

/**
 * @brief Test for handling read error in INT1 of ACC IT.
 *
 * This test verifies the behavior of the ACC IT module when a read error occurs in INT1.
 * It sets up initial registers and simulates an error condition during register read.
 * It asserts the expected command (`EV_FAIL`).
 */
void test_acc_int1_read_error(); /**< \test */

/**
 * @brief Test for handling exact threshold condition in INT1 of ACC IT.
 *
 * This test verifies the behavior of the ACC IT module when the INT1 register reads exactly at the threshold.
 * It sets up initial registers and simulates the INT1 register reading exactly at the threshold value.
 * It asserts the expected command (`ACT_IT1` or `ACT_UNK` depending on threshold logic).
 */
void test_acc_it1_threshold_exact(); /**< \test */

/**
 * @brief Test for handling exact threshold condition in INT2 of ACC IT.
 *
 * Similar to `test_acc_it1_threshold_exact`, this test verifies the behavior of the ACC IT module
 * when the INT2 register reads exactly at the threshold.
 * It sets up initial registers and simulates the INT2 register reading exactly at the threshold value.
 * It asserts the expected command (`ACT_IT2` or `ACT_UNK` depending on threshold logic).
 */
void test_acc_it2_threshold_exact(); /**< \test */

/**
 * @brief Test for handling combined read and write errors in ACC IT.
 *
 * This test verifies the behavior of the ACC IT module when combined read and write errors occur.
 * It sets up initial registers and simulates scenarios where errors are encountered during register operations.
 * It asserts the expected command (`EV_FAIL`).
 */
void test_acc_combined_read_write_errors(); /**< \test */

/**
 * @brief Test for handling multiple read errors in ACC IT.
 *
 * This test verifies the behavior of the ACC IT module when multiple consecutive read errors occur.
 * It sets up initial registers and simulates scenarios where consecutive read errors are encountered.
 * It asserts the expected command (`EV_FAIL`) and ensures errors are reset properly.
 */
void test_acc_multiple_read_errors(); /**< \test */

#endif /* TRACE_TEST_H_ */
