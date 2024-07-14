#ifndef MEM_DRV_H_
#define MEM_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_mem_data.h"

/**
 * @brief Initializes the memory driver.
 * 
 * Initializes the memory port and performs necessary setup operations,
 * including directory creation and file operations.
 */
void mem_drv_init();

/**
 * @brief Saves processed WAV data to the external memory.
 * 
 * @param wav SWavData structure containing WAV data to be saved.
 */
void save_wav_data(SWavData wav);

/**
 * @brief Deinitializes the memory driver.
 * 
 * Deinitializes the memory port and performs cleanup operations.
 */
void mem_drv_deinit();

#endif /* MEM_DRV_H_ */