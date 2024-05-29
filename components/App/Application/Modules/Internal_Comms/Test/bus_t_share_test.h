#ifndef BUS_T_SHARE_TEST_H_
#define BUS_T_SHARE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test function for verifying the setting and reading of task information.
 *
 * This test function verifies the correct setting and reading of task information using the indicator controller module.
 * It sets a sample task information, sends it using the set_task_bus_info function,
 * and then reads the information back using the controller_bus_read function.
 * Finally, it asserts that the sent task information matches the received task information.
 */
void test_set_and_read_task_bus_info(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of indicator controller data.
 *
 * This test function verifies the correct setting and reading of indicator controller data using the indicator controller module.
 * It sets a sample plant buffer and buffer time, sends them using the ind_ctrl_send function,
 * and then reads the data back using the controller_bus_read function.
 * Finally, it asserts that the sent plant buffer and buffer time match the received data.
 */
void test_send_and_read_bus_controller_data(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of task status.
 *
 * This test function verifies the correct setting and reading of task status using the indicator controller module.
 * It sets a sample task status, sends it using the set_task_bus_status function,
 * and then reads the status back using the controller_bus_read function.
 * Finally, it asserts that the sent task status matches the received task status.
 */
void test_set_and_read_task_bus_status(void); /**< \test */

void test_send_and_read_bus_controller_data(void);

void test_read_bus_controller_data_before_sending(void); /**< \test */

void test_send_and_read_controller_bus_data(void);

void test_read_controller_bus_data_before_sending(void);


#endif /* BUS_T_SHARE_TEST_H_ */