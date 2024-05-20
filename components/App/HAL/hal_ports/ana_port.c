#include "ana_port.h"
#include "adc_cfg.h"
#include "adc_drv.h"

/* Declarations of static functions */
static int8_t ana_port_init(void);    // Function to initialize the analog port
static int8_t ana_port_reset(void);   // Function to reset the analog port
static int8_t ana_port_read(uint8_t channel, uint32_t *data);   // Function to read data from the analog port
static int8_t ana_port_write(uint8_t channel, uint32_t data);   // Function to write data to the analog port

/* Definition of the analog port interface */
static const IAnaPort ana_port_interface = {
    .init = ana_port_init,    // Initialize function pointer
    .reset = ana_port_reset,  // Reset function pointer
    .read = ana_port_read,    // Read function pointer
    .write = ana_port_write   // Write function pointer
};

/* Function to initialize the analog port */
static int8_t ana_port_init(void)
{
    return adc_config_init();  // Call the ADC initialization function
}

/* Function to reset the analog port */
static int8_t ana_port_reset(void)
{
    return adc_config_reset();  // Call the ADC reset function
}

/* Function to read data from the analog port */
static int8_t ana_port_read(uint8_t channel, uint32_t *data)
{
    return read_adc(channel, data);  // Call the ADC read function
}

/* Function to write data to the analog port */
static int8_t ana_port_write(uint8_t channel, uint32_t data)
{
    // To be determined
    return 0;
}

/* Function to retrieve the analog port interface */
const IAnaPort *hal_ana_get_port(void)
{
    const IAnaPort *port = &ana_port_interface;  // Pointer to the analog port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->reset != NULL && 
        port->read != NULL && 
        port->write != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
