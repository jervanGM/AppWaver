#ifndef IND_CODEC_TEST_H_
#define IND_CODEC_TEST_H_

#include "test_suite.h"

/**
 * @brief Test for verifying the handling of port error during DSP module initialization.
 * 
 * This test initializes the DSP module, checks if an initialization error is stored
 * in the designated error slot, and verifies that the error matches the expected code.
 */
void test_handle_port_error(); /**< \test */

/**
 * @brief Test case for initializing the indicator and reading its state.
 * 
 * This test initializes the indicator module, retrieves the IO port,
 * and verifies that reading from the port returns a true value after initialization.
 */
void test_indicator_init(); /**< \test */

/**
 * @brief Test case for setting the indicator state to 'fixed on'.
 * 
 * This test initializes the indicator module, sets the state of a specific indicator
 * to 'fixed on', and verifies that reading from the IO port returns a true value.
 */
void test_indicator_set_state_fix_on(); /**< \test */

/**
 * @brief Test case for setting the indicator state to 'fixed off'.
 * 
 * This test initializes the indicator module, sets the state of a specific indicator
 * to 'fixed off', and verifies that reading from the IO port returns a false value.
 */
void test_indicator_set_state_fix_off(); /**< \test */

#endif /* IND_CODEC_TEST_H_ */
