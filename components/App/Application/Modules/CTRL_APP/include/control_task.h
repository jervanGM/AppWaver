#ifndef CONTROL_TASK_H_
#define CONTROL_TASK_H_


void task_control(void *pvParameters);

void task_control_init();

void on_ctrl_init();

void on_ctrl_ready();

void on_ctrl_execute();

void on_ctrl_breakdown();

#endif /* CONTROL_TASK_H_ */