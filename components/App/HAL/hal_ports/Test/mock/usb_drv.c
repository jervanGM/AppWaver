#include "usb_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdio.h>
#include <stdio.h>

static uint8_t temp_data[BUF_SIZE];
static bool is_connected = false;
static uint8_t init_error = 0;
static uint8_t deinit_error = 0;

int8_t usb_init()
{
    memset(temp_data, 0, sizeof(temp_data));
    return init_error;
}

bool usb_is_connected()
{
    return is_connected;
}

void read_cmd(uint8_t *data, uint32_t size)
{
    uint8_t int_temp_data[BUF_SIZE] = {0};
    int len = memcmp(temp_data, int_temp_data, sizeof(temp_data));

    // Write data back to the USB SERIAL JTAG
    if (len > 0) {
        memcpy(data,temp_data,size);
    }
}

int8_t usb_deinit()
{
    return deinit_error;
}

void set_errors(uint8_t init_err, uint8_t deinit_err)
{
    init_error = init_err;
    deinit_error = deinit_err;
}

void set_serial_connection(bool conn)
{
    is_connected = conn;
}

void set_serial_msg(const uint8_t msg[BUF_SIZE])
{
    memcpy(temp_data,msg,BUF_SIZE);
}

