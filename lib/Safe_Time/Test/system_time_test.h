#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test case to verify the system time retrieval from hardware.
 * 
 * This test verifies the correct functionality of the system time retrieval 
 * from hardware. It gets the system time at the beginning and end of a 
 * one-second interval using `get_system_time()` and asserts that the difference
 * in seconds is equal to 1.
 */
void test_safe_time_get_hw_time(); /**< \test */

/**
 * @brief Test case to verify the system time retrieval in case of hardware and software fallback.
 * 
 * This test verifies the correct functionality of the system time retrieval 
 * when the hardware time fails and falls back to software time. It gets the
 * system time at the beginning and end of a one-second interval, first without
 * simulating a failure and then simulating a failure to test the fallback to
 * software time. It asserts that the difference in seconds is equal to 1 when
 * hardware time is functional and the system time is reset to 0 when falling
 * back to software time.
 */
void test_safe_time_get_hw_sw_time(); /**< \test */

/**
 * @brief Test case to verify the system time retrieval from software.
 * 
 * This test verifies the correct functionality of the system time retrieval 
 * from software when hardware time is unavailable. It stops the system time
 * and gets the system time repeatedly for 10 iterations, asserting that the
 * time increases by 10 seconds in total.
 */
void test_safe_time_get_sw_time(); /**< \test */


#endif /* TRACE_TEST_H_ */