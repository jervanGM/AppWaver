#include "ind_codec.h"
#include "io_port.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "safe_timer.h"

static const IIOPort *port;

static void ind_fixed_on_drive(uint8_t pin);
static void ind_fixed_off_drive(uint8_t pin);
static void blink_periodic(uint64_t time, uint8_t pin);
static void ind_error_code(uint8_t pin);

void ind_init()
{
    port = hal_io_get_port();
    // Check if the port interface is valid
    if (port != NULL)
    {
        port->init(IND_LED1_PIN,IO_OUTPUT,false);
        ind_fixed_on_drive(IND_LED1_PIN);
    }
    else
    {
        // Log an error if the analog port is not properly configured
        store_error_in_slot(INDICATOR_ERROR_SLOT, HAL_IND_CONFIG_ERROR);
        TRACE_ERROR("Indicator IO HAL port has not been configured correctly on init");
    }
}

void set_indicator_state( EIndId_t id,EIndSts_t state)
{
    uint8_t ind_pin = 0;
    switch (id)
    {
    case IND_LED1:
        ind_pin = IND_LED1_PIN;
        break;
    
    default:
        ind_pin = IND_UNK_PIN;
        break;
    }

    switch (state)
    {
    case FIXED_ON:
        ind_fixed_on_drive(ind_pin);
        break;
    case FIXED_OFF:
        ind_fixed_off_drive(ind_pin);
        break;
    case BLINK_500_MS:
        blink_periodic(T_500_MS,ind_pin);
        break;
    case BLINK_1_S:
        blink_periodic(T_1_S,ind_pin);
        break;
    case BLINK_2_S:
        blink_periodic(T_2_S,ind_pin);
        break;
    case BLINK_4_S:
        blink_periodic(T_4_S,ind_pin);
        break;
    case BLINK_TASK_ERROR:
        ind_error_code(ind_pin);
        break;
    
    default:
        ASSERT_PANIC(false,"An unknown led state has been read");
        break;
    }
}

static void ind_fixed_on_drive(uint8_t pin)
{
    port->write(pin,STS_ON);
}

static void ind_fixed_off_drive(uint8_t pin)
{
    port->write(pin,STS_OFF);
}

static void blink_periodic(uint64_t time, uint8_t pin)
{
    static uint8_t led_sts = STS_OFF;
    static STimer_t timer = {
        .type = PERIODIC,
        .id = "blink"
    };
    timer.period = time;
    if(safe_timer_is_on(&timer))
    {

        if(safe_timer_is_expired(&timer))
        {
            led_sts = !led_sts;
            port->write(pin,led_sts);
        }

    }
    else
    {
        safe_timer_init(&timer);
    }
}


static void ind_error_code(uint8_t pin)
{

}

