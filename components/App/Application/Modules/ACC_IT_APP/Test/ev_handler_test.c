#include "ev_handler_test.h"
#include "safe_memory.h"
#include "safe_trace.h"
#include "ev_handler.h"
#include "i2c_drv.h"
#include <windows.h>
#include <pthread.h> 
#include "bus_port.h"
#include "fff.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef FAKE_FUNC
    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(const IBusPort *, hal_bus_get_port);
    // Test for verifying the initialization error handling of the DSP module.
    void test_handle_port_error()
    {
        // Perform DSP module initialization
        EIntCmd_t cmd;
        cmd = acc_it_handle_pulse();
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(ACC_IT_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_ACC_IT_CONFIG_ERROR);
        TEST_ASSERT_EQUAL(cmd, EV_FAIL);
    }

#endif

#ifndef FAKE_FUNC

static init_registers()
{
    set_errors(0, 0, 0, 0);
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            set_read_data(i,j,0);
        }
    }
}

void test_acc_it1_handle_pulse() {

    init_registers();
    EIntCmd_t cmd;
    // Simula la presión del botón
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_INT1_SRC,85);

    cmd = acc_it_handle_pulse();

    TEST_ASSERT_EQUAL(cmd,ACT_IT1);
}


void test_acc_it2_handle_pulse() {

    init_registers();
    EIntCmd_t cmd;
    // Simula la presión del botón
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_INT2_SRC,85);

    cmd = acc_it_handle_pulse();

    TEST_ASSERT_EQUAL(cmd,ACT_IT2);
}

void test_acc_unk_handle_pulse() {

    init_registers();
    EIntCmd_t cmd;

    cmd = acc_it_handle_pulse();

    TEST_ASSERT_EQUAL(cmd,ACT_UNK);
}

void test_acc_int1_read_error()
{
    init_registers();
    EIntCmd_t cmd;
    
    // Simula error en la lectura del registro INT1
    set_errors(0, 0, READ_ERROR, 0);
    
    cmd = acc_it_handle_pulse();
    
    TEST_ASSERT_EQUAL(cmd, EV_FAIL);
}

void test_acc_it1_threshold_exact()
{
    init_registers();
    EIntCmd_t cmd;
    // Simula la lectura del registro INT1 justo en el umbral
    set_read_data(LIS3DH_DEFAULT_ADDR, LIS3DH_INT1_SRC, IT1_THESHOLD);

    cmd = acc_it_handle_pulse();

    // Dependiendo de la lógica del umbral, verifica si el resultado es ACT_IT1 o ACT_UNK
    TEST_ASSERT_EQUAL(cmd, ACT_IT1); // Ajusta según la lógica deseada
}

void test_acc_it2_threshold_exact()
{
    init_registers();
    EIntCmd_t cmd;
    
    // Simula la lectura del registro INT2 justo en el umbral
    set_read_data(LIS3DH_DEFAULT_ADDR, LIS3DH_INT2_SRC, IT2_THESHOLD);

    cmd = acc_it_handle_pulse();

    // Dependiendo de la lógica del umbral, verifica si el resultado es ACT_IT2 o ACT_UNK
    TEST_ASSERT_EQUAL(cmd, ACT_IT2); // Ajusta según la lógica deseada
}

void test_acc_combined_read_write_errors()
{
    init_registers();
    EIntCmd_t cmd;

    // Simula error de escritura en el registro INT1
    set_errors(0, 0, 0, WRITE_ERROR);

    cmd = acc_it_handle_pulse();

    // Verifica que el resultado es un fallo
    TEST_ASSERT_EQUAL(cmd, EV_FAIL);

    // Simula error de lectura en el registro INT2
    set_errors(0, 0, READ_ERROR, 0);

    cmd = acc_it_handle_pulse();

    // Verifica que el resultado es un fallo
    TEST_ASSERT_EQUAL(cmd, EV_FAIL);
}

void test_acc_multiple_read_errors()
{
    init_registers();
    EIntCmd_t cmd;

    // Simula errores de lectura consecutivos en INT1 e INT2
    set_errors(0, 0, READ_ERROR, 0);

    cmd = acc_it_handle_pulse();

    // Verifica que el resultado es un fallo
    TEST_ASSERT_EQUAL(cmd, EV_FAIL);

    // Asegúrate de que los errores se resetean adecuadamente
    set_errors(0, 0, 0, 0);

    // Verifica comportamiento normal después de resetear errores
    set_read_data(LIS3DH_DEFAULT_ADDR, LIS3DH_INT1_SRC, IT1_THESHOLD + 1);
    cmd = acc_it_handle_pulse();
    TEST_ASSERT_EQUAL(cmd, ACT_IT1);
}


#endif

void ev_handler_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
    RUN_TEST(test_acc_it1_handle_pulse);
    RUN_TEST(test_acc_it2_handle_pulse);
    RUN_TEST(test_acc_unk_handle_pulse);
    RUN_TEST(test_acc_int1_read_error);
    RUN_TEST(test_acc_it1_threshold_exact);
    RUN_TEST(test_acc_it2_threshold_exact);
    RUN_TEST(test_acc_combined_read_write_errors);
    RUN_TEST(test_acc_multiple_read_errors);
#endif
}
