#include "ana_port.h"
#include "sw_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "analog_task.h"


void systemConfig()
{
    hwInit();
    taskConfig();
}

void taskConfig()
{   
    TickType_t ticks_period = pdMS_TO_TICKS(NULL);
    ticks_period = pdMS_TO_TICKS(ANA_T_PERIOD);
    xTaskCreate(taskAnalog, "Analog Task", 4096,&ticks_period,ANA_T_PRIOR, NULL);
}

void otaConfig()
{

}

void openThreadInit()
{

}

void hwInit()
{
    HAL_ANA_GetPort()->init();
}