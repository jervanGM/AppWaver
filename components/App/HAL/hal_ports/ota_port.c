#include "ota_port.h"
#include "ota_drv.h"

/* Declarations of static functions */
static int8_t ota_port_init(void);    // Function to initialize the OTA port
static void ota_port_update_reboot(void);  // Function to initiate reboot after OTA update
static void ota_port_reset(void);  // Function to reset OTA process
static int8_t ota_port_finish(void);   // Function to finish OTA process
static int8_t ota_port_upgrade(void);  // Function to upgrade firmware via OTA
static int8_t ota_port_write(const void *data, size_t length);   // Function to write data during OTA update
static int8_t ota_port_update_install(void);   // Function to install OTA update

/* Definition of the OTA port interface */
static const IOtaPort ota_port_interface = {
    .init = ota_port_init,    // Initialize function pointer
    .reset = ota_port_reset,  // Reset function pointer
    .finish = ota_port_finish,    // Finish function pointer
    .upgrade = ota_port_upgrade,  // Upgrade function pointer
    .update_install = ota_port_update_install,    // Update install function pointer
    .update_reboot = ota_port_update_reboot,  // Update reboot function pointer
    .write = ota_port_write   // Write function pointer
};

/* Function to initialize the OTA port */
static int8_t ota_port_init(void)
{
    return ota_init();
}

/* Function to initiate reboot after OTA update */
static void ota_port_update_reboot(void)
{
    ota_update_reboot();
}

/* Function to reset OTA process */
static void ota_port_reset(void)
{
    ota_abort();
}

/* Function to finish OTA process */
static int8_t ota_port_finish(void)
{
    return ota_end();
}

/* Function to write data during OTA update */
static int8_t ota_port_write(const void *data, size_t length)
{
    return ota_write(data, length);
}

/* Function to upgrade firmware via OTA */
static int8_t ota_port_upgrade(void)
{
    return ota_upgrade();
}

/* Function to install OTA update */
static int8_t ota_port_update_install(void)
{
    return ota_update_install();
}

/* Function to retrieve the OTA port interface */
const IOtaPort *hal_ota_get_port(void)
{
    const IOtaPort *port = &ota_port_interface;  // Pointer to the OTA port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL &&
        port->reset != NULL &&
        port->finish != NULL &&
        port->upgrade != NULL &&
        port->update_install != NULL &&
        port->update_reboot != NULL &&
        port->write != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
