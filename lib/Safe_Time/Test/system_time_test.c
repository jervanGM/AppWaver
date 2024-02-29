#include "system_time_test.h"
#include <windows.h>
#include "safe_timer.h"
#include "hw_tmr_cfg.h"

void setUp(void)
{
}

void tearDown(void)
{

}

// Test function for verifying the system time retrieval from hardware.
void test_safe_time_get_hw_time()
{
    // Get the system time at the beginning of the test
    STime_t time_start = get_system_time();

    // Wait for one second
    Sleep(1000);

    // Get the system time at the end of the test
    STime_t time_end = get_system_time();

    // Assert that the difference in seconds is equal to 1
    TEST_ASSERT_EQUAL((time_end.sec - time_start.sec), 1);
}

// Test function for verifying the system time retrieval in case of hardware and software fallback.
void test_safe_time_get_hw_sw_time()
{
    // Get the system time at the beginning of the test
    STime_t time_start = get_system_time();

    // Wait for one second
    Sleep(1000);

    // Get the system time at the end of the test
    STime_t time_end = get_system_time();

    // Assert that the difference in seconds is equal to 1
    TEST_ASSERT_EQUAL((time_end.sec - time_start.sec), 1);

    // Simulate hardware failure and switch to software time
    set_stop_system_time();

    // Get the system time after switching to software time
    time_end = get_system_time();

    // Assert that the system time is reset to 0 after switching to software time
    TEST_ASSERT_EQUAL(time_end.sec, 0);
}

// Test function for verifying the system time retrieval from software.
void test_safe_time_get_sw_time()
{
    // Variable to store the system time
    STime_t time_end;

    // Stop system time
    set_stop_system_time();

    // Get the system time repeatedly for 10 iterations
    for(int i = 0; i < 10; i++)
    {
        time_end = get_system_time();   
    }

    // Assert that the system time increases by 10 seconds in total
    TEST_ASSERT_EQUAL(time_end.sec, 10);
}


void system_time_test_suite()
{
    RUN_TEST(test_safe_time_get_hw_time);
    RUN_TEST(test_safe_time_get_hw_sw_time);
    RUN_TEST(test_safe_time_get_sw_time);
}