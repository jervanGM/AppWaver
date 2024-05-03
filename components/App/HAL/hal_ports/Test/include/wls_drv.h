#ifndef WLS_DRV_H_
#define WLS_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int8_t wifi_initialize(void);
int8_t wifi_connect();
int8_t wifi_disconnect(void);
int8_t wifi_deinitialize(void);

int8_t mac_get_default(uint8_t *mac);

void wireless_system_abort(const char *msg);

#endif /* WLS_DRV_H_ */