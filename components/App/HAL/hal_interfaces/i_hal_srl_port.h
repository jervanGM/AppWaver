#ifndef I_HAL_SRL_PORT_H_
#define I_HAL_SRL_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Analog Ports.
 * 
 * This interface defines the functions required to interact with analog ports
 * in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)  (void); /**< Function pointer to initialize the analog port. */
    bool (*is_connected) (void); /**< Function pointer to reset the analog port. */
    void (*read_cmd)  (uint8_t *data, uint32_t size); /**< Function pointer to read data from the analog port. */
    int8_t (*deinit)  (void);
} ISrlPort;

#endif /* I_HAL_SRL_PORT_H_ */
