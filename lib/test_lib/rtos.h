#ifndef RTOS_H_
#define RTOS_H_

#include "task_types.h"
#include <stdint.h>

#define MAX_MUTEX 10

typedef void (*TaskFunction_t)(void *);

ETaskCfgError_t create_task(TaskFunction_t task_func,const char *const task_name,int period,unsigned int priority);

uint32_t get_task_tick_count();

void task_delay_until();

void mutex_create();

void mutex_lock(uint8_t mutex_id);

void mutex_unlock(uint8_t mutex_id);

#endif /* RTOS_H_ */