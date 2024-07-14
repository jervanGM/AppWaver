#ifndef IO_CFG_H_
#define IO_CFG_H_

#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "driver/gpio.h"

#define ESP_INTR_FLAG_DEFAULT 0

/**
 * @brief Configure a GPIO pin.
 * 
 * Configures a GPIO pin with the specified mode and pull mode.
 * 
 * @param io_pin GPIO number to configure.
 * @param mode GPIO mode (e.g., GPIO_MODE_INPUT, GPIO_MODE_OUTPUT).
 * @param pull_mode Pull mode (true for pull-up, false for pull-down).
 */
void config_gpio(gpio_num_t io_pin, gpio_mode_t mode, bool pull_mode);

/**
 * @brief Configure a GPIO pin with interrupt.
 * 
 * Configures a GPIO pin to generate interrupts of the specified type,
 * and assigns the ISR handler function.
 * 
 * @param io_pin GPIO number to configure.
 * @param intr_type Type of interrupt to generate (e.g., GPIO_INTR_POSEDGE, GPIO_INTR_NEGEDGE).
 * @param isr_handler ISR handler function to be called on interrupt.
 */
void config_gpio_it(gpio_num_t io_pin, gpio_int_type_t intr_type, gpio_isr_t isr_handler);

/**
 * @brief Enable GPIO interrupt handling.
 * 
 * Installs the GPIO ISR service.
 */
void io_enable_it();

/**
 * @brief Disable GPIO interrupt handling.
 * 
 * Uninstalls the GPIO ISR service.
 */
void io_disable_it();

/**
 * @brief Reset a GPIO pin.
 * 
 * Resets the specified GPIO pin, removing any configuration and ISR handler.
 * 
 * @param io_pin GPIO number to reset.
 */
void io_reset(gpio_num_t io_pin);

#endif /* IO_CFG_H_ */