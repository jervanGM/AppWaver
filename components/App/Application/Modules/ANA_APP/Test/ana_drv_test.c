#include "ana_drv_test.h"
#include "safe_memory.h"
#include "analog_drv.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef FAKE_FUNC
// Test for handling error when the data buffer pointer is NULL
void test_ana_drv_data_buffer_error() {
    // First case: NULL data buffer pointer
    SDataBuffer_t *data_buffer = NULL;
    SBufferTime_t data_time;
    // Store error in slot
    store_error_in_slot(0, 0);
    // Attempt to get data buffer with NULL pointer
    get_data_buffer(data_buffer, &data_time);
    // Read error code from the slot
    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Verify buffer empty error
    TEST_ASSERT_EQUAL(error, ANA_DRV_BUFFER_EMPTY);

    // Second case: NULL data time pointer
    SDataBuffer_t data_buffer_2;
    SBufferTime_t *data_time_2 = NULL;
    store_error_in_slot(0, 0);
    // Attempt to get data buffer with NULL time pointer
    get_data_buffer(&data_buffer_2, data_time_2);
    error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Verify buffer empty error
    TEST_ASSERT_EQUAL(error, ANA_DRV_BUFFER_EMPTY);
}

// Test for handling error when adding data to the buffer
void test_ana_drv_add_data_buffer_error() {
    // First case: NULL data buffer pointer
    SDataBuffer_t *data_buffer = NULL;
    SBufferTime_t data_time;
    store_error_in_slot(0, 0);
    // Attempt to add data to buffer with NULL pointer
    add_to_buffer(data_buffer, &data_time, 0);
    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Verify buffer empty error
    TEST_ASSERT_EQUAL(error, ANA_DRV_BUFFER_EMPTY);

    // Second case: NULL data time pointer
    SDataBuffer_t data_buffer_2;
    SBufferTime_t *data_time_2 = NULL;
    store_error_in_slot(0, 0);
    // Attempt to add data to buffer with NULL time pointer
    add_to_buffer(&data_buffer_2, data_time_2, 0);
    error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Verify buffer empty error
    TEST_ASSERT_EQUAL(error, ANA_DRV_BUFFER_EMPTY);
}

// Test for handling error when clearing the data buffer
void test_ana_drv_clean_data_buffer_error() {
    // NULL data buffer pointer
    SDataBuffer_t *data_buffer = NULL;
    store_error_in_slot(0, 0);
    // Attempt to clear data buffer with NULL pointer
    clear_data_buffer(data_buffer);
    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    // Verify buffer empty error
    TEST_ASSERT_EQUAL(error, ANA_DRV_BUFFER_EMPTY);
}

// Test for verifying data buffer behavior
void test_get_data_buffer() {
    // Initialize data buffer and time structures
    SDataBuffer_t buffer;
    SBufferTime_t time;
    buffer.size = 0;
    buffer.ready = false;

    // Stabilize buffer with 0 values
    for (int i = 0; i < 10000; i++) {
        SDataBuffer_t buffer_f;
        SBufferTime_t time_f;
        set_adc_value(0);
        get_data_buffer(&buffer_f, &time_f);
    }

    // Simulate ADC data
    uint32_t simulated_adc_value = 50;
    set_adc_value(simulated_adc_value);

    // Get data buffer
    get_data_buffer(&buffer, &time);

    // Check buffer state after adding first value
    TEST_ASSERT_EQUAL(buffer.size, 1);
    TEST_ASSERT_EQUAL(buffer.data[0], 6);
    TEST_ASSERT_NOT_EQUAL(time.start_time.sec, 0);
    TEST_ASSERT_EQUAL(buffer.ready, false);

    //Set 1s delay for time
    Sleep(1000);

    // Collect data for BUFFER_SIZE iterations
    for (int i = 1; i < BUFFER_SIZE; i++) {
        // Simulate new ADC data
        simulated_adc_value = rand() % UINT32_MAX;
        set_adc_value(simulated_adc_value);
        get_data_buffer(&buffer, &time);
        // Verify data range
        TEST_ASSERT_GREATER_OR_EQUAL(0, buffer.data[i]);
        TEST_ASSERT_LESS_OR_EQUAL(255, buffer.data[i]);
    }

    // Verify buffer state after filling
    TEST_ASSERT_EQUAL(buffer.ready, true);
    TEST_ASSERT_EQUAL(buffer.size, BUFFER_SIZE);
    TEST_ASSERT_NOT_EQUAL(time.end_time.sec, 0);
    TEST_ASSERT_NOT_EQUAL(time.end_time.sec, time.start_time.sec);
}

