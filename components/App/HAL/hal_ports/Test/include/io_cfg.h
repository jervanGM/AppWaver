#ifndef ADC_CFG_H_
#define ADC_CFG_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    GPIO_OUTPUT 
} gpio_mode_t;

typedef enum {
    GPIO_IT_DISABLE
} gpio_int_type_t;

typedef enum {
    GPIO_1
} gpio_num_t;

typedef void (*gpio_isr_t)(void *arg);

#define ESP_INTR_FLAG_DEFAULT 0

void config_gpio(gpio_num_t io_pin, gpio_mode_t mode, bool pull_mode);

void config_gpio_it(gpio_num_t io_pin, gpio_int_type_t intr_type, gpio_isr_t isr_handler);

void io_enable_it();

void io_disable_it();

void io_reset(gpio_num_t io_pin);

#endif /* ADC_CFG_H_ */