#include "io_port.h"
#include "io_cfg.h"
#include "io_drv.h"

/* Declarations of static functions */
static void io_port_init(uint8_t io_pin, io_mode_t mode, bool pull_mode);    // Function to initialize the analog port
static void io_port_init_it(uint8_t io_pin, io_it_type_t intr_type, io_isr_handler_t isr_handler);   // Function to initialize the analog port
static void io_port_enable_it(void);    // Function to initialize the analog port
static void io_port_disable_it(void);    // Function to initialize the analog port
static void io_port_reset(uint8_t io_pin);   // Function to reset the analog port
static int8_t io_port_write(uint8_t io_pin, uint32_t value);   // Function to read data from the analog port
static uint32_t io_port_read(uint8_t io_pin);   // Function to write data to the analog port

/* Definition of the analog port interface */
static const IIOPort io_port_interface = {
    .init = io_port_init,    // Initialize function pointer
    .init_io_it = io_port_init_it,
    .enable_it = io_port_enable_it,
    .disable_it = io_port_disable_it,
    .reset = io_port_reset,  // Reset function pointer
    .read = io_port_read,    // Read function pointer
    .write = io_port_write   // Write function pointer
};

static void io_port_init(uint8_t io_pin, io_mode_t mode, bool pull_mode)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    gpio_mode_t gpio_mode = (gpio_mode_t)mode;
    config_gpio(gpio_pin, gpio_mode, pull_mode);
}

static void io_port_init_it(uint8_t io_pin, io_it_type_t intr_type, io_isr_handler_t isr_handler)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    gpio_int_type_t it_type = (gpio_int_type_t) intr_type;
    config_gpio_it(gpio_pin, it_type, isr_handler);
}

static void io_port_enable_it(void)
{
    io_enable_it();
}

static void io_port_disable_it(void)
{
    io_disable_it();
}
static void io_port_reset(uint8_t io_pin)
{
    gpio_num_t gpio_pin = (gpio_num_t)io_pin;
    io_reset(gpio_pin);
}

static uint32_t io_port_read(uint8_t io_pin)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    return io_read(gpio_pin);
}

static int8_t io_port_write(uint8_t io_pin, uint32_t value)
{
    gpio_num_t gpio_pin = (gpio_num_t) io_pin;
    return io_write(gpio_pin, value);
}

/* Function to retrieve the input/output port interface */
const IIOPort *hal_io_get_port(void)
{
    const IIOPort *port = &io_port_interface;  // Pointer to the analog port interface

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