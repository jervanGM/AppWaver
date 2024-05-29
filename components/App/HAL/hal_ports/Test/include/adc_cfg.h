#ifndef ADC_CFG_H_
#define ADC_CFG_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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

#define READ_LEN                    256



int8_t adc_config_init();
int8_t adc_config_reset();

bool is_init();

void set_cfg_error(int8_t init_err, int8_t reset_err);

#endif /* ADC_CFG_H_ */