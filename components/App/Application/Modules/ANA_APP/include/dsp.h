#ifndef DSP_H_
#define DSP_H_
#include <stdlib.h>

c_uint8_t getDSPData();
void iirFilter(c_uint32_t *input);
c_uint8_t dataNormalization(c_uint32_t input);

#endif /* DSP_H_ */