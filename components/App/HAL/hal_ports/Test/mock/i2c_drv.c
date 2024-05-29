#include "i2c_drv.h"

static uint8_t init_error = 0;
static uint8_t deinit_error = 0;
static uint8_t write_error = 0;
static uint8_t read_error = 0;
static uint8_t temp_data = 0;
static uint8_t temp_reg = 0;

static uint8_t reg_data[MAX_DEV_NUM][MAX_REG_NUM] = {0};


int8_t i2c_bus_init(void)
{
    return init_error;
}


int8_t i2c_read_register(uint8_t dev_addrs, uint8_t *data, size_t len)
{
    if(len == 1)
    {
        *data = reg_data[dev_addrs][temp_reg];
    }
    else
    {
        for(int i=0; i<len; i++)
        {
            data[i] = reg_data[dev_addrs][temp_reg + i];
        }
    }
    
    return read_error;
}


int8_t i2c_write_register(uint8_t dev_addrs, uint8_t *data, size_t len)
{
    if(len == 1)
    {
        temp_reg  = *data;
    }
    else
    {
        temp_reg  = data[0];
    }
    return write_error;
}

int8_t i2c_bus_deinit()
{
    return deinit_error;
}

void set_errors(uint8_t init_err, uint8_t deinit_err, uint8_t read_err, uint8_t write_err)
{
    init_error = init_err;
    deinit_error = deinit_err;
    read_error = read_err;
    write_error = write_err;
}

void set_read_data(uint8_t dev_addr, uint8_t reg, uint8_t data)
{
    reg_data[dev_addr][reg] = data;
}
