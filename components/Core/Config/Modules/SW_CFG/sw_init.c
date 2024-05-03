#include "sw_init.h"
#include "rtos.h"
#include "analog_task.h"
#include "control_task.h"
#include "wireless_task.h"
#include "btn_task.h"
#include "ind_task.h"
#include "pw_task.h"
#include "io_port.h"
#include "mem_task.h"
#include "serial_task.h"
#include "btn_isr.h"
#include <stdio.h>
#include <stdbool.h>
#include "assert_panic.h"

#include "wdt_cfg.h"


void systemConfig()
{
    hwInit();
    taskConfig();
}

void taskConfig()
{  
    mutex_create();
    create_task(task_analog,"Analog Task",4096,ANA_T_PERIOD,ANA_T_PRIOR,ANA_T_HANDLER);
    create_task(task_control,"Control Task",4096,CONTROL_T_PERIOD,CONTROL_T_PRIOR,CONTROL_T_HANDLER);
    create_task(task_power,"Power Task",4096,POWER_T_PERIOD,POWER_T_PRIOR,POWER_T_HANDLER);
    create_task(task_indicator,"Indication Task",4096,IND_T_PERIOD,IND_T_PRIOR,IND_T_HANDLER);
    create_task(task_wireless,"Wireless Task",16384,WIRELESS_T_PERIOD,WIRELESS_T_PRIOR,WIRELESS_T_HANDLER);
    create_task(task_ext_memory,"External Memory Task",4096,EXT_MEM_T_PERIOD,EXT_MEM_T_PRIOR,EXT_MEM_T_HANDLER);
    create_task(task_serial,"Serial Task",4096,SERIAL_RX_T_PERIOD,SERIAL_RX_T_PRIOR,SERIAL_RX_T_HANDLER);
    create_sporadic_task(task_button,"Button Task", SPORADIC_BUTTON_HANDLER);
}



void hwInit()
{
    set_wdt_disable();
    const IIOPort *port = hal_io_get_port();
    ASSERT_PANIC(port != NULL,"GPIO configurarion port on firmware intialization has not been initialized correctly");
    port->enable_it();
    port->init(BUTTON_PIN,IO_INPUT,true);
    port->init_io_it(BUTTON_PIN,IO_IT_NEGEDGE,button_it);
}