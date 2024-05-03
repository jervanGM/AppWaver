#include "pw_mng_test.h"
#include "safe_memory.h"
#include "pw_mng.h"
#include "io_port.h"
#include "fff.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const IIOPort *, hal_io_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_handle_port_error()
    {
        // Perform DSP module initialization
        pw_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(POWER_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_PW_CONFIG_ERROR);
    }
#endif

#ifndef FAKE_FUNC

void test_power_init()
{
    const IIOPort *iport = hal_io_get_port();
    pw_init();
    bool value  = iport->read(1);
    TEST_ASSERT_EQUAL(false,value);
}

void test_power_off()
{
    const IIOPort *port = hal_io_get_port();
    set_main_power_off();
    bool value  = port->read(1);
    TEST_ASSERT_EQUAL(true,value);
}

#endif

void pw_mng_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_power_init);
    RUN_TEST(test_power_off);
#endif
}
