#include "panic_test.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}
 
// Test function to verify that panic is not executed when condition is true.
void test_assert_panic_not_executed()
{
    // Reset the panic state
    reset_panic();
    // Assert that panic is not executed when the condition is true
    ASSERT_PANIC(true, "PANIC NOT EXECUTED");
    // Check if panic was not executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == false);
}

// Test function to verify that panic is executed when condition is false.
void test_assert_panic_executed()
{
    // Reset the panic state
    reset_panic();
    // Assert that panic is executed when the condition is false
    ASSERT_PANIC(false, "PANIC EXECUTED");
    // Check if panic was executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == true);
}

// Test with empty message
void test_assert_panic_empty_message() {
    // Reset the panic state
    reset_panic();
    // Assert that panic is executed with an empty message
    ASSERT_PANIC(false, "");
    // Check if panic was executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == true);
}

// Test with long message
void test_assert_panic_long_message() {
    // Reset the panic state
    reset_panic();
    // Assert that panic is executed with a long message
    ASSERT_PANIC(false, "This is a long error message to test the maximum length limit of the message.");
    // Check if panic was executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == true);
}

// Test exceeding message length limit
void test_assert_panic_excessive_length_message() {
    // Reset the panic state
    reset_panic();
    // Assert that panic is executed with an excessively long message
    ASSERT_PANIC(false, "This is an extremely long error message that exceeds the maximum length limit allowed.");
    // Check if panic was executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == true);
}

// Performance test
void test_assert_panic_performance() {
    // Reset the panic state
    reset_panic();
    // Perform multiple calls to ASSERT_PANIC in a loop to measure performance
    for (int i = 0; i < 1000000; ++i) {
        ASSERT_PANIC(false, "Test message for a false condition");
    }
    // Check if panic was executed using is_panic_executed() function
    TEST_ASSERT(is_panic_executed() == true);
}

void panic_test_suite()
{
    RUN_TEST(test_assert_panic_not_executed);
    RUN_TEST(test_assert_panic_executed);
    RUN_TEST(test_assert_panic_empty_message);
    RUN_TEST(test_assert_panic_long_message);
    RUN_TEST(test_assert_panic_excessive_length_message);
    RUN_TEST(test_assert_panic_performance);
}