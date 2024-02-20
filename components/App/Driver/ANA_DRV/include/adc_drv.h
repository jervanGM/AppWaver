#ifndef ADC_DRV_H_
#define ADC_DRV_H_
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
#include "adc_cfg.h"

static int adc_raw[2][10];
static int voltage[2][10];

void read_adc(c_uint8_t channel,c_uint32_t * data);

#endif /* ADC_DRV_H_ */