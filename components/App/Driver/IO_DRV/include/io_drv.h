#ifndef IO_DRV_H_
#define IO_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "driver/gpio.h"

/**
 * @brief Write a value to the specified GPIO pin.
 *
 * @param io_pin GPIO pin number.
 * @param value Value to write (0 or 1).
 * @return 0 on success, -1 on failure.
 */
int8_t io_write(gpio_num_t io_pin, uint32_t value);

/**
 * @brief Read the current value of the specified GPIO pin.
 *
 * @param io_pin GPIO pin number.
 * @return Current value of the GPIO pin (0 or 1).
 */
uint32_t io_read(gpio_num_t io_pin);

#endif /* IO_DRV_H_ */