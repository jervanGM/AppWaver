#ifndef ADC_DRV_H_
#define ADC_DRV_H_
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include "adc_cfg.h"

int8_t read_adc(uint8_t channel,uint32_t * data);

void set_adc_value(uint32_t data);

void set_read_error(int8_t error);

#endif /* ADC_DRV_H_ */