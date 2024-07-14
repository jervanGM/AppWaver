#ifndef SERIAL_CODEC_H_
#define SERIAL_CODEC_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "i_serial_data.h"

/**
 * @brief Initializes the serial module.
 * 
 * Function prototype for initializing the serial module.
 */
void serial_init();

/**
 * @brief Checks if the serial connection is established.
 * 
 * Checks if the serial port is connected.
 * 
 * @return true if connected, false otherwise
 */
bool serial_connected();

/**
 * @brief Processes the serial command received.
 * 
 * Processes the serial command read from the serial port.
 * 
 * @return Processed serial command structure
 */
SSerialCmd_t serial_process_cmd();

/**
 * @brief Deinitializes the serial module.
 * 
 * Function prototype for deinitializing the serial module.
 */
void serial_deinit();

#endif /* SERIAL_CODEC_H_ */