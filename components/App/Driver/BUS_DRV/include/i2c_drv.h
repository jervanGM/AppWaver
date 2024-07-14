#ifndef I2C_DRV_H_
#define I2C_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "i2c driver";

#define I2C_MASTER_SCL_IO           7                          /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           6                          /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000
#define DEV_WITHOUT_REG             0x00

/**
 * @brief Initialize the I2C bus.
 *
 * @return 0 on success, -1 on failure.
 */
int8_t i2c_bus_init(void);

/**
 * @brief Read from a register of an I2C device.
 *
 * @param dev_addr I2C device address.
 * @param data Pointer to buffer to store read data.
 * @param len Number of bytes to read.
 * @return 0 on success, -1 on failure.
 */
int8_t i2c_read_register(uint8_t dev_addr, uint8_t *data, size_t len);

/**
 * @brief Write to a register of an I2C device.
 *
 * @param dev_addr I2C device address.
 * @param data Pointer to data buffer to write.
 * @param len Number of bytes to write.
 * @return 0 on success, -1 on failure.
 */
int8_t i2c_write_register(uint8_t dev_addr, uint8_t *data, size_t len);

/**
 * @brief Deinitialize the I2C bus.
 *
 * @return 0 on success, -1 on failure.
 */
int8_t i2c_bus_deinit(void);

#endif /* I2C_DRV_H_ */