#ifndef USB_DRV_H_
#define USB_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE (1024)

int8_t usb_init();

bool usb_is_connected();

void read_cmd(uint8_t *data, uint32_t size);

int8_t usb_deinit();

void set_errors(uint8_t init_err, uint8_t deinit_err);

void set_serial_connection(bool conn);

void set_serial_msg(const uint8_t msg[BUF_SIZE]);

#endif /* USB_DRV_H_ */