#include "pwm_port.h"
#include "pwm_drv.h"

/* Declarations of static functions */
static int8_t pwm_port_init(int gpio, uint8_t pwm_chan, uint32_t freq);   // Initialize PWM port
static int8_t pwm_port_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts);  // Set PWM parameters
static int8_t pwm_port_deinit(uint8_t pwm_chan);  // Deinitialize PWM port

/* Definition of the PWM port interface */
static const IPwmPort bus_port_interface = {
    .init = pwm_port_init,     // Initialize function pointer
    .set = pwm_port_set,       // Set function pointer
    .deinit = pwm_port_deinit  // Deinitialize function pointer
};

/* Function to initialize the PWM port */
static int8_t pwm_port_init(int gpio, uint8_t pwm_chan, uint32_t freq)
{
    return pwm_init(gpio, pwm_chan, freq);
}

/* Function to set PWM parameters */
static int8_t pwm_port_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts)
{
    return pwm_set(pwm_chan, duty, sts);
}

/* Function to deinitialize the PWM port */
static int8_t pwm_port_deinit(uint8_t pwm_chan)
{
    return pwm_deinit(pwm_chan);
}

/* Function to retrieve the PWM port interface */
const IPwmPort *hal_pwm_get_port(void)
{
    const IPwmPort *port = &bus_port_interface;  // Pointer to the PWM port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL && 
        port->set != NULL && 
        port->deinit != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}