// Test for verifying buffer clearing behavior
void test_get_data_clean_buffer() {
    // Initialize data buffer and time structures
    SDataBuffer_t buffer;
    SBufferTime_t time;
    buffer.size = 0;
    buffer.ready = false;

    // Stabilize buffer with 0 values
    for (int i = 0; i < 10000; i++) {
        SDataBuffer_t buffer_f;
        SBufferTime_t time_f;
        set_adc_value(0);
        get_data_buffer(&buffer_f, &time_f);
    }

    // Simulate ADC data
    uint32_t simulated_adc_value = 50;
    set_adc_value(simulated_adc_value);

    // Get data buffer
    get_data_buffer(&buffer, &time);

    // Check buffer state after adding first value
    TEST_ASSERT_EQUAL(buffer.size, 1);
    TEST_ASSERT_EQUAL(buffer.data[0], 6);
    TEST_ASSERT_NOT_EQUAL(time.start_time.sec, 0);
    TEST_ASSERT_EQUAL(buffer.ready, false);

    //Set 1s delay for time
    Sleep(1000);
    
    // Collect data for BUFFER_SIZE iterations
    for (int i = 1; i < BUFFER_SIZE; i++) {
        // Simulate increasing ADC data
        simulated_adc_value++;
        set_adc_value(simulated_adc_value);
        get_data_buffer(&buffer, &time);
    }

    // Simulate final ADC data
    set_adc_value(simulated_adc_value);
    get_data_buffer(&buffer, &time);

    // Verify buffer state after clearing
    TEST_ASSERT_EQUAL(buffer.ready, false);
    TEST_ASSERT_EQUAL(buffer.size, 1);
    TEST_ASSERT_NOT_EQUAL(time.end_time.sec, 0);
    TEST_ASSERT_EQUAL(time.end_time.sec, time.start_time.sec);
}

// Test for verifying buffer behavior with random wave input
void test_get_data_buffer_random_wave() {
    // Initialize data buffer and time structures
    SDataBuffer_t buffer;
    SBufferTime_t time;
    buffer.size = 0;
    buffer.ready = false;

    // Stabilize buffer with 0 values
    for (int i = 0; i < 10000; i++) {
        SDataBuffer_t buffer_f;
        SBufferTime_t time_f;
        set_adc_value(0);
        get_data_buffer(&buffer_f, &time_f);
    }

    // Simulate ADC data
    uint32_t simulated_adc_value = 50;
    set_adc_value(simulated_adc_value);

    // Get data buffer
    get_data_buffer(&buffer, &time);

    // Check buffer state after adding first value
    TEST_ASSERT_EQUAL(buffer.size, 1);
    TEST_ASSERT_EQUAL(buffer.data[0], 6);
    TEST_ASSERT_NOT_EQUAL(time.start_time.sec, 0);
    TEST_ASSERT_EQUAL(buffer.ready, false);

    //Set 1s delay for time
    Sleep(1000);

    // Collect data for BUFFER_SIZE iterations
    for (int i = 1; i < BUFFER_SIZE; i++) {
        // Simulate increasing ADC data
        simulated_adc_value++;
        set_adc_value(simulated_adc_value);
        get_data_buffer(&buffer, &time);
    }

    // Verify buffer state after filling
    TEST_ASSERT_EQUAL(buffer.ready, true);
    TEST_ASSERT_EQUAL(buffer.size, BUFFER_SIZE);
    TEST_ASSERT_NOT_EQUAL(time.end_time.sec, 0);
    TEST_ASSERT_NOT_EQUAL(time.end_time.sec, time.start_time.sec);
}

#endif

void ana_drv_test_suite()
{
#ifndef FAKE_FUNC
    RUN_TEST(test_ana_drv_data_buffer_error);
    RUN_TEST(test_ana_drv_add_data_buffer_error);
    RUN_TEST(test_ana_drv_clean_data_buffer_error);
    RUN_TEST(test_get_data_buffer);
    RUN_TEST(test_get_data_clean_buffer);
    RUN_TEST(test_get_data_buffer_random_wave);
#endif
}
