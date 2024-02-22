#ifndef ANALOG_TASK_H_
#define ANALOG_TASK_H_


void task_analog(void *pvParameters);

void task_analog_init();

void task_analog_q_get();

void task_analog_q_set();

void on_ana_init();

void on_ana_ready();

void on_ana_execute();

void on_ana_breakdown();

#endif /* ANALOG_TASK_H_ */