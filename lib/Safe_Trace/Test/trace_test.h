#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"


/**
 * @brief Performs an information trace.
 *
 * This function performs an information trace using TRACE_INFO.
 * It also performs a trace with a specified number.
 *
 * @post The information trace is performed successfully.
 */
void test_safe_trace_info(); /**< \test */

/**
 * @brief Performs a warning trace.
 *
 * This function performs a warning trace using TRACE_WARNING.
 * It also performs a trace with a specified number.
 *
 * @post The warning trace is performed successfully.
 */
void test_safe_trace_warning(); /**< \test */

/**
 * @brief Performs an error trace.
 *
 * This function performs an error trace using TRACE_ERROR.
 * It also performs a trace with a specified number.
 *
 * @post The error trace is performed successfully.
 */
void test_safe_trace_error(); /**< \test */

/**
 * @brief Performs a debug trace.
 *
 * This function performs a debug trace using TRACE_DEBUG.
 * It also performs a trace with a specified number.
 *
 * @post The debug trace is performed successfully.
 */
void test_safe_trace_debug(); /**< \test */

/**
 * @brief Performs an invalid message type trace.
 *
 * This function attempts to perform a trace with an invalid message type.
 *
 * @post It is ensured that the function handles the invalid message type appropriately.
 */
void test_safe_trace_message_type_failure(); /**< \test */

/**
 * @brief Performs a trace with multiple arguments.
 *
 * This function performs a trace with multiple arguments using TRACE_INFO.
 *
 * @post The trace with multiple arguments is performed successfully.
 */
void test_safe_trace_multiple_arguments(); /**< \test */

/**
 * @brief Performs a trace performance test.
 *
 * This function performs multiple calls to TRACE_INFO to evaluate performance.
 *
 * @post The trace performance test is completed successfully.
 */
void test_safe_trace_performance(); /**< \test */

/**
 * @brief Performs a trace concurrency test.
 *
 * This function creates multiple threads to perform concurrent calls to TRACE_INFO.
 *
 * @post The trace concurrency test is completed successfully.
 */
void test_safe_trace_concurrency(); /**< \test */

/**
 * @brief Performs a trace concurrency test.
 *
 * This function creates multiple threads to perform concurrent calls to TRACE_INFO.
 *
 * @post The trace concurrency test is completed successfully.
 */
void* test_safe_trace_concurrent_trace(void* arg); /**< \test */

/**
 * @brief Performs a trace capacity limits test.
 *
 * This function creates multiple threads to perform concurrent calls to safe_trace
 *
 * @post The trace capacity limits test is completed successfully.
 */
void test_safe_trace_capacity_limits(); /**< \test */

/**
 * @brief Performs a trace stress test.
 *
 * This function generates a large number of calls to TRACE_INFO under heavy load.
 *
 * @post The trace stress test is completed successfully.
 */
void test_safe_trace_stress(); /**< \test */



#endif /* TRACE_TEST_H_ */