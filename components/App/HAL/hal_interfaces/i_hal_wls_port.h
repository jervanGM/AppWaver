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
    int8_t (*init)  (void); /**< Function pointer to initialize the wireless port. */
    int8_t (*reset) (void); /**< Function pointer to reset the wireless port. */
    int8_t (*get_mac) (uint8_t *mac);
    void (*system_abort) (const char *msg);
    int8_t (*connect) (void);
    int8_t (*disconnect) (void);
    int32_t (*get_wifi_event) (void);
    void (*send) (uint8_t channel, uint32_t data); /**< Function pointer to send data to the wireless port. */
    void (*receive)  (uint8_t channel, uint32_t *data); /**< Function pointer to receive data from the wireless port. */
} IWlsPort;

#endif /* I_HAL_WLS_PORT_H_ */