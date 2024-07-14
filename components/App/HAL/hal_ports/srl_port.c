#include "srl_port.h"
#include "usb_drv.h"

/* Declarations of static functions */
static int8_t srl_port_init(void);   // Initialize serial port
static bool srl_port_is_connected(void);   // Check if serial port is connected
static void srl_port_read_cmd(uint8_t *data, uint32_t size);   // Read command from serial port
static int8_t srl_port_deinit(void);   // Deinitialize serial port

/* Definition of the serial port interface */
static const ISrlPort srl_port_interface = {
    .init = srl_port_init,    // Initialize function pointer
    .is_connected = srl_port_is_connected,   // Is connected function pointer
    .read_cmd = srl_port_read_cmd,    // Read command function pointer
    .deinit = srl_port_deinit   // Deinitialize function pointer
};

/* Function to initialize the serial port */
static int8_t srl_port_init(void)
{
    return usb_init();  // Call USB initialization function
}

/* Function to check if the serial port is connected */
static bool srl_port_is_connected(void)
{
    return usb_is_connected();  // Call USB connection status function
}

/* Function to read command from the serial port */
static void srl_port_read_cmd(uint8_t *data, uint32_t size)
{
    read_cmd(data, size);  // Call function to read command
}

/* Function to deinitialize the serial port */
static int8_t srl_port_deinit(void)
{
    return usb_deinit();  // Call USB deinitialization function
}

/* Function to retrieve the serial port interface */
const ISrlPort *hal_srl_get_port(void)
{
    const ISrlPort *port = &srl_port_interface;  // Pointer to the serial port interface

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

