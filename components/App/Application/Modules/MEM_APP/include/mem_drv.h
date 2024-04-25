#ifndef MEM_DRV_H_
#define MEM_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_mem_data.h"

void mem_drv_init();

void save_wav_data(SWavData wav);

void mem_drv_deinit();

#endif /* MEM_DRV_H_ */