#include "sw_init.h"
#include "rtos.h"
#include "analog_task.h"
#include "control_task.h"
#include "wireless_task.h"
#include "btn_task.h"
#include "ind_task.h"
#include "pw_task.h"
#include "io_port.h"
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
    create_task(task_analog,"Analog Task",4096,ANA_T_PERIOD,ANA_T_PRIOR);
    create_task(task_control,"Control Task",4096,CONTROL_T_PERIOD,CONTROL_T_PRIOR);
    create_task(task_power,"Power Task",4096,POWER_T_PERIOD,POWER_T_PRIOR);
    create_task(task_indicator,"Indication Task",4096,IND_T_PERIOD,IND_T_PRIOR);
    create_task(task_wireless,"Wireless Task",16384,WIRELESS_T_PERIOD,WIRELESS_T_PRIOR);
    create_sporadic_task(task_button,"Button Task", SPORADIC_BUTTON_HANDLER);
}



void hwInit()
{
    set_wdt_disable();
    const IIOPort *port = hal_io_get_port();
    ASSERT_PANIC(port != NULL,"GPIO configurarion port on firmware intialization has not been initialized correctly");
    port->enable_it();
    port->init(21,IO_INPUT,true);
    port->init_io_it(21,IO_IT_NEGEDGE,button_it);
    port->init(10,IO_OUTPUT,false);
    port->write(10,1);

}