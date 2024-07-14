#include "usb_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdio.h>
#include <stdio.h>
#include "driver/usb_serial_jtag.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_check.h"

#define BUF_SIZE (1024)

int8_t usb_init()
{
    usb_serial_jtag_driver_config_t usb_serial_jtag_config = {
        .rx_buffer_size = BUF_SIZE,
        .tx_buffer_size = BUF_SIZE,
    };

    if (usb_serial_jtag_driver_install(&usb_serial_jtag_config) != ESP_OK)
    {
        return -1; // Failed to install USB Serial JTAG driver
    }
    else
    {
        return 0; // Driver installed successfully
    }
}

bool usb_is_connected()
{
    return usb_serial_jtag_is_connected();
}

void read_cmd(uint8_t *data, uint32_t size)
{
    uint8_t temp_data[size];
    int len = usb_serial_jtag_read_bytes(temp_data, (size - 1), 2);

    // Write data back to the USB SERIAL JTAG
    if (len > 0) {
        memcpy(data,temp_data,size);
    }
    else{
        memset(data,0,size);
    }
}

int8_t usb_deinit()
{
    if (usb_serial_jtag_driver_uninstall() != ESP_OK)
    {
        return -1; // Failed to uninstall USB Serial JTAG driver
    }
    else
    {
        return 0; // Driver uninstalled successfully
    }
}

