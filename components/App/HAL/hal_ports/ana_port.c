#include "ana_port.h"
#include "adc_cfg.h"
#include "adc_drv.h"

/* Retrieves the analog port interface */
const IAnaPort *hal_ana_get_port(void) {
    const IAnaPort *port = &ana_port_interface;

    // Check if all members of the structure pointed by 'port' are initialized
    if (port->init != NULL &&
        port->reset != NULL &&
        port->read != NULL &&
        port->write != NULL) {
        // The structure is not empty
        return port;
    } else {
        // The structure is empty or not all members are initialized
        return NULL;
    }
}

/* Initializes the analog port */
static void ana_port_init(void)
{
    adc_config_init();
}

/* Resets the analog port */
static void ana_port_reset(void)
{
    adc_config_reset();
}

/* Reads data from the analog port */
static void ana_port_read(uint8_t channel,uint32_t * data)
{
    read_adc(channel,data);
}

/* Writes data to the analog port */
static void ana_port_write(uint8_t channel,uint32_t data)
{
    // To be determined
}
