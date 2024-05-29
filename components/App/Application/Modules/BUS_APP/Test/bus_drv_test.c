#include "bus_drv_test.h"
#include "safe_memory.h"
#include "bus_drv.h"
#include "bus_port.h"
#include "i2c_drv.h"
#include "fff.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const IBusPort *, hal_bus_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_handle_port_error()
    {
        // Perform DSP module initialization
        bus_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_BUS_CONFIG_ERROR);
    }

    void test_port_dev_init_error()
    {
        // Perform DSP module initialization
        devices_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, BUS_DRN_ON_DEVINIT_FATAL_ERROR);
    }

    void test_port_measure_data_error()
    {
        uint8_t raw_data[RAW_DATA_BYTES] = {0};
        // Perform DSP module initialization
        measure_raw_data(raw_data);
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, BUS_DRV_ON_READ_FATAL_ERROR);
    }

    void test_port_write_temp_moist_cmd_error()
    {
        ESht4xHeaterCmd_t cmd = SHT4X_NO_HEATER;
        // Perform DSP module initialization
        write_temp_moist_cmd(cmd);
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, BUS_DRV_ON_WRITE_ERROR);
    }
#endif

#ifndef FAKE_FUNC

static init_registers()
{
    store_error_in_slot(BUS_ERROR_SLOT,0); 
    set_errors(0, 0, 0, 0);
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            set_read_data(i,j,0);
        }
    }
}

void test_bus_drv_init_error()
{
    init_registers();
    set_errors(-1, 0, 0, 0);
    bus_init();
    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,BUS_DRV_INIT_ERROR);
}

void test_bus_drv_deinit_error()
{
    init_registers();      
    set_errors(0, -1, 0, 0);
    bus_deinit();
    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
}

void test_bus_drv_dev_init()
{
    init_registers();

    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);

    devices_init();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
}

void test_bus_drv_dev_init_serial_error()
{
    init_registers();

    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);

    devices_init();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,BUS_DEVICE_NOT_INIT);
}

void test_bus_drv_dev_init_chip_id_error()
{
    init_registers();

    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);

    devices_init();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,BUS_DEVICE_NOT_INIT);
}

void test_bus_drv_dev_init_write_error()
{
    init_registers();

    set_errors(0, 0, 0, -1);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);

    devices_init();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,BUS_DEVICE_NOT_INIT);
}

void test_bus_drv_dev_init_read_error()
{
    init_registers();

    set_errors(0, 0, -1, 0);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);

    devices_init();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,BUS_DEVICE_NOT_INIT);
}

void test_bus_measure_raw_data()
{
    init_registers();
    uint8_t raw_data[RAW_DATA_BYTES] = {0};
    uint8_t cmp_raw_data[RAW_DATA_BYTES] = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION,cmp_raw_data[0]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+1,cmp_raw_data[1]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+2,cmp_raw_data[2]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+3,cmp_raw_data[3]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+4,cmp_raw_data[4]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+5,cmp_raw_data[5]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_X_L,cmp_raw_data[6]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_X_H,cmp_raw_data[7]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Y_L,cmp_raw_data[8]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Y_H,cmp_raw_data[9]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Z_L,cmp_raw_data[10]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Z_H,cmp_raw_data[11]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC1_L,cmp_raw_data[12]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC1_H,cmp_raw_data[13]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC2_L,cmp_raw_data[14]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC2_H,cmp_raw_data[15]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC3_L,cmp_raw_data[16]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC3_H,cmp_raw_data[17]);

    measure_raw_data(raw_data);

    TEST_ASSERT_EQUAL(memcmp(raw_data, cmp_raw_data, RAW_DATA_BYTES),0);

}

void test_bus_measure_raw_data_null()
{
    init_registers();
    uint8_t raw_data[RAW_DATA_BYTES] = {0};

    measure_raw_data(NULL);

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(error, BUS_DRV_ON_READ_FATAL_ERROR);

}

