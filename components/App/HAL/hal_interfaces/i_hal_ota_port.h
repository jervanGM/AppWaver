#ifndef I_HAL_OTA_PORT_H_
#define I_HAL_OTA_PORT_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for OTA (Over-The-Air) Port operations.
 * 
 * This interface defines functions for performing firmware update operations
 * in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(void); /**< Function pointer to initialize the OTA port. */
    void (*update_reboot)(void); /**< Function pointer to reboot after updating firmware. */
    int8_t (*write)(const void *data, size_t length); /**< Function pointer to write firmware data. */
    void (*reset)(void); /**< Function pointer to reset the OTA process. */
    int8_t (*finish)(void); /**< Function pointer to finish the OTA process. */
    int8_t (*upgrade)(void); /**< Function pointer to perform firmware upgrade. */
    int8_t (*update_install)(void); /**< Function pointer to install the firmware update. */
} IOtaPort;

#endif /* I_HAL_OTA_PORT_H_ */
