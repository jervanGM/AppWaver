#ifndef PW_MNG_TEST_H_
#define PW_MNG_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for handling port error during power management initialization.
 *
 * This test initializes the power management module and checks if an error
 * is correctly stored in the designated error slot. It verifies that the error
 * matches the expected configuration error code.
 */
void test_handle_port_error(); /**< \test */

/**
 * @brief Test function for initializing power management module.
 *
 * This test function verifies the initialization of the power management module
 * and checks the initial state of the associated I/O port.
 */
void test_power_init(); /**< \test */

/**
 * @brief Test function for powering off the main power.
 *
 * This test function verifies the behavior of powering off the main power and
 * checks the state of the associated I/O port.
 */
void test_power_off(); /**< \test */

#endif /* PW_MNG_TEST_H_ */
