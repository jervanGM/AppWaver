#include "rtos.h"
#include "acc_isr.h"

void IRAM_ATTR acc1_it(void *arg)
{
    notify_to_task_from_it(ACC_IT_HANDLER_ID);
}

void IRAM_ATTR acc2_it(void *arg)
{
    notify_to_task_from_it(ACC_IT_HANDLER_ID);
}