#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test the function hal_ana_get_port.
 *
 * This function tests the functionality of the `hal_ana_get_port` function,
 * which retrieves a pointer to the analog port interface.
 */
void test_hal_ana_get_port(void); /**< \test */

/**
 * @brief Test the initialization and reset of the analog port.
 *
 * This function tests the initialization and reset functionalities
 * of the analog port. It initializes the port, checks if the initialization
 * flag is set, resets the port, and verifies if the flag is cleared after reset.
 */
void test_hal_ana_is_init(void); /**< \test */

/**
 * @brief Test the analog port read functionality.
 *
 * This function tests the read functionality of the analog port.
 * It sets a simulated ADC value, reads from the port, and compares
 * the read value with the expected value.
 */
void test_hal_ana_read(void); /**< \test */



#endif /* TRACE_TEST_H_ */