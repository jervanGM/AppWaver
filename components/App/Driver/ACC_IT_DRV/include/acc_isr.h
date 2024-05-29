#ifndef ACC_ISR_H_
#define ACC_ISR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_attr.h>

#define ACC_IT_HANDLER_ID 9

#define ACT_IT1 1
#define ACT_IT2 2

void IRAM_ATTR acc1_it(void *arg);
void IRAM_ATTR acc2_it(void *arg);

#endif /* ACC_ISR_H_ */