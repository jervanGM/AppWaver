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

int8_t pwm_init(int gpio, uint8_t pwm_chan, uint32_t freq);

int8_t pwm_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts);

int8_t pwm_deinit(uint8_t pwm_chan);

#endif /* PWM_DRV_H_ */