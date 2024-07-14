#ifndef PWM_DRV_H_
#define PWM_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "driver/ledc.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define IDLE_LEVEL              0

/**
 * @brief Initialize PWM channel.
 * 
 * This function initializes a PWM channel with the specified GPIO pin and frequency.
 * 
 * @param gpio GPIO number to use for PWM output.
 * @param pwm_chan PWM channel number.
 * @param freq PWM frequency in Hz.
 * @return 0 on success, -1 on failure.
 */
int8_t pwm_init(int gpio, uint8_t pwm_chan, uint32_t freq);

/**
 * @brief Set duty cycle for a PWM channel.
 * 
 * This function sets the duty cycle (percentage) for a PWM channel.
 * 
 * @param pwm_chan PWM channel number.
 * @param duty Duty cycle percentage (0-100).
 * @param sts Status flag (1: enable PWM, 0: disable PWM).
 * @return 0 on success, -1 on failure.
 */
int8_t pwm_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts);

/**
 * @brief Deinitialize a PWM channel.
 * 
 * This function stops and deinitializes a PWM channel.
 * 
 * @param pwm_chan PWM channel number.
 * @return 0 on success, -1 on failure.
 */
int8_t pwm_deinit(uint8_t pwm_chan);

#endif /* PWM_DRV_H_ */