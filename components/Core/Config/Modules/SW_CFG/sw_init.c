#include "sw_init.h"
#include "rtos.h"
#include "analog_task.h"
#include "control_task.h"
#include "wireless_task.h"
#include <stdio.h>


void systemConfig()
{
    hwInit();
    taskConfig();
}

void taskConfig()
{  
    mutex_create();
    //create_task(task_analog,"Analog Task",4096,ANA_T_PERIOD,ANA_T_PRIOR);
    //create_task(task_control,"Control Task",4096,CONTROL_T_PERIOD,CONTROL_T_PRIOR);
    create_task(task_wireless,"Wireless Task",16384,WIRELESS_T_PERIOD,WIRELESS_T_PRIOR);
}

void otaConfig()
{

}

void openThreadInit()
{

}

void hwInit()
{
}