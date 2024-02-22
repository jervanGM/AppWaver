#ifndef DSP_H_
#define DSP_H_
#include <stdlib.h>
#include "gen_types.h"

void dsp_init_port();
uint8_t get_dsp_data();
void iir_filter(uint32_t *input);
uint8_t data_normalization(uint32_t input);

#endif /* DSP_H_ */