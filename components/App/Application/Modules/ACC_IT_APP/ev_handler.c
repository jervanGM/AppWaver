#include "ev_handler.h"
#include "io_port.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "bus_port.h"
#include "rtos.h"

EIntCmd_t acc_it_handle_pulse()
{
    const IBusPort *bus_port = hal_bus_get_port();

    if (bus_port != NULL)
    {
        uint8_t reg = LIS3DH_INT1_SRC;
        uint8_t data = 0;
        bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
        bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&data,1);
        if(data > IT1_THESHOLD)
        {
            return ACT_IT1;
        }
        reg = LIS3DH_INT2_SRC;
        data = 0;
        bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
        bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&data,1);
        if(data > IT2_THESHOLD)
        {
            return ACT_IT2;
        }
        store_error_in_slot(ACC_IT_ERROR_SLOT,ACC_IT_CMD_ERROR);
        TRACE_ERROR("Unknown interrupt has been launched");
        return ACT_UNK;
    }
    else
    {
        store_error_in_slot(ACC_IT_ERROR_SLOT, HAL_ACC_IT_CONFIG_ERROR);
        TRACE_ERROR("Serial HAL port has not been configured correctly on init");
    }
    return EV_FAIL;
}