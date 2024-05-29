#ifndef I_HAL_PWM_PORT_H_
#define I_HAL_PWM_PORT_H_

#include <stdint.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for PWM Ports.
 * 
 * This interface defines the functions required to interact with pwm ports
 * in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(int gpio, uint8_t pwm_chan, uint32_t freq);
    int8_t (*set)(uint8_t pwm_chan, uint8_t duty, uint8_t sts);
    int8_t (*deinit)(uint8_t pwm_chan);
} IPwmPort;

#endif /* I_HAL_PWM_PORT_H_ */