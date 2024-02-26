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
    void (*init)  (void); /**< Function pointer to initialize the analog port. */
    void (*reset) (void); /**< Function pointer to reset the analog port. */
    void (*write) (uint8_t channel, uint32_t data); /**< Function pointer to write data to the analog port. */
    void (*read)  (uint8_t channel, uint32_t *data); /**< Function pointer to read data from the analog port. */
} IAnaPort;

#endif /* I_HAL_ANA_PORT_H_ */
