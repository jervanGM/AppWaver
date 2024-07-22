#ifndef BUS_DRV_H_
#define BUS_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "i_bus_data.h"

/**
 * @brief Initializes the bus communication module.
 *
 * This function initializes the bus communication module by getting the bus port,
 * initializing it, and checking for any initialization errors.
 */
void bus_init();

/**
 * @brief Deinitializes the bus communication module.
 *
 * This function deinitializes the bus communication module by deinitializing the bus port.
 */
void bus_deinit();

/**
 * @brief Initializes connected devices.
 *
 * This function initializes specific devices connected to the bus, such as temperature/humidity
 * sensors and accelerometers. It checks for initialization errors and logs them if necessary.
 */
void devices_init();

/**
 * @brief Measures raw data from connected sensors.
 *
 * This function measures raw data from sensors connected to the bus, such as temperature,
 * humidity, and accelerometer data. It handles errors during measurement and logs them if necessary.
 *
 * @param[out] raw_data Pointer to store the raw sensor data.
 */
void measure_raw_data(uint8_t *raw_data);

/**
 * @brief Writes a command to control the heater of a temperature/moisture sensor.
 *
 * This function writes a command to control the heater of a temperature/moisture sensor
 * connected to the bus. It handles different heater command options and logs errors if necessary.
 *
 * @param[in] cmd Command to set the temperature/heater mode of the moisture sensor.
 */
void write_temp_moist_cmd(ESht4xHeaterCmd_t cmd);
void bus_deinit();
#endif /* BUS_DRV_H_ */