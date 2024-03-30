#ifndef PW_T_SHARE_H_
#define PW_T_SHARE_H_

#include <stdbool.h>
#include "i_pw_data.h"

#define CTRL_PW_M_ID 8
#define PW_CTRL_M_ID 9

void set_task_power_info(SPwTaskInfo_t task_info);

void set_task_power_status(EPwTaskStatus_t status);

void pw_ctrl_read(SPwCtrlMsg_t *msg);

void ctrl_pw_send( ESensSwSts_t sens_sw_sts,
                   EMainSwSts_t main_sw_sts,
                   ESoilActSts_t soil_act_sts,
                   EPwMode_t pw_mode);

void ctrl_pw_read(SCtrlPwMsg_t *msg);

#endif /* PW_T_SHARE_H_ */