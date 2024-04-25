#include "mem_drv_test.h"
#include "safe_memory.h"
#include "mem_drv.h"
#include "mem_port.h"
#include "sd_spi_drv.h"
#include "fff.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const IMemPort *, hal_ext_mem_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_handle_port_error()
    {
        // Perform DSP module initialization
        mem_drv_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_MEM_CONFIG_ERROR);
    }
#endif

#ifndef FAKE_FUNC
void test_mem_drv_init_file()
{
    struct stat st;
    mock_drv_errors(0,0,0,0,0,0,1,0,0,0);
    mem_drv_init();

    TEST_ASSERT_EQUAL(stat("./sdcard/device_info.txt", &st), 0);
    TEST_ASSERT_EQUAL(stat("./sdcard/wave_data", &st), 0);
    const char *filename = "./sdcard/device_info.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        TEST_ASSERT_EQUAL(strcmp(line, "FW VERSION:1.0.0"),0);
    }

    fclose(file);
}

void test_mem_drv_init_error()
{
    struct stat st;
    mock_drv_errors(-1,0,0,0,0,0,1,0,0,0);
    mem_drv_init();

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, MEM_DRV_INIT_ERROR);

    TEST_ASSERT_NOT_EQUAL(stat("./sdcard/device_info.txt", &st), 0);
    TEST_ASSERT_NOT_EQUAL(stat("./sdcard/wave_data", &st), 0);

}

void test_mem_drv_init_create_dir_error()
{
    struct stat st;
    mock_drv_errors(0,0,0,0,-1,0,1,0,0,0);
    mem_drv_init();

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, MEM_DRV_CREATE_DIR_ERROR);

    TEST_ASSERT_EQUAL(stat("./sdcard/device_info.txt", &st), 0);
    TEST_ASSERT_NOT_EQUAL(stat("./sdcard/wave_data", &st), 0);

}

void test_mem_drv_init_create_file_error()
{
    struct stat st;
    mock_drv_errors(0,0,0,0,0,-1,1,0,0,0);
    remove("./sdcard/device_info.txt");
    mem_drv_init();

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, MEM_DRV_CREATE_FILE_ERROR);

}

void test_mem_drv_create_wav_file_error()
{
    struct stat st;
    SWavData wav;
    mock_drv_errors(0,0,0,0,0,-1,1,0,0,0);
    sprintf(wav.file_path, "%s", "/wave_data/1/test.wav");
    save_wav_data(wav);

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, MEM_DRV_CREATE_FILE_ERROR);

}

void test_mem_drv_write_wav_file_error()
{
    struct stat st;
    SWavData wav;
    mock_drv_errors(0,-1,0,0,0,0,1,0,0,0);
    sprintf(wav.file_path, "%s", "/wave_data/2/test.wav");
    save_wav_data(wav);

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(stat("./sdcard/wave_data/2/test.wav", &st), 0);
    TEST_ASSERT_EQUAL(error, MEM_DRV_WRITE_FILE_ERROR);

}

void test_mem_drv_deinit_error()
{
    struct stat st;
    SWavData wav;
    mock_drv_errors(0,0,0,0,0,0,1,0,0,-1);
    mem_drv_deinit();

    int8_t error = read_error_from_slot(EXT_MEM_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, MEM_DRV_DEINIT_ERROR);

}

#endif

void mem_drv_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_mem_drv_init_error);
    RUN_TEST(test_mem_drv_init_create_dir_error);
    RUN_TEST(test_mem_drv_init_create_file_error);
    RUN_TEST(test_mem_drv_init_file);
    RUN_TEST(test_mem_drv_create_wav_file_error);
    RUN_TEST(test_mem_drv_write_wav_file_error);
    RUN_TEST(test_mem_drv_deinit_error);
    
#endif
}
