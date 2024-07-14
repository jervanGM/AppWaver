#ifndef MEM_DRV_TEST_H_
#define MEM_DRV_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for handling port errors in DSP module initialization.
 *
 * This test function initializes the memory driver module, checks if an error is stored in the designated error slot,
 * and asserts that the error matches the expected error code HAL_MEM_CONFIG_ERROR.
 */
void test_handle_port_error(); /**< \test */

/**
 * @brief Test function for initializing memory and verifying file creation.
 *
 * This test function initializes the memory driver module, mocks specific errors,
 * and verifies that the expected files "./sdcard/device_info.txt" and "./sdcard/wave_data" are created.
 * It also verifies the contents of "./sdcard/device_info.txt".
 */
void test_mem_drv_init_file(); /**< \test */

/**
 * @brief Test function for initializing memory and verifying initialization error handling.
 *
 * This test function initializes the memory driver module, mocks specific errors,
 * and verifies that the initialization error is stored in the designated error slot.
 */
void test_mem_drv_init_error(); /**< \test */

/**
 * @brief Test function for initializing memory and verifying directory creation error handling.
 *
 * This test function initializes the memory driver module, mocks specific errors,
 * and verifies that the directory creation error is stored in the designated error slot.
 * It also verifies that "./sdcard/device_info.txt" is created but "./sdcard/wave_data" is not created.
 */
void test_mem_drv_init_create_dir_error(); /**< \test */

/**
 * @brief Test function for initializing memory and verifying file creation error handling.
 *
 * This test function initializes the memory driver module, mocks specific errors,
 * removes "./sdcard/device_info.txt", and verifies that the file creation error is stored in the designated error slot.
 */
void test_mem_drv_init_create_file_error(); /**< \test */

/**
 * @brief Test function for creating WAV file and verifying file creation error handling.
 *
 * This test function mocks specific errors during WAV file creation,
 * sets the file path to "/wave_data/1/test.wav", and verifies that the file creation error is stored in the designated error slot.
 */
void test_mem_drv_create_wav_file_error(); /**< \test */

/**
 * @brief Test function for writing WAV file and verifying file write error handling.
 *
 * This test function mocks specific errors during WAV file writing,
 * sets the file path to "/wave_data/2/test.wav", and verifies that the file write error is stored in the designated error slot.
 * It also verifies that the file "./sdcard/wave_data/2/test.wav" exists.
 */
void test_mem_drv_write_wav_file_error(); /**< \test */

/**
 * @brief Test function for deinitializing memory and verifying deinitialization error handling.
 *
 * This test function initializes the memory driver module, mocks specific errors during deinitialization,
 * and verifies that the deinitialization error is stored in the designated error slot.
 */
void test_mem_drv_deinit_error(); /**< \test */

#endif /* MEM_DRV_TEST_H_ */
