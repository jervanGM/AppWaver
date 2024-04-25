#ifndef IND_CODEC_H_
#define IND_CODEC_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_ind_data.h"

void ind_init();

void set_indicator_state( EIndId_t id,EIndSts_t state);

#endif /* IND_CODEC_H_ */