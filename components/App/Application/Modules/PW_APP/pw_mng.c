#include "pw_mng.h"
#include "io_port.h"
#include "wls_port.h"
#include "pwm_port.h"
#include "safe_trace.h"
#include "safe_memory.h"

static const IIOPort *port;

static const IWlsPort *wls_port;

static const IPwmPort *pwm_port;

/* Initializes the power module */
void pw_init()
{
    // Retrieve the IO, wireless, and PWM port interfaces
    port = hal_io_get_port();
    wls_port = hal_wls_get_port();
    pwm_port = hal_pwm_get_port();

    // Check if the port interfaces are valid
    if ((port != NULL) && (wls_port != NULL) && (pwm_port != NULL))
    {
        // Initialize power off pin
        port->init(POWER_OFF_PIN, IO_OUTPUT, false);
        port->write(POWER_OFF_PIN, STS_OFF);

        #ifdef ADVANCED
        // Initialize soil moisture PWM and sensor switch pins in advanced mode
        pwm_port->init(SOIL_PWM_PIN, SOIL_PWM_CHAN, SOIL_FREQ);
        pwm_port->set(SOIL_PWM_CHAN, SOIL_DUTY, STS_ON);
        port->init(SENS_SW_PIN, IO_OUTPUT, false);
        port->write(SENS_SW_PIN, STS_ON);
        #endif
    }
    else
    {
        // Log an error if the port interfaces are not properly configured
        store_error_in_slot(POWER_ERROR_SLOT, HAL_PW_CONFIG_ERROR);
        TRACE_ERROR("Power IO HAL port has not been configured correctly on init");
    }
}

void execute_low_power_mode()
{
    // Implement logic for low power mode
    // (To be defined based on system requirements)
}

void execute_full_power_mode()
{
    // Implement logic for full power mode
    // (To be defined based on system requirements)
}

void set_main_power_off()
{
    // Log a warning message
    TRACE_WARNING("The system will shut down completely");

    // Turn off main power by writing to the power off pin
    port->write(POWER_OFF_PIN, STS_ON);
}

void set_main_power_reset()
{
    // Trigger a system abort through the wireless port
    wls_port->system_abort("[PW TASK] System abort by user");
}

void set_wifi_power(EWifiActSts_t wifi_pw)
{
    if (wifi_pw == PW_WIFI_OFF)
    {
        // Disconnect Wi-Fi through the wireless port
        wls_port->disconnect();
    }
    else
    {
        // Handle other states or configurations for Wi-Fi power
        // (To be defined based on system requirements)
    }
}

