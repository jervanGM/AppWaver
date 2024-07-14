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

/**
 * @brief Handles button pulses.
 *
 * This function reads the state of a button pin and determines the type of pulse based on the duration the button is pressed.
 *
 * @param[in] btn_pin The pin number of the button.
 * @return The type of button pulse.
 */
EBtnPulse_t btn_handle_pulse(uint8_t btn_pin);

#endif /* CMD_HANDLER_H_ */