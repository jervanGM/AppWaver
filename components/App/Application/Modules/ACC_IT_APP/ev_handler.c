#include "ev_handler.h"
#include "io_port.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "bus_port.h"
#include "rtos.h"

static const IBusPort *acc_bus_port;

/* Reads a register from a device */
static int8_t read_register(uint8_t dev_addrs, uint8_t registr, uint8_t *data)
{
    uint8_t reg = registr;
    if(acc_bus_port->write_reg(dev_addrs, &reg, 1) == ACC_IT_DRV_OK)
    {
        if(acc_bus_port->read_reg(dev_addrs, data, 1) != ACC_IT_DRV_OK)
        {
            store_error_in_slot(ACC_IT_ERROR_SLOT, READ_ERROR);  // Log read error
            return -1;            
        }
    }
    else
    {
        store_error_in_slot(ACC_IT_ERROR_SLOT, WRITE_ERROR);  // Log write error
        return -1;    
    }
    return 0;
}

/* Handles an interrupt pulse */
EIntCmd_t acc_it_handle_pulse()
{
    acc_bus_port = hal_bus_get_port();

    /*Checks for any IT event*/
    if (acc_bus_port != NULL)
    {
        return ACT_IT1;
    }
    else
    {
        store_error_in_slot(ACC_IT_ERROR_SLOT, HAL_ACC_IT_CONFIG_ERROR);  // Log configuration error
        TRACE_ERROR("Serial HAL port has not been configured correctly on init");
    }
    return EV_FAIL;
}