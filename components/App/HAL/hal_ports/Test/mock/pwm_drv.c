#include "pwm_drv.h"

static uint8_t init_error = 0;
static uint8_t deinit_error = 0;
static uint8_t write_error = 0;

int8_t pwm_init(int gpio, uint8_t pwm_chan, uint32_t freq) {
  // Prepare and apply LEDC timer configuration
  return init_error;
}

int8_t pwm_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts) {
  return write_error;
}

int8_t pwm_deinit(uint8_t pwm_chan) {
  return deinit_error;
}

void set_errors(uint8_t init_err, uint8_t deinit_err, uint8_t write_err)
{
    init_error = init_err;
    deinit_error = deinit_err;
    write_error = write_err;
}