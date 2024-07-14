#ifndef MEM_APP_H_
#define MEM_APP_H_

#include <stdbool.h>
#include "i_mem_data.h"

#define MINOR_FAULT_THRESHOLD -1
#define MAYOR_FAULT_THESHOLD -20

/**
 * @brief Initializes the default WAV header.
 */
void mem_app_init();

/**
 * @brief Processes raw data into a WAV file format.
 *
 * @param data Pointer to the data to be processed.
 * @param start_t Start time for data processing.
 * @param end_t End time for data processing.
 * @return SWavData Struct containing the processed WAV data.
 */
SWavData process_data_to_wav(uint32_t* data, int64_t start_t, int64_t end_t);

/**
 * @brief Checks faults in the memory application.
 *
 * Reads error information from the specified error slot and determines
 * the status based on predefined thresholds.
 *
 * @return EMemTaskStatus_t Status of the memory application task.
 */
EMemTaskStatus_t mem_app_check_faults();


#endif /* MEM_APP_H_ */