#ifndef I2C_DRV_H_
#define I2C_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_DEV_NUM 256
#define MAX_REG_NUM 256

/**
 * @brief i2c master initialization
 */
int8_t i2c_bus_init(void);

/**
 * @brief Read a sequence of bytes from a device registers
 */
int8_t i2c_read_register(uint8_t dev_addrs, uint8_t *data, size_t len);

/**
 * @brief Write a byte to a device register
 */
int8_t i2c_write_register(uint8_t dev_addrs, uint8_t *data, size_t len);

/**
 * @brief i2c master deinitialization
 */
int8_t i2c_bus_deinit();

void set_errors(uint8_t init_err, uint8_t deinit_err, uint8_t read_err, uint8_t write_err);

void set_read_data(uint8_t dev_addr, uint8_t reg, uint8_t data);

#endif /* I2C_DRV_H_ */