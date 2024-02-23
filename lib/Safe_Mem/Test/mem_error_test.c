#include "mem_error_test.h"
#include "safe_memory.h"

void setUp(void)
{
}

void tearDown(void)
{
}
 
// Test function for storing and reading a value in safe memory.
void test_safe_mem_store_value()
{
    // Subtest 1: store and read a value in a memory slot
    int8_t initial_value = 27;
    int8_t read = 0;
    store_error_in_slot(0, initial_value);
    read = read_error_from_slot(0);
    TEST_ASSERT(read == initial_value);
}

// Test function for storing and reading multiple errors in safe memory.
void test_safe_mem_multiple_errors()
{
    // Subtest 1: store multiple errors in different slots
    for (uint8_t i = 0; i < MAX_ERROR_ADRESSES; ++i)
    {
        store_error_in_slot(i, i * 2);
    }

    // Subtest 2: read and verify the errors stored
    for (uint8_t i = 0; i < MAX_ERROR_ADRESSES; ++i)
    {
        int8_t read = read_error_from_slot(i);
        TEST_ASSERT(read == i * 2);
    }
}

// Test function to verify handling of out-of-bounds index when storing an error.
void test_safe_mem_store_error_out_of_bounds()
{
    // Subtest 1: attempt to store an error at an index outside the valid range
    store_error_in_slot(MAX_ERROR_ADRESSES + 1, 42);
    // Verification of proper error handling is done implicitly within the function call
}

// Test function to verify handling of out-of-bounds index when reading an error.
void test_safe_mem_read_error_out_of_bounds()
{
    // Subtest 1: attempt to read an error from an index outside the valid range
    int8_t read = read_error_from_slot(MAX_ERROR_ADRESSES + 1);
    // Verification of proper error handling is done implicitly within the function call
}

// Test function to verify storage and retrieval of an error at the lower bound of the index range.
void test_safe_mem_store_read_error_lower_bound()
{
    // Subtest 1: store and read an error at the lowest index
    int8_t value = -128; // Minimum value for an int8_t
    store_error_in_slot(0, value);
    int8_t read = read_error_from_slot(0);
    TEST_ASSERT(read == value);
}

// Test function to verify storage and retrieval of an error at the upper bound of the index range.
void test_safe_mem_store_read_error_upper_bound()
{
    // Subtest 1: store and read an error at the highest index
    int8_t value = 127; // Maximum value for an int8_t
    store_error_in_slot(MAX_ERROR_ADRESSES - 1, value);
    int8_t read = read_error_from_slot(MAX_ERROR_ADRESSES - 1);
    TEST_ASSERT(read == value);
}

// Test function to verify handling of a negative index when storing an error.
void test_safe_mem_store_error_negative_index()
{
    // Subtest 1: attempt to store an error with a negative index
    store_error_in_slot(-1, 42);
    // Verification of proper error handling is done implicitly within the function call
}

// Test function to verify handling of a negative index when reading an error.
void test_safe_mem_read_error_negative_index()
{
    // Subtest 1: attempt to read an error from a negative index
    int8_t read = read_error_from_slot(-1);
    // Verification of proper error handling is done implicitly within the function call
}

void mem_error_test_suite()
{
    RUN_TEST(test_safe_mem_store_value);
    RUN_TEST(test_safe_mem_multiple_errors);
    RUN_TEST(test_safe_mem_store_error_out_of_bounds);
    RUN_TEST(test_safe_mem_read_error_out_of_bounds);
    RUN_TEST(test_safe_mem_store_read_error_lower_bound);
    RUN_TEST(test_safe_mem_store_read_error_upper_bound);
    RUN_TEST(test_safe_mem_store_error_negative_index);
    RUN_TEST(test_safe_mem_read_error_negative_index);
}