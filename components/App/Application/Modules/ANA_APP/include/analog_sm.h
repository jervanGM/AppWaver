#ifndef ANALOG_SM_H_
#define ANALOG_SM_H_

#include <stdbool.h>
#include "i_analog_sm.h"
#include "i_analog_data.h"

ETaskStatus_t analog_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
);

void analog_sm_run();

ETaskState_t analog_sm_get_state();

void analog_sm_set_event();

void init_transition();
void ready_transition();
void operational_transition();
void breakdown_transition();

#endif /* ANALOG_SM_H_ */