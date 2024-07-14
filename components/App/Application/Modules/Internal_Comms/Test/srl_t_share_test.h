#ifndef SRL_T_SHARE_TEST_H_
#define SRL_T_SHARE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test function for verifying the setting and reading of task information.
 *
 * This test function verifies the correct setting and reading of task information using the serial controller module.
 * It sets a sample task information, sends it using the set_task_analog_info function,
 * and then reads the information back using the analog_controller_read function.
 * Finally, it asserts that the sent task information matches the received task information.
 */
void test_set_and_read_task_serial_info(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of serial controller data.
 *
 * This test function verifies the correct setting and reading of serial controller data using the serial controller module.
 * It sets a sample plant buffer and buffer time, sends them using the analog_controller_send function,
 * and then reads the data back using the analog_controller_read function.
 * Finally, it asserts that the sent plant buffer and buffer time match the received data.
 */
void test_send_and_read_serial_controller_data(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of task status.
 *
 * This test function verifies the correct setting and reading of task status using the serial controller module.
 * It sets a sample task status, sends it using the set_task_analog_status function,
 * and then reads the status back using the analog_controller_read function.
 * Finally, it asserts that the sent task status matches the received task status.
 */
void test_set_and_read_task_serial_status(void); /**< \test */

/**
 * @brief Test function for verifying the behavior when reading serial controller data before sending.
 *
 * This test function verifies the behavior of the serial controller module when reading data before it is sent.
 * It initializes the _msg, plant_buff, and buff_time variables with zeros, reads the serial controller data,
 * and then ensures that the sizes of _msg's _plant_buff and _buff_time members are equal to the sizes of plant_buff and buff_time, respectively.
 */
void test_read_serial_controller_data_before_sending(void); /**< \test */


#endif /* SRL_T_SHARE_TEST_H_ */