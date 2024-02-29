#include "adc_cfg.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"

static bool init;

void adc_config_init()
{
    init = true;
}

void adc_config_reset()
{
    init = false;
}

bool is_init()
{
    return init;
}