#include "ota_port.h"
#include "ota_drv.h"


/* Declarations of static functions */
static int8_t ota_port_init(void);    // Function to initialize the wireless port
static void ota_port_update_reboot(void);
static void ota_port_reset(void);
static int8_t ota_port_finish(void);
static int8_t ota_port_upgrade(void);
static int8_t ota_port_write(const void *data, size_t length);
static int8_t ota_port_update_intall();


/* Definition of the wireless port interface */
static const IOtaPort ota_port_interface = {
    .init = ota_port_init,    // Initialize function pointer
    .reset = ota_port_reset,
    .finish = ota_port_finish,
    .upgrade = ota_port_upgrade,
    .update_install = ota_port_update_intall,
    .update_reboot = ota_port_update_reboot,
    .write = ota_port_write
};

/* Function to initialize the wireless port */
static int8_t ota_port_init(void)
{
    return ota_init();
}

static void ota_port_update_reboot()
{
    ota_update_reboot();
}

static void ota_port_reset(void)
{
    ota_abort();
}

static int8_t ota_port_finish(void)
{
    return ota_end();
}

static int8_t ota_port_write(const void *data, size_t length)
{
    return ota_write(data,length);
}

static int8_t ota_port_upgrade(void)
{
    return ota_upgrade();
}

static int8_t ota_port_update_intall(void)
{
    return ota_update_install();
}

/* Function to retrieve the wireless port interface */
const IOtaPort *hal_ota_get_port(void)
{
    const IOtaPort *port = &ota_port_interface;  // Pointer to the wireless port interface

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