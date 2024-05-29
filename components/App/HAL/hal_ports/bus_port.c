#include "bus_port.h"
#include "i2c_drv.h"

/* Declarations of static functions */
static int8_t bus_port_init(void);
static int8_t bus_port_write_reg(uint8_t dev_addrs, uint8_t *data, size_t len); 
static int8_t bus_port_read_reg(uint8_t dev_addrs, uint8_t *data, size_t len); 
static int8_t bus_port_deinit(void);

/* Definition of the analog port interface */
static const IBusPort bus_port_interface = {
    .init = bus_port_init,
    .write_reg = bus_port_write_reg,
    .read_reg = bus_port_read_reg,
    .deinit = bus_port_deinit
};

static int8_t bus_port_init(void)
{
    return i2c_bus_init();
}

static int8_t bus_port_write_reg(uint8_t dev_addrs, uint8_t *data, size_t len)
{
    return i2c_write_register(dev_addrs, data, len);
}

static int8_t bus_port_read_reg(uint8_t dev_addrs, uint8_t *data, size_t len)
{
    return i2c_read_register(dev_addrs, data, len);
}

static int8_t bus_port_deinit(void)
{
    return i2c_bus_deinit();
}

/* Function to retrieve the analog port interface */
const IBusPort *hal_bus_get_port(void)
{
    const IBusPort *port = &bus_port_interface;  // Pointer to the analog port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->write_reg != NULL && 
        port->read_reg != NULL && 
        port->deinit != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}