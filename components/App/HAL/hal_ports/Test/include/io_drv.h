#ifndef ADC_DRV_H_
#define ADC_DRV_H_
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "io_cfg.h"

int8_t io_write(gpio_num_t io_pin, uint32_t value);

uint32_t io_read(gpio_num_t io_pin);

#endif /* ADC_DRV_H_ */