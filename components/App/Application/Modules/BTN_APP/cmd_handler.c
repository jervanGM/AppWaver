#include "cmd_handler.h"
#include "io_port.h"
#include "safe_trace.h"
#include "safe_memory.h"

EBtnPulse_t btn_handle_pulse(uint8_t btn_pin)
{
    int64_t start_time = get_system_time();
    const IIOPort *port = hal_io_get_port();
    
    if (port != NULL)
    {
        if (get_system_time() > SYSTEM_INIT_WAIT_TIME)
        {
            while (!port->read(btn_pin));  // Wait until the button is pressed
            
            int64_t end_time = get_system_time();
            c_uint8_t button_time = end_time - start_time;  // Calculate button press duration
            
            //Checks which state is ac5tivated based on the duration calculated
            if (button_time < SHORT_PRESS_LIMIT)
            {
                return SHORT_PRESS; 
            }
            else if (button_time >= SHORT_PRESS_LIMIT && button_time < LONG_PRESS_LIMIT)
            {
                return LONG_PRESS;
            }
            else if (button_time > POWER_OFF_LIMIT)
            {
                return POWER_OFF;
            }
            else
            {
                return PULSE_ERR;
            }
        }
    }
    else
    {
        store_error_in_slot(BUTTON_ERROR_SLOT, HAL_BTN_CONFIG_ERROR);  // Log configuration error
        TRACE_ERROR("Button task IO HAL port has not been configured correctly on handle");
    }

    return NO_PULSE;
}