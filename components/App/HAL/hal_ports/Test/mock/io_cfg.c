#include "io_cfg.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"

void config_gpio(gpio_num_t io_pin, gpio_mode_t mode, bool pull_mode)
{
    return;
}

void config_gpio_it(gpio_num_t io_pin, gpio_int_type_t intr_type, gpio_isr_t isr_handler)
{
    return;
}

void io_enable_it()
{
    return;
}

void io_disable_it()
{
    return;
}

void io_reset(gpio_num_t io_pin)
{
    return;
}