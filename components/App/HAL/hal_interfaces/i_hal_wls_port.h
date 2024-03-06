#ifndef I_HAL_WLS_PORT_H_
#define I_HAL_WLS_PORT_H_

#include <stdint.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for wireless Ports.
 * 
 * This interface defines the functions required to interact with wireless ports
 * in a hardware-independent manner.
 */
typedef struct {
    void (*init)  (void); /**< Function pointer to initialize the wireless port. */
    void (*reset) (void); /**< Function pointer to reset the wireless port. */
    void (*get_mac) (uint8_t *mac);
    void (*system_abort) (const char *msg);
    void (*connect) (void);
    void (*disconnect) (void);
    void (*send) (uint8_t channel, uint32_t data); /**< Function pointer to send data to the wireless port. */
    void (*receive)  (uint8_t channel, uint32_t *data); /**< Function pointer to receive data from the wireless port. */
} IWlsPort;

#endif /* I_HAL_WLS_PORT_H_ */