#ifndef I_HAL_ANA_PORT_H_
#define I_HAL_ANA_PORT_H_

#include <stdint.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Analog Ports.
 * 
 * This interface defines the functions required to interact with analog ports
 * in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)  (void); /**< Function pointer to initialize the analog port. */
    int8_t (*reset) (void); /**< Function pointer to reset the analog port. */
    int8_t (*write) (uint8_t channel, uint32_t data); /**< Function pointer to write data to the analog port. */
    int8_t (*read)  (uint8_t channel, uint32_t *data); /**< Function pointer to read data from the analog port. */
} IAnaPort;

#endif /* I_HAL_ANA_PORT_H_ */
