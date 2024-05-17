#ifndef USB_DRV_H_
#define USB_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sdkconfig.h"


int8_t usb_init();

bool usb_is_connected();

void read_cmd(uint8_t *data, uint32_t size);

int8_t usb_deinit();

#endif /* USB_DRV_H_ */