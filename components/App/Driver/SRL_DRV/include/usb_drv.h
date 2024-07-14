#ifndef USB_DRV_H_
#define USB_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sdkconfig.h"


/**
 * @brief Initialize the USB Serial JTAG driver.
 * 
 * This function initializes the USB Serial JTAG driver with a specified buffer size.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t usb_init();

/**
 * @brief Check if USB Serial JTAG is connected.
 * 
 * @return true if connected, false otherwise.
 */
bool usb_is_connected();

/**
 * @brief Read command data from USB Serial JTAG.
 * 
 * This function reads command data from USB Serial JTAG into the provided buffer.
 * 
 * @param data Pointer to the buffer to store data.
 * @param size Size of the buffer.
 */
void read_cmd(uint8_t *data, uint32_t size);

/**
 * @brief Deinitialize the USB Serial JTAG driver.
 * 
 * This function deinitializes the USB Serial JTAG driver.
 * 
 * @return 0 if successful, -1 otherwise.
 */
int8_t usb_deinit();

#endif /* USB_DRV_H_ */