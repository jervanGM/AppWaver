#ifndef I_HAL_IO_PORT_H_
#define I_HAL_IO_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration defining operation modes for an I/O port.
 */
typedef enum {
    IO_DISABLE = 0,           /**< Disable I/O port. */
    IO_INPUT = 1,             /**< Input mode for the I/O port. */
    IO_OUTPUT = 2,            /**< Output mode for the I/O port. */
    IO_INPUT_OUTPUT = 3,      /**< Input/Output mode for the I/O port. */
    IO_OUTPUT_OD = 6,         /**< Output mode with open-drain for the I/O port. */
    IO_INPUT_OUTPUT_OD = 7    /**< Input/Output mode with open-drain for the I/O port. */
} io_mode_t;

/**
 * @brief Enumeration defining interrupt types for an I/O port.
 */
typedef enum {
    IO_IT_DISABLE,            /**< Interrupt disabled for the I/O port. */
    IO_IT_POSEDGE,            /**< Interrupt on positive edge for the I/O port. */
    IO_IT_NEGEDGE,            /**< Interrupt on negative edge for the I/O port. */
    IO_IT_ANYEDGE,            /**< Interrupt on any edge for the I/O port. */
    IO_IT_LOW_LEVEL,          /**< Interrupt on low level for the I/O port. */
    IO_IT_HIGH_LEVEL          /**< Interrupt on high level for the I/O port. */
} io_it_type_t;

/**
 * @brief Function pointer type for I/O interrupt service routine (ISR) handler.
 */
typedef void (*io_isr_handler_t)(void *arg);

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Input/Output Ports.
 * 
 * This interface defines the functions required to interact with Input/Output ports
 * in a hardware-independent manner.
 */
typedef struct {
    void (*init)(uint8_t io_pin, io_mode_t mode, bool pull_mode); /**< Function pointer to initialize the I/O port. */
    void (*init_io_it)(uint8_t io_pin, io_it_type_t it_type, io_isr_handler_t isr_handler); /**< Function pointer to initialize I/O interrupt for the I/O port. */
    void (*enable_it)(void);    /**< Function pointer to enable I/O interrupt for the I/O port. */
    void (*disable_it)(void);   /**< Function pointer to disable I/O interrupt for the I/O port. */
    void (*reset)(uint8_t io_pin); /**< Function pointer to reset the I/O port. */
    int8_t (*write)(uint8_t io_pin, uint32_t value); /**< Function pointer to write data to the I/O port. */
    uint32_t (*read)(uint8_t io_pin); /**< Function pointer to read data from the I/O port. */
} IIOPort;

#endif /* I_HAL_IO_PORT_H_ */
