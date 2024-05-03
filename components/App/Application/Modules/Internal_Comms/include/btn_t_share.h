#ifndef BTN_T_SHARE_H_
#define BTN_T_SHARE_H_

#include <stdbool.h>
#include "i_btn_data.h"

#define BTN_M_ID 4

void set_task_button_info(SBtnTaskInfo_t task_info);

void set_task_button_status(EBtnTaskStatus_t status);

void button_controller_send(EBtnCmd_t btn_cmd);

void button_controller_read(SBtnMsg_t *msg);

#endif /* BTN_T_SHARE_H_ */