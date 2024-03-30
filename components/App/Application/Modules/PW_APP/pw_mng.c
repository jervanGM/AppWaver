#include "pw_mng.h"
#include "io_port.h"
#include "safe_trace.h"
#include "safe_memory.h"

/* Initializes the power module */
void pw_init()
{
    // Retrieve the IO port interface
    const IIOPort *port = hal_io_get_port();

    // Check if the port interface is valid
    if (port != NULL)
    {
        port->init(POWER_OFF_PIN,IO_OUTPUT,false);
        port->write(POWER_OFF_PIN,0);
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(POWER_ERROR_SLOT, HAL_PW_CONFIG_ERROR);
        TRACE_ERROR("Analog sensor HAL port has not been configured correctly on init");
    }
}
