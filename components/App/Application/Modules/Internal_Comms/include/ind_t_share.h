#ifndef IND_T_SHARE_H_
#define IND_T_SHARE_H_

#include <stdbool.h>
#include "i_ind_data.h"

#define CTRL_IND_M_ID 6
#define IND_CTRL_M_ID 7

void set_task_indicator_info(SIndTaskInfo_t task_info);

void set_task_indicator_status(EIndTaskStatus_t status);

void ind_ctrl_read(SIndCtrlMsg_t *msg);

void ctrl_ind_send(EIndId_t ind_id, EIndSts_t ind_state);

void ctrl_ind_read(SCtrlIndMsg_t *msg);

#endif /* IND_T_SHARE_H_ */