/**
 * @file test_suite.h
 * @brief Header file containing functions for running test suites.
 */

#ifndef TEST_SUITE_H
#define TEST_SUITE_H
#include "unity.h"

/**
 * @brief Run the test suite.
 *
 * This function runs all the test defined for this test suite.
 */
extern void ev_handler_test_suite();

/**
 * @brief Run the test suite.
 *
 * This function runs all the test defined for this test suite.
 */
extern void acc_it_app_test_suite();

/**
 * @brief Run the test suite.
 *
 * This function runs all the test defined for this test suite.
 */
extern void acc_it_task_test_suite();

/**
 * @brief Set up function.
 *
 * This function is called before each test case.
 */
extern void setUp(void);

/**
 * @brief Tear down function.
 *
 * This function is called after each test case.
 */
extern void tearDown(void);

/**
 * @brief Run the test suites.
 *
 * This function runs the test suites by calling `dsp_test_suite()`,`ana_drv_test_suite()`
 * ,`ana_sm_test_suite()`,`ana_app_test_suite()`,`ana_task_test_suite()`.
 */
static inline void run_test_suites()
{
    ev_handler_test_suite();
    acc_it_app_test_suite();
    acc_it_task_test_suite();
}

/**
 * @def UNITY_TEST_RESET()
 * @brief Macro to reset test environment.
 *
 * This macro defines a function `resetTest()` that resets the test environment by calling `tearDown()` and `setUp()`.
 */
#define UNITY_TEST_RESET() \
    void resetTest(void) \
    {   \
        tearDown(); \
        setUp();    \
    }

/**
 * @def UNITY_TEST_SUITE()
 * @brief Macro to define the main function for running test suites.
 *
 * This macro defines the `main()` function which begins the test execution, runs the test suites,
 * and returns the test results.
 */
#define UNITY_TEST_SUITE() \
    int main() { \
        UNITY_BEGIN(); \
        run_test_suites(); \
        return UNITY_END(); \
    }

#endif /* TEST_SUITE_H */
