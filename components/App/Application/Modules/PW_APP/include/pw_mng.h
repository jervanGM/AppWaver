#ifndef PW_MNG_H_
#define PW_MNG_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_pw_data.h"

void pw_init();

void execute_low_power_mode();

void execute_full_power_mode();

void set_main_power_off();

void set_main_power_reset();

void set_wifi_power(EWifiActSts_t wifi_pw);

#endif /* PW_MNG_H_ */