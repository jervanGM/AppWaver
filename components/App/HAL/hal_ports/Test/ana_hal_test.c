#include "ana_hal_test.h"
#include "safe_trace.h"
#include "ana_port.h"
#include "adc_cfg.h"
#include "adc_drv.h"
#include "gen_types.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// Test function for verifying the retrieval of the analog port interface.
void test_hal_ana_get_port(void) {
    // Get the analog port interface
    const IAnaPort *port = hal_ana_get_port();

    // Verify that the retrieved port pointer is not NULL
    TEST_ASSERT_NOT_NULL(port);
}

// Test function for verifying the initialization and reset of the analog port.
void test_hal_ana_is_init(void) {
    // Get the analog port interface
    const IAnaPort *port = hal_ana_get_port();

    // Initialize the analog port
    port->init();

    // Verify that the initialization flag is set
    TEST_ASSERT_EQUAL(is_init(), true);

    // Reset the analog port
    port->reset();

    // Verify that the initialization flag is cleared after reset
    TEST_ASSERT_EQUAL(is_init(), false);
}

// Test function for verifying the read functionality of the analog port.
void test_hal_ana_read(void) {
    // Get the analog port interface
    const IAnaPort *port = hal_ana_get_port();

    // Variables for input and output ADC values
    uint32_t in_adc_value = 0;
    uint32_t out_adc_value = 0;

    // Iterate over a range of input ADC values
    for (int i = 0; i < 10; i++) {
        // Set the simulated ADC value
        in_adc_value = i;
        set_adc_value(in_adc_value);

        // Read from the analog port
        port->read(0, &out_adc_value);

        // Log input and output ADC values
        TRACE_INFO("INPUT VALUES TO ADC:", TO_STRING(in_adc_value), 
                   "OUTPUT VALUES FROM ADC:", TO_STRING(out_adc_value));

        // Verify that the output ADC value matches the input ADC value
        TEST_ASSERT_EQUAL(out_adc_value, in_adc_value);
    }
}

void ana_hal_test_suite()
{
    RUN_TEST(test_hal_ana_get_port);
    RUN_TEST(test_hal_ana_is_init);
    RUN_TEST(test_hal_ana_read);
}