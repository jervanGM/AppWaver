#include "panic_test.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_assert_panic_not_executed()
{
    reset_panic();
    ASSERT_PANIC(true, "PANIC NOT EXECUTED");
    TEST_ASSERT(is_panic_executed() == false);
}

void test_assert_panic_executed()
{
    reset_panic();
    ASSERT_PANIC(false, "PANIC EXECUTED");
    TEST_ASSERT(is_panic_executed() == true);
}

// Test with empty message
void test_assert_panic_empty_message() {
    reset_panic();
    ASSERT_PANIC(false, "");
    TEST_ASSERT(is_panic_executed() == true);
}

// Test with long message
void test_assert_panic_long_message() {
    reset_panic();
    ASSERT_PANIC(false, "This is a long error message to test the maximum length limit of the message.");
    TEST_ASSERT(is_panic_executed() == true);
}

// Test exceeding message length limit
void test_assert_panic_excessive_length_message() {
    reset_panic();
    ASSERT_PANIC(false, "This is an extremely long error message that exceeds the maximum length limit allowed.");
    TEST_ASSERT(is_panic_executed() == true);
}

// Performance test
void test_assert_panic_performance() {
    reset_panic();
    for (int i = 0; i < 1000000; ++i) {
        ASSERT_PANIC(false, "Test message for a false condition");
    }
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