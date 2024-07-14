#ifndef PW_MNG_H_
#define PW_MNG_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_pw_data.h"

/**
 * @brief Initializes the power module.
 * 
 * This function initializes the IO, wireless, and PWM ports for power management.
 * It configures specific pins and states based on the platform's configuration.
 */
void pw_init();

/**
 * @brief Executes low power mode.
 * 
 * This function should implement the logic for transitioning the system into a low power mode.
 */
void execute_low_power_mode();

/**
 * @brief Executes full power mode.
 * 
 * This function should implement the logic for transitioning the system into full power mode.
 */
void execute_full_power_mode();

/**
 * @brief Sets the main power off.
 * 
 * This function turns off the main power by writing to the power off output pin.
 */
void set_main_power_off();

/**
 * @brief Sets the main power reset.
 * 
 * This function triggers a system abort through the wireless port.
 */
void set_main_power_reset();

/**
 * @brief Sets the Wi-Fi power status.
 * 
 * @param wifi_pw The desired Wi-Fi power status (ON or OFF).
 * 
 * This function controls the Wi-Fi power status using the wireless port interface.
 */
void set_wifi_power(EWifiActSts_t wifi_pw);

#endif /* PW_MNG_H_ */