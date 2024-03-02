#include "wls_port.h"
#include "wls_cfg.h"
#include "wls_drv.h"

/* Declarations of static functions */
static void wls_port_init(void);    // Function to initialize the wireless port
static void wls_port_reset(void);   // Function to reset the wireless port
static void wls_port_receive(uint8_t channel, uint32_t *data);   // Function to read data from the wireless port
static void wls_port_send(uint8_t channel, uint32_t data);   // Function to write data to the wireless port

/* Definition of the wireless port interface */
static const IWlsPort wls_port_interface = {
    .init = wls_port_init,    // Initialize function pointer
    .reset = wls_port_reset,  // Reset function pointer
    .receive = wls_port_receive,    // Read function pointer
    .send = wls_port_send   // Write function pointer
};

/* Function to initialize the wireless port */
static void wls_port_init(void)
{

}

/* Function to reset the wireless port */
static void wls_port_reset(void)
{

}

/* Function to read data from the wireless port */
static void wls_port_receive(uint8_t channel, uint32_t *data)
{

}

/* Function to write data to the wireless port */
static void wls_port_send(uint8_t channel, uint32_t data)
{
    // To be determined
}

/* Function to retrieve the wireless port interface */
const IWlsPort *hal_wls_get_port(void)
{
    const IWlsPort *port = &wls_port_interface;  // Pointer to the wireless port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->reset != NULL && 
        port->receive != NULL && 
        port->send != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}