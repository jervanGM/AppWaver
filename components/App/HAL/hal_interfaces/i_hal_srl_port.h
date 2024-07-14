#ifndef I_HAL_SRL_PORT_H_
#define I_HAL_SRL_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Serial Ports.
 * 
 * This interface defines functions for serial port operations in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(void); /**< Function pointer to initialize the serial port. */
    bool (*is_connected)(void); /**< Function pointer to check if the serial port is connected. */
    void (*read_cmd)(uint8_t *data, uint32_t size); /**< Function pointer to read data from the serial port. */
    int8_t (*deinit)(void); /**< Function pointer to deinitialize the serial port. */
} ISrlPort;

#endif /* I_HAL_SRL_PORT_H_ */

