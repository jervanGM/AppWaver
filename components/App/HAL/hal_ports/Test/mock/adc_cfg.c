#include "adc_cfg.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"

static bool init;
static int8_t init_error;
static int8_t reset_error;

int8_t adc_config_init()
{
    init = true;
    return init_error;
}

int8_t adc_config_reset()
{
    init = false;
    return reset_error;
}

bool is_init()
{
    return init;
}

void set_cfg_error(int8_t init_err, int8_t reset_err)
{
    init_error = init_err;
    reset_error = reset_err;
}