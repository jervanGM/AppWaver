#ifndef SRL_CODEC_TEST_H_
#define SRL_CODEC_TEST_H_

#include "test_suite.h"

/**
 * @brief Test case to verify handling of port initialization error.
 * 
 * This test initializes the serial module and checks if the initialization error
 * is stored in the designated error slot.
 */
void test_handle_port_error(); /**< \test */

/**
 * @brief Test case to verify initialization error handling of the serial codec.
 * 
 * This test sets an initialization error, initializes the serial module, and
 * checks if the error is correctly stored in the designated error slot.
 */
void test_serial_codec_init_error(); /**< \test */

/**
 * @brief Test case to verify deinitialization error handling of the serial codec.
 * 
 * This test sets a deinitialization error, deinitializes the serial module, and
 * checks if the error slot remains unchanged.
 */
void test_serial_codec_deinit_error(); /**< \test */

/**
 * @brief Test case to verify serial connection status.
 * 
 * This test sets and checks the serial connection status.
 */
void test_serial_codec_connection(); /**< \test */

/**
 * @brief Test case to verify correct parsing of serial commands.
 * 
 * This test covers various scenarios of parsing serial commands with and without
 * the --force option and additional text.
 */
void test_serial_codec_correct_msg(); /**< \test */

#endif /* SRL_CODEC_TEST_H_ */
