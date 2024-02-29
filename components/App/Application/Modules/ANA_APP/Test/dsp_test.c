#include "dsp_test.h"
#include "safe_memory.h"
#include "fff.h"
#include "dsp.h"
#include "ana_port.h"
#include "i_analog_data.h"
#include "adc_drv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const IAnaPort *, hal_ana_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_dsp_init_error()
    {
        // Perform DSP module initialization
        dsp_init_port();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_ANA_CONFIG_ERROR);
    }

    // Test for verifying the memory error handling of the DSP module data retrieval.
    void test_dsp_data_memory_error()
    {
        // Variable to store the retrieved data
        uint8_t data = 0;
        
        // Retrieve data from the DSP module
        data = get_dsp_data();
        
        // Check if the memory error is stored in the designated error slot
        int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
        
        // Verify that the error matches the expected error code and the returned data is zero
        TEST_ASSERT_EQUAL(error, HAL_ANA_CONFIG_ERROR);
        TEST_ASSERT_EQUAL(data, 0);
    }
#endif

#ifndef FAKE_FUNC
    // Test for verifying the initialization of the DSP module.
    void test_dsp_init()
    {
        // Perform DSP module initialization
        store_error_in_slot(0, 0);
        dsp_init_port();
        
        // Check if the error slot remains zero after initialization
        int8_t error = read_error_from_slot(0);
        TEST_ASSERT_EQUAL(error, 0);
    }

    // Test for verifying data retrieval from the DSP module.
    void test_dsp_data()
    {
        // Variable to store the retrieved data
        uint8_t data = 0;
        
        // Retrieve data from the DSP module
        store_error_in_slot(0, 0);
        set_adc_value(27);
        data = get_dsp_data();
        
        // Check if the error slot remains zero after data retrieval and if the returned data matches the expected value
        int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
        TEST_ASSERT_EQUAL(error, 0);
        TEST_ASSERT_EQUAL(data, 3);
    }

    // Test for verifying the error handling of the DSP module's data filtering.
    void test_dsp_data_filter_error()
    {
        // Variable to store the error
        int8_t error;
        
        // Create a null pointer to simulate an error condition
        uint32_t *null_pointer = NULL;
        
        // Call the function to test error handling
        store_error_in_slot(0, 0);
        iir_filter(null_pointer);
        
        // Check if the error is stored in the designated error slot
        error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
        TEST_ASSERT_EQUAL(error, ANA_DSP_IIR_ERROR);
    }

    // Test for verifying the error handling of the DSP module with overflow data.
    void test_dsp_data_overflow_error()
    {
        // Variable to store the data
        uint32_t data = UINT32_MAX;
        
        // Call the function to test error handling with overflow data
        store_error_in_slot(0, 0);
        set_adc_value(data);
        data = get_dsp_data();

        // Check if the error is stored in the designated error slot
        TEST_ASSERT_EQUAL(read_error_from_slot(ANALOGIC_ERROR_SLOT), ANA_DSP_NORMALIZE_ERROR);
    }

    // Test for verifying data retrieval from the DSP module with low input.
    void test_dsp_data_with_low_input()
    {
        // Variable to store the low input value
        uint32_t low_input = 100;
        
        // Set 1000 numbers to 0 to filter stabilization
        for (int i = 0; i < 10000; i++)
        {
            set_adc_value(0);
            get_dsp_data();
        }
        
        // Set the low input value
        set_adc_value(low_input);
        
        // Retrieve data from the DSP module
        uint8_t result = get_dsp_data();

        // Check if the returned data falls within the expected range
        TEST_ASSERT_LESS_OR_EQUAL(13, result);
    }

    // Test for verifying data retrieval from the DSP module with high input.
    void test_dsp_data_with_high_input()
    {
        // Variable to store the high input value
        uint32_t high_input = 1000;
        
        // Set the high input value
        set_adc_value(high_input);

        // Retrieve data from the DSP module
        uint8_t result = get_dsp_data();

        // Check if the returned data falls within the expected range
        TEST_ASSERT(result <= NORMALIZED_MAX);
    }

    // Test for verifying data retrieval from the DSP module with random input.
    void test_dsp_data_random_wave()
    {
        // Variables to store the high input value and the result
        uint32_t high_input = 0;
        uint8_t result = 0;
        
        // Seed the random number generator
        srand(time(NULL));
        
        // Set 1000 numbers to 0 to filter stabilization
        for (int i = 0; i < 10000; i++)
        {
            set_adc_value(0);
            get_dsp_data();
        }
        
        // Generate random input and retrieve data from the DSP module
        for (int i = 0; i < 100; i++)
        {
            high_input = rand() % UINT32_MAX;
            set_adc_value(high_input);
            result = get_dsp_data();
            
            // Check if the returned data falls within the expected range
            TEST_ASSERT_GREATER_OR_EQUAL(NORMALIZED_MIN, result);
            TEST_ASSERT_LESS_OR_EQUAL(NORMALIZED_MAX, result);
        }
    }
#endif


void dsp_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_dsp_init_error);
    RUN_TEST(test_dsp_data_memory_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_dsp_init);
    RUN_TEST(test_dsp_data);
    RUN_TEST(test_dsp_data_filter_error);
    RUN_TEST(test_dsp_data_overflow_error);
    RUN_TEST(test_dsp_data_with_low_input);
    RUN_TEST(test_dsp_data_with_high_input);
    RUN_TEST(test_dsp_data_random_wave);
#endif
}