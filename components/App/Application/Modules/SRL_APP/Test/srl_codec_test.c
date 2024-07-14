#include "srl_codec_test.h"
#include "safe_memory.h"
#include "serial_codec.h"
#include "srl_port.h"
#include "usb_drv.h"
#include "fff.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const ISrlPort *, hal_srl_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_handle_port_error()
    {
        // Perform DSP module initialization
        serial_init();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(SERIAL_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_SRL_CONFIG_ERROR);
    }
#endif

#ifndef FAKE_FUNC
    void test_serial_codec_init_error()
    {
        set_errors(-1, 0);
        serial_init();
        int8_t error = read_error_from_slot(SERIAL_ERROR_SLOT);
        TEST_ASSERT_EQUAL(error,SRL_codec_INIT_ERROR);
    }

    void test_serial_codec_deinit_error()
    {
        store_error_in_slot(SERIAL_ERROR_SLOT,0);   
        set_errors(0, -1);
        serial_deinit();
        int8_t error = read_error_from_slot(SERIAL_ERROR_SLOT);
        TEST_ASSERT_EQUAL(error,0);
    }

    void test_serial_codec_connection()
    {
        set_serial_connection(true);
        bool conn = serial_connected();
        TEST_ASSERT_EQUAL(conn,true);

        set_serial_connection(false);
        conn = serial_connected();
        TEST_ASSERT_EQUAL(conn,false);
    }
    
void test_serial_codec_correct_msg()
{
    SSerialCmd_t cmd;
    
    // Caso de prueba 1: Comando sin opción --force
    set_serial_msg("/system_off/");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    // Caso de prueba 2: Comando con opción --force
    set_serial_msg("/system_off --force/");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,1);

    // Caso de prueba 3: Comando con opción --force y texto adicional
    set_serial_msg("/system_off --force/done");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,1);

    // Caso de prueba 4: Comando con opción --force en una ubicación diferente
    set_serial_msg("example/system_off --force/done");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,1);

    // Caso de prueba 5: Comando con texto adicional pero sin opción --force
    set_serial_msg("example/system_off/done");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    // Caso de prueba 6: Comando con texto adicional después de la opción --force
    set_serial_msg("/system_off --force/done_extra");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,1);

    // Caso de prueba 7: Comando con texto adicional antes de la opción --force
    set_serial_msg("/extra_text/system_off --force/");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"extra_text"),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    // Caso de prueba 8: Comando vacío
    set_serial_msg("/");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,""),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    // Caso de prueba 9: Comando con texto adicional después de la primera barra
    set_serial_msg("/extra_text/");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"extra_text"),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    set_serial_msg("system_off");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,0);

    set_serial_msg("system_off --force");
    cmd = serial_process_cmd();
    TEST_ASSERT_EQUAL(strcmp(cmd.cmd,"system_off"),0);
    TEST_ASSERT_EQUAL(cmd.force,1);
}


#endif

void srl_codec_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_serial_codec_init_error);
    RUN_TEST(test_serial_codec_deinit_error);
    RUN_TEST(test_serial_codec_connection);
    RUN_TEST(test_serial_codec_correct_msg);
#endif
}
