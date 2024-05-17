#include "esp_err.h"
#include "pwm_drv.h"

int8_t pwm_init(int gpio, uint8_t pwm_chan, uint32_t freq) {
  // Prepare and apply LEDC timer configuration
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_MODE,
    .duty_resolution = LEDC_DUTY_RES,
    .timer_num = LEDC_TIMER,
    .freq_hz = freq, // Set output frequency
    .clk_cfg = LEDC_AUTO_CLK,
  };
  if (ledc_timer_config(&ledc_timer) != ESP_OK) {
    return -1;
  }

  // Prepare and apply LEDC channel configuration
  ledc_channel_config_t ledc_channel = {
    .speed_mode = LEDC_MODE,
    .channel = (ledc_channel_t)pwm_chan,
    .timer_sel = LEDC_TIMER,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = gpio,
    .duty = 0, // Set initial duty to 0%
    .hpoint = 0,
  };
  if (ledc_channel_config(&ledc_channel) != ESP_OK) {
    return -1;
  }

  return 0;
}

int8_t pwm_set(uint8_t pwm_chan, uint8_t duty, uint8_t sts) {
  uint32_t converted_duty = sts ? (uint32_t)(1 << (uint8_t)LEDC_DUTY_RES) * (duty / 100.0) : 0;

    if (ledc_set_duty(LEDC_MODE, (ledc_channel_t)pwm_chan, converted_duty) != ESP_OK) {
    return -1;
    }
    if (ledc_update_duty(LEDC_MODE, (ledc_channel_t)pwm_chan) != ESP_OK) {
      return -1;
    }
    return 0;
}

int8_t pwm_deinit(uint8_t pwm_chan) {
  if (ledc_stop(LEDC_MODE, (ledc_channel_t)pwm_chan, IDLE_LEVEL) != ESP_OK) {
    return -1;
  }
  return 0;
}