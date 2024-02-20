#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test function to verify that panic is not executed when condition is true.
 * 
 * This function resets the panic state, asserts that panic is not executed when the condition is true,
 * and checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_not_executed(); /**< \test */

/**
 * @brief Test function to verify that panic is executed when condition is false.
 * 
 * This function resets the panic state, asserts that panic is executed when the condition is false,
 * and checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_executed(); /**< \test */

/**
 * @brief Test function to verify panic behavior with an empty message.
 * 
 * This function resets the panic state, asserts that panic is executed with an empty message,
 * and checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_empty_message(); /**< \test */

/**
 * @brief Test function to verify panic behavior with a long message.
 * 
 * This function resets the panic state, asserts that panic is executed with a long message,
 * and checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_long_message(); /**< \test */

/**
 * @brief Test function to verify panic behavior with an excessively long message.
 * 
 * This function resets the panic state, asserts that panic is executed with an excessively long message,
 * and checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_excessive_length_message(); /**< \test */

/**
 * @brief Test function to measure performance of panic assertion.
 * 
 * This function resets the panic state and performs multiple calls to ASSERT_PANIC in a loop to measure performance.
 * It checks if the panic was executed using is_panic_executed() function.
 */
void test_assert_panic_performance(); /**< \test */


#endif /* TRACE_TEST_H_ */