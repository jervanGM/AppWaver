#ifndef CMD_HANDLER_H_
#define CMD_HANDLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_btn_data.h"

#define SHORT_PRESS_LIMIT 2
#define LONG_PRESS_LIMIT 5
#define POWER_OFF_LIMIT 8

#define SYSTEM_INIT_WAIT_TIME 10

EBtnPulse_t btn_handle_pulse(uint8_t btn_pin);

#endif /* CMD_HANDLER_H_ */