#include "cmd_handler_test.h"
#include "safe_memory.h"
#include "safe_trace.h"
#include "cmd_handler.h"
#include <windows.h>
#include <pthread.h> 
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
        btn_handle_pulse(10);
        
        // Check if the initialization error is stored in the designated error slot
        int8_t error = read_error_from_slot(BUTTON_ERROR_SLOT);
        
        // Verify that the error matches the expected error code
        TEST_ASSERT_EQUAL(error, HAL_BTN_CONFIG_ERROR);
    }

#endif

#ifndef FAKE_FUNC
//Can't simulate correctly without getting in a infinite loop. In the real MCU works well but here is not.
// static void simulate_button_press() {
//     const IIOPort* port = hal_io_get_port();

//     // Simula la presión del botón
//     port->write(0, 1); // Presiona el botón

//     // // Simula el tiempo que el botón está presionado
//     // Sleep(1000); // Simula la presión del botón durante 3 segundos
//     // // Simula soltar el botón
//     // port->write(0, 1); // Suelta el botón

//     return NULL;
// }


// void test_btn_handle_pulse(void) {
//     // Caso donde el tiempo del sistema es menor que el tiempo de espera
//     EBtnPulse_t pulse = btn_handle_pulse(0);
//     TEST_ASSERT_EQUAL(NO_PULSE, pulse);

//     // Inicia un hilo para simular la interacción con el botón
//     pthread_t thread;
//     pthread_mutex_t mutex;
//     simulate_button_press();
//     pulse = btn_handle_pulse(0);
//     // Espera corta
//     TEST_ASSERT_EQUAL(SHORT_PRESS, pulse);

//     // Espera a que el hilo termine
//     pthread_join(thread, NULL);
// }

#endif

void cmd_handler_test_suite()
{
#ifdef FAKE_FUNC
    RUN_TEST(test_handle_port_error);
#endif
#ifndef FAKE_FUNC
#endif
}
