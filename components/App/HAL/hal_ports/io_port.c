#include "io_port.h"
#include "io_cfg.h"
#include "io_drv.h"

/* Declarations of static functions */
static void io_port_init(uint8_t io_pin, io_mode_t mode, bool pull_mode);    // Initializes the GPIO pin with specified mode and pull mode
static void io_port_init_it(uint8_t io_pin, io_it_type_t intr_type, io_isr_handler_t isr_handler);   // Initializes GPIO interrupt for the pin
static void io_port_enable_it(void);    // Enables GPIO interrupts
static void io_port_disable_it(void);    // Disables GPIO interrupts
static void io_port_reset(uint8_t io_pin);   // Resets the GPIO pin configuration
static int8_t io_port_write(uint8_t io_pin, uint32_t value);   // Writes a value to the GPIO pin
static uint32_t io_port_read(uint8_t io_pin);   // Reads the current value of the GPIO pin

/* Definition of the Input/Output port interface */
static const IIOPort io_port_interface = {
    .init = io_port_init,    // Initialize function pointer
    .init_io_it = io_port_init_it, //Initialize interruption function pointer
    .enable_it = io_port_enable_it, //Enable interruption function pointer
    .disable_it = io_port_disable_it, //Disable interruption function pointer
    .reset = io_port_reset,  // Reset function pointer
    .read = io_port_read,    // Read function pointer
    .write = io_port_write   // Write function pointer
};

// Initializes the GPIO pin with specified mode and pull mode
static void io_port_init(uint8_t io_pin, io_mode_t mode, bool pull_mode)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    gpio_mode_t gpio_mode = (gpio_mode_t) mode;
    config_gpio(gpio_pin, gpio_mode, pull_mode);
}

// Initializes GPIO interrupt for the pin
static void io_port_init_it(uint8_t io_pin, io_it_type_t intr_type, io_isr_handler_t isr_handler)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    gpio_int_type_t it_type = (gpio_int_type_t) intr_type;
    config_gpio_it(gpio_pin, it_type, isr_handler);
}

// Enables GPIO interrupts
static void io_port_enable_it(void)
{
    io_enable_it();
}

// Disables GPIO interrupts
static void io_port_disable_it(void)
{
    io_disable_it();
}

// Resets the GPIO pin configuration
static void io_port_reset(uint8_t io_pin)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    io_reset(gpio_pin);
}

// Reads the current value of the GPIO pin
static uint32_t io_port_read(uint8_t io_pin)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    return io_read(gpio_pin);
}

// Writes a value to the GPIO pin
static int8_t io_port_write(uint8_t io_pin, uint32_t value)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    return io_write(gpio_pin, value);
}

/* Function to retrieve the input/output port interface */
const IIOPort *hal_io_get_port(void)
{
    const IIOPort *port = &io_port_interface;  // Pointer to the Input/Output port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->init_io_it != NULL && 
        port->enable_it != NULL && 
        port->disable_it != NULL && 
        port->reset != NULL && 
        port->read != NULL && 
        port->write != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
