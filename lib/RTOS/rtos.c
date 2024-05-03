#include "rtos.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "assert_panic.h"

SemaphoreHandle_t xMutex[MAX_MUTEX];
TaskHandle_t xTaskHandle[MAX_TASK_HANDLE];

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,const uint32_t stack_deph,int period,unsigned int priority,uint8_t handle_id)
{
    ASSERT_PANIC(handle_id <= MAX_TASK_HANDLE, "Array index out of bounds");
    BaseType_t xtask_error = pdFAIL;
    xtask_error = xTaskCreate(task_func, task_name, stack_deph,(void *)&period,priority, &xTaskHandle[handle_id]);
    if(xtask_error == pdPASS) return TASK_OK;
    else if(xtask_error == pdFAIL) return TASK_MEM_ERR;
    else return TASK_UNKNOWN_ERR;
}

ETaskCfgError_t create_sporadic_task(TaskFunction_t task_func,const char *const task_name, uint8_t handle_id)
{
    ASSERT_PANIC(handle_id <= MAX_TASK_HANDLE, "Array index out of bounds");
    BaseType_t xtask_error = pdFAIL;
    xtask_error = xTaskCreate(task_func, task_name, 2048 ,NULL, 1, &xTaskHandle[handle_id]);
    if(xtask_error == pdPASS) return TASK_OK;
    else if(xtask_error == pdFAIL) return TASK_MEM_ERR;
    else return TASK_UNKNOWN_ERR;
}

void suspend_task(uint8_t handle_id)
{
    ASSERT_PANIC(handle_id <= MAX_TASK_HANDLE, "Array index out of bounds");
    vTaskSuspend(xTaskHandle[handle_id]);
}

void resume_task(uint8_t handle_id)
{
    ASSERT_PANIC(handle_id <= MAX_TASK_HANDLE, "Array index out of bounds");
    vTaskResume(xTaskHandle[handle_id]);
}

ETaskState_t get_task_rtos_state(uint8_t handle_id)
{
    return (ETaskState_t)eTaskGetState(xTaskHandle[handle_id]);
}

void task_wait_for_event()
{
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
}


uint32_t get_task_tick_count()
{
    return (uint32_t)xTaskGetTickCount();
}

uint32_t get_task_tick_count_from_it()
{
    return (uint32_t)xTaskGetTickCountFromISR();
}

void notify_to_task_from_it(uint8_t handle_id)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(xTaskHandle[handle_id],  0, eNoAction, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void notify_to_task_from_it_with_value(uint8_t handle_id,uint32_t value)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(xTaskHandle[handle_id], value, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay)
{   
    TickType_t delay = pdMS_TO_TICKS(ms_delay);
    vTaskDelayUntil( PreviousWakeTime, delay);
}

void task_delay(uint32_t ms_delay)
{
    TickType_t delay = pdMS_TO_TICKS(ms_delay);
    vTaskDelay(delay);
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