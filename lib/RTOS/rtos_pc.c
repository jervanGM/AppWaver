#include "rtos.h"
#include "assert_panic.h"

SemaphoreHandle_t xMutex[MAX_MUTEX];

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,int period,unsigned int priority)
{

}

uint32_t get_task_tick_count()
{
    static uint32_t tick = 0;
    return tick ++;
}

void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay)
{   

}

void mutex_create()
{

}

void mutex_lock(uint8_t mutex_id)
{

}

void mutex_unlock(uint8_t mutex_id)
{

}