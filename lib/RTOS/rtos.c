#include "rtos.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "assert_panic.h"

SemaphoreHandle_t xMutex[MAX_MUTEX];

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,const uint32_t stack_deph,int period,unsigned int priority)
{
    BaseType_t xtask_error = pdFAIL;
    xtask_error = xTaskCreate(task_func, task_name, stack_deph,(void *)&period,priority, NULL);
    if(xtask_error == pdPASS) return TASK_OK;
    else if(xtask_error == pdFAIL) return TASK_MEM_ERR;
    else return TASK_UNKNOWN_ERR;
}

uint32_t get_task_tick_count()
{
    return (uint32_t)xTaskGetTickCount();
}

void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay)
{   
    TickType_t delay = pdMS_TO_TICKS(ms_delay);
    vTaskDelayUntil( PreviousWakeTime, delay);
}

void mutex_create()
{
    for(int mutex_id=0; mutex_id<MAX_MUTEX; mutex_id++)
    {
        xMutex[mutex_id] = xSemaphoreCreateMutex();
    }
}

void mutex_lock(uint8_t mutex_id)
{
    ASSERT_PANIC(mutex_id <= MAX_MUTEX, "Array index out of bounds");
    xSemaphoreTake(xMutex[mutex_id], portMAX_DELAY);
}

void mutex_unlock(uint8_t mutex_id)
{
    ASSERT_PANIC(mutex_id <= MAX_MUTEX, "Array index out of bounds");
    xSemaphoreGive(xMutex[mutex_id]);
}