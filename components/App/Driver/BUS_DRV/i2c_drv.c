#include "i2c_drv.h"


int8_t i2c_bus_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    // Configure I2C parameters
    if (i2c_param_config(i2c_master_port, &conf) != ESP_OK)
    {
        return -1;
    }

    // Install I2C driver
    if (i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0) != ESP_OK)
    {
        return -1;
    }
    return 0;
}


int8_t i2c_read_register(uint8_t dev_addr, uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    // Start I2C transaction
    i2c_master_start(cmd);
    // Write device address for read operation
    i2c_master_write_byte(cmd, (dev_addr << 1) | 1, true);
    // Read data from device
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    // Stop I2C transaction
    i2c_master_stop(cmd);

    // Execute I2C command
    if (i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS) != ESP_OK)
    {
        ESP_LOGE(TAG, "Could not read from device [0x%02x at %d]", dev_addr, I2C_MASTER_NUM);
        return -1;
    }
    i2c_cmd_link_delete(cmd);

    return 0;
}


int8_t i2c_write_register(uint8_t dev_addr, uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    // Start I2C transaction
    i2c_master_start(cmd);
    // Write device address for write operation
    i2c_master_write_byte(cmd, dev_addr << 1, true);
    // Write data to device
    i2c_master_write(cmd, data, len, true);
    // Stop I2C transaction
    i2c_master_stop(cmd);

    // Execute I2C command
    if (i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS) != ESP_OK)
    {
        ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]", dev_addr, I2C_MASTER_NUM);
        return -1;
    }
    i2c_cmd_link_delete(cmd);

    return 0;
}

int8_t i2c_bus_deinit()
{
    if(i2c_driver_delete(I2C_MASTER_NUM) != ESP_OK)
    {
        return -1;
    }
    return 0; 
}
