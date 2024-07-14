#ifndef MEM_T_SHARE_TEST_H_
#define MEM_T_SHARE_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for verifying the setting and reading of task information.
 *
 * This test function verifies the correct setting and reading of task information using the external memory controller module.
 * It sets a sample task information, sends it using the set_task_ext_mem_info function,
 * and then reads the information back using the mem_ctrl_read function.
 * Finally, it asserts that the sent task information matches the received task information.
 */
void test_set_and_read_task_memory_info(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of external memory controller data.
 *
 * This test function verifies the correct setting and reading of external memory controller data using the external memory controller module.
 * It sets a sample plant buffer and buffer time, sends them using the ctrl_mem_send function,
 * and then reads the data back using the ctrl_mem_read function.
 * Finally, it asserts that the sent plant buffer and buffer time match the received data.
 */
void test_send_and_read_memory_controller_data(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of task status.
 *
 * This test function verifies the correct setting and reading of task status using the external memory controller module.
 * It sets a sample task status, sends it using the set_task_ext_mem_status function,
 * and then reads the status back using the mem_ctrl_read function.
 * Finally, it asserts that the sent task status matches the received task status.
 */
void test_set_and_read_task_memory_status(void); /**< \test */

/**
 * @brief Test function for verifying the behavior when reading external memory controller data before sending.
 *
 * This test function verifies the behavior of the external memory controller module when reading data before it is sent.
 * It initializes the _msg and task_info variables with zeros,
 * reads the external memory controller data, and then ensures that the sizes of _msg's members match the sizes of the initialized variables.
 */
void test_read_memory_controller_data_before_sending(void); /**< \test */

/**
 * @brief Test function for verifying the setting and reading of external memory controller data.
 *
 * This test function verifies the correct setting and reading of external memory controller data using the external memory controller module.
 * It sets a sample device alarm, system status, plant signal, environmental data, power data, axis buffer, current mode, previous mode,
 * start time, end time, and system time, sends them using the ctrl_mem_send function,
 * and then reads the data back using the ctrl_mem_read function.
 * Finally, it asserts that the sent data match the received data.
 */
void test_send_and_read_controller_memory_data(void); /**< \test */

/**
 * @brief Test function for verifying the behavior when reading external memory controller data before sending.
 *
 * This test function verifies the behavior of the external memory controller module when reading data before it is sent.
 * It initializes the _msg, alarm, status, plant_signal, env_data, power_data, axis_buff, current_mode, previous_mode,
 * start_time, end_time, and system_time variables with zeros,
 * reads the external memory controller data, and then ensures that the sizes of _msg's members match the sizes of the initialized variables.
 */
void test_read_controller_memory_data_before_sending(void); /**< \test */

#endif /* MEM_T_SHARE_TEST_H_ */
