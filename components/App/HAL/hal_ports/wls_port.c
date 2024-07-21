#include "wls_port.h"
#include "wls_drv.h"
#include "ota_drv.h"

/* Declarations of static functions */
static int8_t wls_port_init(void);    // Function to initialize the wireless port
static int8_t wls_port_reset(void);   // Function to reset the wireless port
static int8_t wls_port_get_mac(uint8_t *mac);  // Function to retrieve the MAC address
static void wls_system_abort(const char *msg); // Function to abort the system
static int8_t wls_connect(void); // Function to connect to a wireless network
static int8_t wls_disconnect(void); // Function to disconnect from a wireless network
static void wls_port_receive(uint8_t channel, uint32_t *data);   // Function to receive data from the wireless port
static void wls_port_send(uint8_t channel, uint32_t data);   // Function to send data through the wireless port
static int32_t get_wifi_event(void); // Function to get the last WiFi event ID

/* Definition of the wireless port interface */
static const IWlsPort wls_port_interface = {
    .init = wls_port_init,    // Initialize function pointer
    .reset = wls_port_reset,  // Reset function pointer
    .get_mac = wls_port_get_mac,  // Get MAC address function pointer
    .system_abort = wls_system_abort, // System abort function pointer
    .connect = wls_connect, // Connect function pointer
    .disconnect = wls_disconnect, // Disconnect function pointer
    .get_wifi_event = get_wifi_event, // Get WiFi event function pointer
    .receive = wls_port_receive,    // Receive function pointer
    .send = wls_port_send   // Send function pointer
};

/* Function to initialize the wireless port */
static int8_t wls_port_init(void)
{
    return wifi_initialize(); // Call WiFi initialization function
}

/* Function to reset the wireless port */
static int8_t wls_port_reset(void)
{
    return wifi_deinitialize(); // Call WiFi deinitialization function
}

/* Function to retrieve the MAC address from the wireless port */
static int8_t wls_port_get_mac(uint8_t *mac)
{
    return mac_get_default(mac); // Call function to get MAC address
}

/* Function to abort the system operation */
static void wls_system_abort(const char *msg)
{
    wireless_system_abort(msg); // Call function to abort system operation
}

/* Function to connect to a wireless network */
static int8_t wls_connect(void)
{
    return wifi_connect(); // Call function to connect to WiFi network
}

/* Function to disconnect from a wireless network */
static int8_t wls_disconnect(void)
{
    return wifi_disconnect(); // Call function to disconnect from WiFi network
}

static int32_t get_wifi_event()
{
    return get_last_wifi_event_id();
}

/* Function to receive data from the wireless port */
static void wls_port_receive(uint8_t channel, uint32_t *data)
{
    // To be implemented based on wireless driver functionality
}

/* Function to send data through the wireless port */
static void wls_port_send(uint8_t channel, uint32_t data)
{
    // To be implemented based on wireless driver functionality
}

/* Function to retrieve the wireless port interface */
const IWlsPort *hal_wls_get_port(void)
{
    const IWlsPort *port = &wls_port_interface;  // Pointer to the wireless port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->reset != NULL && 
        port->get_mac != NULL &&
        port->system_abort != NULL &&
        port->connect != NULL &&
        port->disconnect != NULL &&
        port->receive != NULL && 
        port->send != NULL &&
        port->get_wifi_event != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
