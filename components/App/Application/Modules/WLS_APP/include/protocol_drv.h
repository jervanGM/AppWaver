#ifndef PROTOCOL_DRV_H_
#define PROTOCOL_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_wireless_data.h"
#define MAIN_NVS_CONFIG_NAMESPACE "config"
#define MAIN_NVS_WRITABLE_WIFI_CONFIG_NAMESPACE "writable_wifi"
#define MAIN_NVS_WIFI_SSID_KEY "wifi_ssid"
#define MAIN_NVS_WIFI_PASSWORD_KEY "wifi_pswd"
#define MAIN_NVS_ENABLE_KEY "wifi_inter_en"

void anjay_main(void);

void init(void);

#endif /* PROTOCOL_DRV_H_ */