#include "ind_codec.h"
#include "io_port.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "safe_timer.h"

static const IIOPort *port;

// Static function prototypes
static void ind_fixed_on_drive(uint8_t pin);
static void ind_fixed_off_drive(uint8_t pin);
static void blink_periodic(uint64_t time, uint8_t pin);
static void ind_error_code(uint8_t pin);

// Initialization function for the indicator module
void ind_init()
{
    port = hal_io_get_port(); // Initialize the port interface

    // Check if the port interface is valid
    if (port != NULL)
    {
        port->init(IND_LED1_PIN, IO_OUTPUT, false); // Initialize LED pin as output
        ind_fixed_on_drive(IND_LED1_PIN); // Turn on the LED initially
    }
    else
    {
        // Log an error if the port is not configured properly
        store_error_in_slot(INDICATOR_ERROR_SLOT, HAL_IND_CONFIG_ERROR);
        TRACE_ERROR("Indicator IO HAL port has not been configured correctly on init");
    }
}

// Function to set the state of an indicator LED
void set_indicator_state(EIndId_t id, EIndSts_t state)
{
    uint8_t ind_pin = 0;

    // Determine the pin based on the indicator ID
    switch (id)
    {
    case IND_LED1:
        ind_pin = IND_LED1_PIN;
        break;
    
    default:
        ind_pin = IND_UNK_PIN; // Default pin for unknown indicator ID
        break;
    }

    // Perform the corresponding action based on the indicator state
    switch (state)
    {
    case FIXED_ON:
        ind_fixed_on_drive(ind_pin); // Turn on the LED
        break;
    case FIXED_OFF:
        ind_fixed_off_drive(ind_pin); // Turn off the LED
        break;
    case BLINK_500_MS:
    case BLINK_1_S:
    case BLINK_2_S:
    case BLINK_4_S:
        blink_periodic(state * T_500_MS, ind_pin); // Start blinking with specified period
        break;
    
    // Note: BLINK_TASK_ERROR case is intentionally omitted from switch
    // since it is not implemented in this example
    default:
        ASSERT_PANIC(false, "An unknown LED state has been read"); // Assert if an unknown state is received
        break;
    }
}

// Function to drive the indicator LED to a fixed ON state
static void ind_fixed_on_drive(uint8_t pin)
{
    port->write(pin, STS_ON); // Set the pin to ON state
}

// Function to drive the indicator LED to a fixed OFF state
static void ind_fixed_off_drive(uint8_t pin)
{
    port->write(pin, STS_OFF); // Set the pin to OFF state
}

// Function to blink the indicator LED periodically
static void blink_periodic(uint64_t time, uint8_t pin)
{
    static uint8_t led_sts = STS_OFF; // Static variable to track the LED status
    static STimer_t timer = {
        .type = PERIODIC,
        .id = "blink"
    };

    timer.period = time; // Set the blinking period

    // Check if the timer is running
    if (safe_timer_is_on(&timer))
    {
        // Check if the timer has expired
        if (safe_timer_is_expired(&timer))
        {
            led_sts = !led_sts; // Toggle the LED status
            port->write(pin, led_sts); // Write the new LED status to the port
        }
    }
    else
    {
        safe_timer_init(&timer); // Initialize the timer if it's not running
    }
}


// Function to indicate an error code on the indicator LED (not implemented)
static void ind_error_code(uint8_t pin)
{
    // Implementation for indicating an error code on the indicator
    // Not implemented in this example
}

