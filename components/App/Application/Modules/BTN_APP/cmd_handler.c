#include "cmd_handler.h"
#include "io_port.h"

EBtnPulse_t btn_handle_pulse(uint8_t btn_pin)
{
    STime_t start_time = get_system_time();
    const IIOPort *port  = hal_io_get_port();
    if(get_system_time().sec > SYSTEM_INIT_WAIT_TIME)
    {
        while(!port->read(btn_pin))
        {
            if((start_time.sec - get_system_time().sec) > POWER_OFF_LIMIT )
            {
                return POWER_OFF;
            }
        }
        STime_t end_time = get_system_time();
        c_uint8_t button_time = end_time.sec - start_time.sec;
        if(button_time < SHORT_PRESS_LIMIT)
        {
                return SHORT_PRESS;
        }
        else if(button_time >= SHORT_PRESS_LIMIT && button_time < LONG_PRESS_LIMIT)
        {
                return LONG_PRESS;
        }
        else
        {
                return PULSE_ERR;
        }
    }
    return NO_PULSE;
}