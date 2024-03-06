#include "wls_port.h"
#include "wls_drv.h"
#include "ota_drv.h"

/* Declarations of static functions */
static void wls_port_init(void);    // Function to initialize the wireless port
static void wls_port_reset(void);   // Function to reset the wireless port
static void wls_port_get_mac(uint8_t *mac);
static void wls_system_abort(const char *msg);
static void wls_connect();
static void wls_disconnect();
static void wls_port_receive(uint8_t channel, uint32_t *data);   // Function to read data from the wireless port
static void wls_port_send(uint8_t channel, uint32_t data);   // Function to write data to the wireless port

/* Definition of the wireless port interface */
static const IWlsPort wls_port_interface = {
    .init = wls_port_init,    // Initialize function pointer
    .reset = wls_port_reset,  // Reset function pointer
    .get_mac = wls_port_get_mac,  // Reset function pointer
    .system_abort = wls_system_abort,
    .connect = wls_connect,
    .disconnect = wls_disconnect,
    .receive = wls_port_receive,    // Read function pointer
    .send = wls_port_send   // Write function pointer
};

/* Function to initialize the wireless port */
static void wls_port_init(void)
{
    wifi_initialize();
}

/* Function to reset the wireless port */
static void wls_port_reset(void)
{
    wifi_deinitialize();
}

static void wls_port_get_mac(uint8_t *mac)
{
    mac_get_default(mac);
}

static void wls_system_abort(const char *msg)
{
    wireless_system_abort(msg);
}

static void wls_connect()
{
    wifi_connect();
}

static void wls_disconnect()
{
    wifi_disconnect();
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
        port->get_mac !=NULL &&
        port->system_abort != NULL &&
        port->connect != NULL &&
        port->disconnect != NULL &&
        port->receive != NULL && 
        port->send != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
