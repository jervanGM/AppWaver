#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>
#include <stdbool.h>
typedef uint32_t TickType_t;

TickType_t xTaskGetTickCount( void );

#endif /* TASK_H_ */