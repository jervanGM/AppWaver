#ifndef IO_DRV_H_
#define IO_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "driver/gpio.h"


int8_t io_write(gpio_num_t io_pin, uint32_t value);

uint32_t io_read(gpio_num_t io_pin);



#endif /* IO_DRV_H_ */