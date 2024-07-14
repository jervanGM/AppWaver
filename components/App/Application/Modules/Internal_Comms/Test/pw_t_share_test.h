#ifndef PW_T_SHARE_TEST_H_
#define PW_T_SHARE_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for verifying the setting and reading of task information.
 *
 * This test function verifies the correct setting and reading of task information using the power controller module.
 * It sets a sample task information, sends it using the set_task_power_info function,
 * and then reads the information back using the pw_ctrl_read function.
 * Finally, it asserts that the sent task information matches the received task information.
 */
void test_set_and_read_task_power_info(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of power controller data.
 *
 * This test function verifies the correct setting and reading of power controller data using the power controller module.
 * It sets a sample sensor switch status, main switch status, soil activation status, WiFi activation status, and power mode,
 * sends them using the ctrl_pw_send function,
 * and then reads the data back using the ctrl_pw_read function.
 * Finally, it asserts that the sent data match the received data.
 */
void test_send_and_read_power_controller_data(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of task status.
 *
 * This test function verifies the correct setting and reading of task status using the power controller module.
 * It sets a sample task status, sends it using the set_task_power_status function,
 * and then reads the status back using the pw_ctrl_read function.
 * Finally, it asserts that the sent task status matches the received task status.
 */
void test_set_and_read_task_power_status(void); /**< \test */

/**
 * @brief Test function for verifying the behavior when reading power controller data before sending.
 *
 * This test function verifies the behavior of the power controller module when reading data before it is sent.
 * It initializes the _msg, sens_sw_sts, main_sw_sts, soil_act_sts, wifi_act_sts, and pw_mode variables with zeros,
 * reads the power controller data, and then ensures that the sizes of _msg's members match the sizes of the initialized variables.
 */
void test_read_power_controller_data_before_sending(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of power controller data.
 *
 * This test function verifies the correct setting and reading of power controller data using the power controller module.
 * It sets a sample sensor switch status, main switch status, soil activation status, WiFi activation status, and power mode,
 * sends them using the ctrl_pw_send function,
 * and then reads the data back using the ctrl_pw_read function.
 * Finally, it asserts that the sent data match the received data.
 */
void test_send_and_read_controller_power_data(void); /**< \test */

/**
 * @brief Test function for verifying the behavior when reading power controller data before sending.
 *
 * This test function verifies the behavior of the power controller module when reading data before it is sent.
 * It initializes the _msg, sens_sw_sts, main_sw_sts, soil_act_sts, wifi_act_sts, and pw_mode variables with zeros,
 * reads the power controller data, and then ensures that the sizes of _msg's members match the sizes of the initialized variables.
 */
void test_read_controller_power_data_before_sending(void); /**< \test */

#endif /* PW_T_SHARE_TEST_H_ */
