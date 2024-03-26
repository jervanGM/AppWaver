#ifndef WLS_DRV_H_
#define WLS_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void wifi_initialize(void);
void wifi_connect();
void wifi_disconnect(void);
void wifi_deinitialize(void);

void mac_get_default(uint8_t *mac);

void wireless_system_abort(const char *msg);

#endif /* WLS_DRV_H_ */