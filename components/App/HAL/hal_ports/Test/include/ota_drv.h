#ifndef OTA_DRV_H_
#define OTA_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void ota_update_reboot();

int8_t ota_init();
void ota_abort();
int8_t ota_end();
int8_t ota_upgrade();
int8_t ota_update_install();
int8_t ota_write(const void *data, size_t length);

#endif /* OTA_DRV_H_ */