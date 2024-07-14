#ifndef I_HAL_BUS_PORT_H_
#define I_HAL_BUS_PORT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Interface definition for hardware abstraction layer (HAL) bus port operations.
 * 
 * This structure defines function pointers for initializing, writing to, reading from,
 * and deinitializing a hardware bus port.
 */
typedef struct {
    int8_t (*init)(void);               /**< Function pointer to initialize the bus port. */
    int8_t (*write_reg)(uint8_t dev_addrs, uint8_t *data, size_t len); /**< Function pointer to write data to a register on the bus. */
    int8_t (*read_reg)(uint8_t dev_addrs, uint8_t *data, size_t len);  /**< Function pointer to read data from a register on the bus. */
    int8_t (*deinit)(void);             /**< Function pointer to deinitialize the bus port. */
} IBusPort;

#endif /* I_HAL_BUS_PORT_H_ */
