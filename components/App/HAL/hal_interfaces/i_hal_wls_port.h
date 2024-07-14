#ifndef I_HAL_WLS_PORT_H_
#define I_HAL_WLS_PORT_H_

#include <stdint.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for wireless Ports.
 * 
 * This interface defines functions for wireless port operations in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(void); /**< Function pointer to initialize the wireless port. */
    int8_t (*reset)(void); /**< Function pointer to reset the wireless port. */
    int8_t (*get_mac)(uint8_t *mac); /**< Function pointer to retrieve the MAC address of the wireless port. */
    void (*system_abort)(const char *msg); /**< Function pointer to perform system abort with a message. */
    int8_t (*connect)(void); /**< Function pointer to connect to a wireless network. */
    int8_t (*disconnect)(void); /**< Function pointer to disconnect from a wireless network. */
    int32_t (*get_wifi_event)(void); /**< Function pointer to get the last Wi-Fi event ID. */
    void (*send)(uint8_t channel, uint32_t data); /**< Function pointer to send data over the wireless port. */
    void (*receive)(uint8_t channel, uint32_t *data); /**< Function pointer to receive data from the wireless port. */
} IWlsPort;

#endif /* I_HAL_WLS_PORT_H_ */
