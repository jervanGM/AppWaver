#include "ind_codec_test.h"
#include "safe_memory.h"
#include "ind_codec.h"
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
        ind_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(INDICATOR_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_IND_CONFIG_ERROR);
    }
#endif

#ifndef FAKE_FUNC

void test_indicator_init()
{
    const IIOPort *port = hal_io_get_port();
    ind_init();

    bool value = port->read(1);
    TEST_ASSERT_EQUAL(true,value);
}

void test_indicator_set_state_fix_on()
{
    const IIOPort *port = hal_io_get_port();
    ind_init();
    set_indicator_state(IND_LED1,FIXED_ON);
    bool value = port->read(1);
    TEST_ASSERT_EQUAL(true,value);
}

void test_indicator_set_state_fix_off()
{
    const IIOPort *port = hal_io_get_port();
    ind_init();
    set_indicator_state(IND_LED1,FIXED_OFF);
    bool value = port->read(1);
    TEST_ASSERT_EQUAL(false,value);
}


#endif

void ind_codec_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_indicator_init);
    RUN_TEST(test_indicator_set_state_fix_on);
    RUN_TEST(test_indicator_set_state_fix_off);
#endif
}
