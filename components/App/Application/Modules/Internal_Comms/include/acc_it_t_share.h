#ifndef ACC_IT_T_SHARE_H_
#define ACC_IT_T_SHARE_H_

#include <stdbool.h>
#include "i_acc_it_data.h"

#define ACC_IT_M_ID 16

void set_task_acc_it_info(SAccItTaskInfo_t task_info);

void set_task_acc_it_status(EAccItTaskStatus_t status);

void acc_it_controller_send(EIntCmd_t int_cmd,int64_t it_moment);

void acc_it_controller_read(SAccItMsg_t *msg);

#endif /* ACC_IT_T_SHARE_H_ */