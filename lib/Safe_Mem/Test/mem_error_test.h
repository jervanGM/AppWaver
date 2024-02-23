#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test for storing and reading a value in safe memory.
 *
 * This test stores a value in a memory slot and then reads it back to verify correctness.
 *
 * @post The value is successfully stored and read from memory.
 */
void test_safe_mem_store_value(); /**< \test */

/**
 * @brief Test for storing and reading multiple errors in safe memory.
 *
 * This test stores multiple errors in different slots and then reads them back to verify correctness.
 *
 * @post Multiple errors are successfully stored and read from memory.
 */
void test_safe_mem_multiple_errors(); /**< \test */

/**
 * @brief Test to verify handling of out-of-bounds index when storing an error.
 *
 * This test attempts to store an error at an index outside the valid range and verifies proper error handling.
 *
 * @post An error message is logged when attempting to store an error outside the valid range.
 */
void test_safe_mem_store_error_out_of_bounds(); /**< \test */

/**
 * @brief Test to verify handling of out-of-bounds index when reading an error.
 *
 * This test attempts to read an error from an index outside the valid range and verifies proper error handling.
 *
 * @post An error message is logged when attempting to read an error from an index outside the valid range.
 */
void test_safe_mem_read_error_out_of_bounds(); /**< \test */

/**
 * @brief Test for storing and reading an error at the lower bound of the index range.
 *
 * This test stores an error at the lowest index and then reads it back to verify correctness.
 *
 * @post The error is successfully stored and read from the lowest index.
 */
void test_safe_mem_store_read_error_lower_bound(); /**< \test */

/**
 * @brief Test for storing and reading an error at the upper bound of the index range.
 *
 * This test stores an error at the highest index and then reads it back to verify correctness.
 *
 * @post The error is successfully stored and read from the highest index.
 */
void test_safe_mem_store_read_error_upper_bound(); /**< \test */

/**
 * @brief Test to verify handling of a negative index when storing an error.
 *
 * This test attempts to store an error with a negative index and verifies proper error handling.
 *
 * @post An error message is logged when attempting to store an error with a negative index.
 */
void test_safe_mem_store_error_negative_index(); /**< \test */

/**
 * @brief Test to verify handling of a negative index when reading an error.
 *
 * This test attempts to read an error from a negative index and verifies proper error handling.
 *
 * @post An error message is logged when attempting to read an error from a negative index.
 */
void test_safe_mem_read_error_negative_index(); /**< \test */



#endif /* TRACE_TEST_H_ */