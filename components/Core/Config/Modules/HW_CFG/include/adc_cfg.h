#ifndef ADC_CFG_H_
#define ADC_CFG_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_adc/adc_continuous.h"
#include "soc/soc_caps.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define ADC_UNIT                    ADC_UNIT_1
#define _ADC_UNIT_STR(unit)         #unit
#define ADC_UNIT_STR(unit)          _ADC_UNIT_STR(unit)
#define ADC_CONV_MODE               ADC_CONV_SINGLE_UNIT_1
#define ADC_ATTEN                   ADC_ATTEN_DB_0
#define ADC_BIT_WIDTH               SOC_ADC_DIGI_MAX_BITWIDTH

#define ADC_OUTPUT_TYPE             ADC_DIGI_OUTPUT_FORMAT_TYPE2
#define ADC_GET_CHANNEL(p_data)     ((p_data)->type2.channel)
#define ADC_GET_DATA(p_data)        ((p_data)->type2.data)

#define ADC1_CHAN0          ADC_CHANNEL_2

#define ADC_ATTEN           ADC_ATTEN_DB_11

static const char *TAG = "ADC";

#define READ_LEN                    256

static adc_channel_t channel[1] = {ADC_CHANNEL_2};

static void continuous_adc_init(adc_channel_t *channel, uint8_t channel_num, adc_continuous_handle_t *out_handle);
static bool adc_calibration_ana_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);
static void adc_calibration_deinit(adc_cali_handle_t handle);
void adc_config_init();
void adc_config_reset();

#endif /* ADC_CFG_H_ */