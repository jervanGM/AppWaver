#ifndef ADC_DRV_H_
#define ADC_DRV_H_
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "adc_cfg.h"

void read_adc(uint8_t channel,uint32_t * data);

void set_adc_value(uint32_t data);

#endif /* ADC_DRV_H_ */