#ifndef RTOS_H_
#define RTOS_H_

#include "task_types.h"
#include <stdint.h>

#define MAX_MUTEX 20
#define MAX_TASK_HANDLE 10

typedef void (*TaskFunction_t)(void *);

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,const uint32_t stack_deph,int period,unsigned int priority,uint8_t handle_id);

ETaskCfgError_t create_sporadic_task(TaskFunction_t task_func,const char *const task_name, uint8_t handle_id);

void suspend_task(uint8_t handle_id);

void resume_task(uint8_t handle_id);

ETaskState_t get_task_rtos_state(uint8_t handle_id);

uint32_t get_task_tick_count();

uint32_t get_task_tick_count_from_it();

void notify_to_task_from_it(uint8_t handle_id);

void notify_to_task_from_it_with_value(uint8_t handle_id,uint32_t value);

uint32_t task_wait_for_event();

void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay);

void task_delay(uint32_t ms_delay);

void mutex_create();

void mutex_lock(uint8_t mutex_id);

void mutex_unlock(uint8_t mutex_id);

#endif /* RTOS_H_ */