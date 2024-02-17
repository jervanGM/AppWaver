#ifndef DSP_H_
#define DSP_H_
#include <stdlib.h>

uint8_t getDSPData();
void iirFilter(uint32_t *input);
uint8_t dataNormalization(uint32_t input);

#endif /* DSP_H_ */