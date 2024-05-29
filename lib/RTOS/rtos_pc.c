#include "rtos.h"
#include "assert_panic.h"

ETaskState_t xTaskState[MAX_TASK_HANDLE];

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,const uint32_t stack_deph,int period,unsigned int priority,uint8_t handle_id)
{
    return;
}

ETaskCfgError_t create_sporadic_task(TaskFunction_t task_func,const char *const task_name, uint8_t handle_id)
{
    return;
}

void suspend_task(uint8_t handle_id)
{
    return;
}

void resume_task(uint8_t handle_id)
{
    return;
}

void set_task_rtos_state(uint8_t handle_id, ETaskState_t state)
{
    xTaskState[handle_id] = state;
}

ETaskState_t get_task_rtos_state(uint8_t handle_id)
{
    return xTaskState[handle_id];
}

uint32_t get_task_tick_count()
{
    static uint32_t tick = 0;
    return tick ++;
}

void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay)
{   
    return;
}

void task_delay(uint32_t ms_delay)
{
    return;
}

uint32_t task_wait_for_event()
{
    return 0;
}

void mutex_create()
{
    return;
}

void mutex_lock(uint8_t mutex_id)
{
    return;
}

void mutex_unlock(uint8_t mutex_id)
{
    return;
}