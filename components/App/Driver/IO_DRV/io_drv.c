#include "io_drv.h"

int8_t io_write(gpio_num_t io_pin, uint32_t value) {
    gpio_num_t gpio_pin = (gpio_num_t)io_pin;
    
    // Escribir en el pin GPIO
    if(gpio_set_level(gpio_pin, value) != ESP_OK)
    {
        return -1;
    }
    return 0;
}

uint32_t io_read(gpio_num_t io_pin) {
    gpio_num_t gpio_pin = (gpio_num_t)io_pin;
    
    return (uint32_t)gpio_get_level(gpio_pin);
}