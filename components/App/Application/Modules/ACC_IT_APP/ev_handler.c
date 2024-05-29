#include "ev_handler.h"
#include "io_port.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "bus_port.h"
#include "rtos.h"

static const IBusPort *acc_bus_port;

static int8_t read_register(uint8_t dev_addrs, uint8_t registr, uint8_t *data)
{
    uint8_t reg = registr;
    if(acc_bus_port->write_reg(dev_addrs,&reg,1) == ACC_IT_DRV_OK)
    {
        if(acc_bus_port->read_reg(dev_addrs,data,1) != ACC_IT_DRV_OK)
        {
            store_error_in_slot(ACC_IT_ERROR_SLOT,READ_ERROR);
            return -1;            
        }
    }
    else
    {
        store_error_in_slot(ACC_IT_ERROR_SLOT,WRITE_ERROR);
        return -1;    
    }
    return 0;
}

EIntCmd_t acc_it_handle_pulse()
{
    acc_bus_port = hal_bus_get_port();

    if (acc_bus_port != NULL)
    {
        uint8_t data = 0;
        if(read_register(LIS3DH_DEFAULT_ADDR,LIS3DH_INT1_SRC, &data) != ACC_IT_DRV_OK)
        {
            return EV_FAIL;
        }
        if(data >= IT1_THESHOLD)
        {
            return ACT_IT1;
        }

        data = 0;
        if(read_register(LIS3DH_DEFAULT_ADDR,LIS3DH_INT2_SRC, &data) != ACC_IT_DRV_OK)
        {
            return EV_FAIL;
        }
        if(data >= IT2_THESHOLD)
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