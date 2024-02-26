#include "adc_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdint.h>

static uint32_t _read_data;

void read_adc(uint8_t channel,uint32_t * data)
{
    *data = _read_data;
}

void set_adc_value(uint32_t data)
{
    _read_data = data;
}
