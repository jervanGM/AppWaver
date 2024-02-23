#ifndef ANA_PORT_H_
#define ANA_PORT_H_

#include "i_hal_ana_port.h"

/**
 * @brief Gets the analog port.
 * 
 * @return Pointer to the analog port.
 */
const IAnaPort * hal_ana_get_port(void);

// Implementation of the ADC HAL interface
/**
 * @brief Initializes the analog port.
 */
static void ana_port_init(void);

/**
 * @brief Resets the analog port.
 */
static void ana_port_reset(void);

/**
 * @brief Reads data from adc peripheral through analog port.
 * 
 * @param channel ADC channel.
 * @param data Pointer to store the read data.
 */
static void ana_port_read(uint8_t channel,uint32_t * data);

/**
 * @brief Writes data to the adc peripheral through analog port.
 * 
 * @param channel ADC channel.
 * @param data Data to write to the analog port.
 */
static void ana_port_write(uint8_t channel,uint32_t data);

/**
 * @brief Interface for the analog port.
 * 
 * This structure defines the interface for the analog port.
 */
static const IAnaPort ana_port_interface = {
    .init = ana_port_init,
    .reset = ana_port_reset,
    .read = ana_port_read,
    .write = ana_port_write
};

#endif /* ANA_PORT_H_ */