#ifndef MEM_APP_TEST_H_
#define MEM_APP_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for checking major faults.
 *
 * This test function stores an error in the external memory error slot,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_MAYOR_FAULT.
 */
void test_mem_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test function for checking minor faults.
 *
 * This test function stores an error in the external memory error slot,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_MINOR_FAULT.
 */
void test_mem_app_check_minor_faults(); /**< \test */

/**
 * @brief Test function for checking no faults.
 *
 * This test function stores an error in the external memory error slot,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_TASK_OK.
 */
void test_mem_app_check_no_faults(); /**< \test */

/**
 * @brief Test function for checking lower minor fault boundary.
 *
 * This test function stores an error at the minor fault threshold,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_TASK_OK.
 */
void test_mem_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking upper minor fault boundary.
 *
 * This test function stores an error just below the major fault threshold,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_MAYOR_FAULT.
 */
void test_mem_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking lower major fault boundary.
 *
 * This test function stores an error at the major fault threshold,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_TASK_OK.
 */
void test_mem_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test function for checking upper major fault boundary.
 *
 * This test function stores an error at the maximum value for int8_t,
 * checks for faults using mem_app_check_faults, and asserts that the returned fault status is MEM_TASK_OK.
 */
void test_mem_app_check_upper_major_fault_boundary(); /**< \test */

/**
 * @brief Test function for processing WAV data.
 *
 * This test function initializes memory, processes data to WAV format,
 * and asserts that the resulting WAV data structure's header matches expected values,
 * and that the data array matches the original data.
 */
void test_mem_app_process_wav_data(); /**< \test */

/**
 * @brief Test function for processing the same WAV data twice.
 *
 * This test function initializes memory, processes data to WAV format twice,
 * asserts that the resulting WAV data structure's header matches expected values for the first run,
 * asserts that the average of the first run is not zero,
 * processes data to WAV format again, and asserts that the average of the second run is zero.
 */
void test_mem_app_process_same_wav_data(); /**< \test */

/**
 * @brief Test function for processing WAV data without initialization.
 *
 * This test function processes data to WAV format without initializing memory,
 * and asserts that the resulting WAV data structure's header and data fields are zeroed out.
 */
void test_mem_app_process_not_init_wav_data(); /**< \test */

/**
 * @brief Test function for processing WAV data with a null pointer.
 *
 * This test function processes NULL data pointer to WAV format,
 * and asserts that the resulting WAV data structure's average field is zero.
 */
void test_process_data_to_wav_null_pointer(); /**< \test */

#endif /* MEM_APP_TEST_H_ */
