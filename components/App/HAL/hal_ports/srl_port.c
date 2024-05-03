#include "srl_port.h"
#include "usb_drv.h"

/* Declarations of static functions */
static int8_t srl_port_init(void);    // Function to initialize the analog port
static bool srl_port_is_connected(void);   // Function to reset the analog port
static void srl_port_read_cmd(uint8_t *data, uint32_t size);   // Function to read data from the analog port
static int8_t srl_port_deinit(void);   // Function to read data from the analog port

/* Definition of the analog port interface */
static const ISrlPort srl_port_interface = {
    .init = srl_port_init,    // Initialize function pointer
    .is_connected = srl_port_is_connected,  // Reset function pointer
    .read_cmd = srl_port_read_cmd,    // Read function pointer
    .deinit = srl_port_deinit
};

/* Function to initialize the analog port */
static int8_t srl_port_init(void)
{
    return usb_init();  // Call the ADC initialization function
}

/* Function to reset the analog port */
static bool srl_port_is_connected(void)
{
    return usb_is_connected();  // Call the ADC reset function
}

/* Function to read data from the analog port */
static void srl_port_read_cmd(uint8_t *data, uint32_t size)
{
    read_cmd(data,size);
}

static int8_t srl_port_deinit()
{
    return usb_deinit();
}

/* Function to retrieve the analog port interface */
const ISrlPort *hal_srl_get_port(void)
{
    const ISrlPort *port = &srl_port_interface;  // Pointer to the analog port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->is_connected != NULL && 
        port->read_cmd != NULL &&
        port->deinit != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
