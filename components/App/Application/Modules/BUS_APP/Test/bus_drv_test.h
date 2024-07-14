#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test case to verify initialization error handling in bus driver.
 * 
 * This test sets up registers, induces an initialization error,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_init_error(); /**< \test */

/**
 * @brief Test case to verify deinitialization error handling in bus driver.
 * 
 * This test sets up registers, induces a deinitialization error,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_deinit_error(); /**< \test */

/**
 * @brief Test case to verify device initialization error handling in bus driver.
 * 
 * This test sets up registers, simulates device initialization,
 * and verifies if the error code matches the expected error when initializing devices.
 */
void test_bus_drv_dev_init(); /**< \test */

/**
 * @brief Test case to verify serial error during device initialization in bus driver.
 * 
 * This test sets up registers, simulates device initialization with a serial error,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_dev_init_serial_error(); /**< \test */

/**
 * @brief Test case to verify chip ID error during device initialization in bus driver.
 * 
 * This test sets up registers, simulates device initialization with a chip ID error,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_dev_init_chip_id_error(); /**< \test */

/**
 * @brief Test case to verify write error during device initialization in bus driver.
 * 
 * This test sets up registers, induces a write error during device initialization,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_dev_init_write_error(); /**< \test */

/**
 * @brief Test case to verify read error during device initialization in bus driver.
 * 
 * This test sets up registers, induces a read error during device initialization,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_dev_init_read_error(); /**< \test */

/**
 * @brief Test case to verify raw data measurement in bus driver.
 * 
 * This test sets up registers, performs raw data measurement,
 * and verifies if the measured raw data matches the expected data.
 */
void test_bus_measure_raw_data(); /**< \test */

/**
 * @brief Test case to verify error handling in raw data measurement in bus driver.
 * 
 * This test sets up registers, performs raw data measurement with NULL data,
 * and verifies if the error code matches the expected error.
 */
void test_bus_measure_raw_data_null(); /**< \test */

/**
 * @brief Test case to verify write-read error handling in raw data measurement in bus driver.
 * 
 * This test sets up registers, induces write-read error during raw data measurement,
 * and verifies if the error code matches the expected error.
 */
void test_bus_measure_raw_data_write_read_error(); /**< \test */

/**
 * @brief Test case to verify temperature and moisture command handling in bus driver.
 * 
 * This test sets up registers, performs various temperature and moisture commands,
 * and verifies if no error occurs for valid commands and the expected error for an invalid command.
 */
void test_bus_drv_temp_moist_cmd(); /**< \test */

/**
 * @brief Test case to verify write error handling in temperature and moisture command in bus driver.
 * 
 * This test sets up registers, induces a write error during temperature and moisture command,
 * and verifies if the error code matches the expected error.
 */
void test_bus_drv_temp_moist_cmd_write_error(); /**< \test */

#endif /* TRACE_TEST_H_ */
