#include "adc_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdint.h>

static uint32_t _read_data;
static int8_t read_error;

int8_t read_adc(uint8_t channel,uint32_t * data)
{
    *data = _read_data;
    return read_error;
}

void set_adc_value(uint32_t data)
{
    _read_data = data;
}

void set_read_error(int8_t error)
{
    read_error = error;
}