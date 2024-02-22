#include "ana_port.h"
#include "adc_cfg.h"
#include "adc_drv.h"

const IAnaPort * hal_ana_get_port(void)
{
    return & ana_port_interface;
}

static void ana_port_init(void)
{
    adc_config_init();
}

static void ana_port_reset(void)
{
    adc_config_reset();
}

static void ana_port_read(uint8_t channel,uint32_t * data)
{
    read_adc(channel,data);
}

static void ana_port_write(uint8_t channel,uint32_t data)
{
    //TBD
}