void test_bus_measure_raw_data_write_read_error()
{
    init_registers();
    set_errors(0, 0, 0, -1);
    uint8_t raw_data[RAW_DATA_BYTES] = {0};
    uint8_t cmp_raw_data[RAW_DATA_BYTES] = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};

    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION,cmp_raw_data[0]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+1,cmp_raw_data[1]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+2,cmp_raw_data[2]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+3,cmp_raw_data[3]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+4,cmp_raw_data[4]);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_NOHEAT_LOWPRECISION+5,cmp_raw_data[5]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_X_L,cmp_raw_data[6]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_X_H,cmp_raw_data[7]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Y_L,cmp_raw_data[8]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Y_H,cmp_raw_data[9]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Z_L,cmp_raw_data[10]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_Z_H,cmp_raw_data[11]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC1_L,cmp_raw_data[12]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC1_H,cmp_raw_data[13]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC2_L,cmp_raw_data[14]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC2_H,cmp_raw_data[15]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC3_L,cmp_raw_data[16]);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_OUT_ADC3_H,cmp_raw_data[17]);

    measure_raw_data(raw_data);

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_NOT_EQUAL(memcmp(raw_data, cmp_raw_data, RAW_DATA_BYTES),0);
    TEST_ASSERT_EQUAL(error, BUS_DRV_ON_READ_ERROR);

    set_errors(0, 0, 0, -1);

    measure_raw_data(raw_data);

    error = read_error_from_slot(BUS_ERROR_SLOT);
        
    // Verify that the error matches the expected error code
    TEST_ASSERT_NOT_EQUAL(memcmp(raw_data, cmp_raw_data, RAW_DATA_BYTES),0);
    TEST_ASSERT_EQUAL(error, BUS_DRV_ON_READ_ERROR);

    set_errors(0, 0, 0, 0);

    measure_raw_data(raw_data);

    // Verify that the error matches the expected error code
    TEST_ASSERT_EQUAL(memcmp(raw_data, cmp_raw_data, RAW_DATA_BYTES),0);

}

void test_bus_drv_temp_moist_cmd()
{
    ESht4xHeaterCmd_t cmd = SHT4X_NO_HEATER;
    int8_t error = 0;
    init_registers();
    // Perform DSP module initialization
    for(int i=0; i<=SHT4X_LOW_HEATER_100MS;i++ )
    {
        cmd = (ESht4xHeaterCmd_t)i;
        write_temp_moist_cmd(cmd);
            
        error = read_error_from_slot(BUS_ERROR_SLOT);
            
        TEST_ASSERT_EQUAL(error, 0);  
    }
    cmd = (ESht4xHeaterCmd_t)10;
    write_temp_moist_cmd(cmd);
            
    error = read_error_from_slot(BUS_ERROR_SLOT);
            
    TEST_ASSERT_EQUAL(error, BUS_DRV_HEAT_CMD_INVALID); 
}

void test_bus_drv_temp_moist_cmd_write_error()
{
    ESht4xHeaterCmd_t cmd = SHT4X_NO_HEATER;
    int8_t error = 0;
    init_registers();
    set_errors(0, 0, 0, -1);
    // Perform DSP module initialization
    for(int i=1; i<=SHT4X_LOW_HEATER_100MS;i++)
    {
        cmd = (ESht4xHeaterCmd_t)i;
        write_temp_moist_cmd(cmd);
            
        error = read_error_from_slot(BUS_ERROR_SLOT);
            
        TEST_ASSERT_EQUAL(error, BUS_DRV_ON_WRITE_ERROR);  
    }
    cmd = (ESht4xHeaterCmd_t)10;
    write_temp_moist_cmd(cmd);
            
    error = read_error_from_slot(BUS_ERROR_SLOT);
            
    TEST_ASSERT_EQUAL(error, BUS_DRV_HEAT_CMD_INVALID); 
}

#endif

void bus_drv_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
    RUN_TEST(test_port_dev_init_error);
    RUN_TEST(test_port_measure_data_error);
    RUN_TEST(test_port_write_temp_moist_cmd_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_bus_drv_init_error);
    RUN_TEST(test_bus_drv_deinit_error);
    RUN_TEST(test_bus_drv_dev_init);
    RUN_TEST(test_bus_drv_dev_init_serial_error);
    RUN_TEST(test_bus_drv_dev_init_chip_id_error);
    RUN_TEST(test_bus_drv_dev_init_write_error);
    RUN_TEST(test_bus_drv_dev_init_read_error);
    RUN_TEST(test_bus_measure_raw_data);
    RUN_TEST(test_bus_measure_raw_data_null);
    RUN_TEST(test_bus_measure_raw_data_write_read_error);
    RUN_TEST(test_bus_drv_temp_moist_cmd);
    RUN_TEST(test_bus_drv_temp_moist_cmd_write_error);
#endif
}
