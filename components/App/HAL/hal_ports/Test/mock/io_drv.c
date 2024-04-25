#include "io_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdint.h>

static uint32_t _read_data;

int8_t io_write(gpio_num_t io_pin, uint32_t value)
{
    _read_data = value;
    return 0;
}

uint32_t io_read(gpio_num_t io_pin)
{
    return _read_data;
}
