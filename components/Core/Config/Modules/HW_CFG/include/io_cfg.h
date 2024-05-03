#ifndef IO_CFG_H_
#define IO_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "driver/gpio.h"

#define ESP_INTR_FLAG_DEFAULT 0

void config_gpio(gpio_num_t io_pin, gpio_mode_t mode, bool pull_mode);

void config_gpio_it(gpio_num_t io_pin, gpio_int_type_t intr_type, gpio_isr_t isr_handler);

void io_enable_it();

void io_disable_it();

void io_reset(gpio_num_t io_pin);

#endif /* IO_CFG_H_ */