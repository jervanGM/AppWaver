#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "io_cfg.h"

void config_gpio(gpio_num_t io_pin, gpio_mode_t mode, bool pull_mode) {

    //Init GPIO configuration stucture
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = mode,
        .pin_bit_mask = (1ULL << io_pin),
        .pull_down_en = (pull_mode == false) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
        .pull_up_en = (pull_mode == true) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

}

void config_gpio_it(gpio_num_t gpio_pin, gpio_int_type_t it_type, gpio_isr_t isr_handler) {
    
    //Init GPIO interruption type and handler
    if (it_type != GPIO_INTR_DISABLE && isr_handler != NULL) {
        ESP_ERROR_CHECK(gpio_set_intr_type(gpio_pin, it_type));
        ESP_ERROR_CHECK(gpio_isr_handler_add(gpio_pin, isr_handler, (void*) gpio_pin));
    }
}

void io_enable_it()
{
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT));
}

void io_disable_it()
{
    gpio_uninstall_isr_service();
}

void io_reset(gpio_num_t gpio_pin) {
    
    gpio_reset_pin(gpio_pin);

    gpio_isr_handler_remove(gpio_pin);
}