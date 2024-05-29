#ifndef PWM_DRV_H_
#define PWM_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int8_t pwm_init(int gpio, uint8_t pwm_chan, uint32_t freq);

int8_t pwm_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts);

int8_t pwm_deinit(uint8_t pwm_chan);

void set_errors(uint8_t init_err, uint8_t deinit_err, uint8_t write_err);

#endif /* PWM_DRV_H_ */