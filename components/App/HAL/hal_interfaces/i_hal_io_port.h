#ifndef I_HAL_IO_PORT_H_
#define I_HAL_IO_PORT_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    IO_DISABLE = 0,
    IO_INPUT = 1,
    IO_OUTPUT = 2,
    IO_INPUT_OUTPUT = 3,
    IO_OUTPUT_OD = 6,
    IO_INPUT_OUTPUT_OD = 7
} io_mode_t;

typedef enum {
    IO_IT_DISABLE,
    IO_IT_POSEDGE,
    IO_IT_NEGEDGE,
    IO_IT_ANYEDGE,
    IO_IT_LOW_LEVEL,
    IO_IT_HIGH_LEVEL
} io_it_type_t;

typedef void (*io_isr_handler_t)(void *arg);

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Analog Ports.
 * 
 * This interface defines the functions required to interact with analog ports
 * in a hardware-independent manner.
 */
typedef struct {
    void (*init)  (uint8_t io_pin, io_mode_t mode, bool pull_mode); /**< Function pointer to initialize the analog port. */
    void (*init_io_it) (uint8_t io_pin, io_it_type_t it_type, io_isr_handler_t isr_handler);
    void (*enable_it) (void);
    void (*disable_it) (void);
    void (*reset) (uint8_t io_pin); /**< Function pointer to reset the analog port. */
    int8_t (*write) (uint8_t io_pin, uint32_t value); /**< Function pointer to write data to the analog port. */
    uint32_t (*read)  (uint8_t io_pin); /**< Function pointer to read data from the analog port. */
} IIOPort;

#endif /* I_HAL_IO_PORT_H_ */