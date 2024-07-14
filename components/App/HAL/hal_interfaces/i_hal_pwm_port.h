#ifndef I_HAL_PWM_PORT_H_
#define I_HAL_PWM_PORT_H_

#include <stdint.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for PWM (Pulse Width Modulation) Ports.
 * 
 * This interface defines functions for PWM operations in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(int gpio, uint8_t pwm_chan, uint32_t freq); /**< Function pointer to initialize PWM port. */
    int8_t (*set)(uint8_t pwm_chan, uint8_t duty, uint8_t sts); /**< Function pointer to set PWM parameters. */
    int8_t (*deinit)(uint8_t pwm_chan); /**< Function pointer to deinitialize PWM port. */
} IPwmPort;

#endif /* I_HAL_PWM_PORT_H_ */
