#include "pw_t_share.h"
#include "rtos.h"
#include <string.h>
#include "safe_trace.h"

static SPwCtrlMsg_t _pw_msg = {0};
static SCtrlPwMsg_t _ctrl_msg = {0};

void set_task_power_info(SPwTaskInfo_t task_info)
{
    mutex_lock(PW_CTRL_M_ID);
        memcpy(&_pw_msg._task_info, &task_info, sizeof(SPwTaskInfo_t));
    mutex_unlock(PW_CTRL_M_ID);
}

void set_task_power_status(EPwTaskStatus_t status)
{
    mutex_lock(PW_CTRL_M_ID);
        _pw_msg._task_info.status = status;
    mutex_unlock(PW_CTRL_M_ID);
}

void pw_ctrl_read(SPwCtrlMsg_t *msg)
{
    mutex_lock(PW_CTRL_M_ID);
        memcpy(msg, &_pw_msg, sizeof(SPwCtrlMsg_t));
    mutex_unlock(PW_CTRL_M_ID);
}

void ctrl_pw_send( ESensSwSts_t sens_sw_sts,
                   EMainSwSts_t main_sw_sts,
                   ESoilActSts_t soil_act_sts,
                   EWifiActSts_t wifi_act_sts,
                   EPwMode_t pw_mode)
{
    mutex_lock(CTRL_PW_M_ID);
        memcpy(&_ctrl_msg._sens_sw_sts, &sens_sw_sts, sizeof(ESensSwSts_t));
        memcpy(&_ctrl_msg._main_sw_sts, &main_sw_sts, sizeof(EMainSwSts_t));
        memcpy(&_ctrl_msg._soil_act_sts, &soil_act_sts, sizeof(ESoilActSts_t));
        memcpy(&_ctrl_msg._wifi_act_sts, &wifi_act_sts, sizeof(EWifiActSts_t));
        memcpy(&_ctrl_msg._pw_mode, &pw_mode, sizeof(EPwMode_t));
    mutex_unlock(CTRL_PW_M_ID);
}

void ctrl_pw_read(SCtrlPwMsg_t *msg)
{
    mutex_lock(CTRL_PW_M_ID);
        memcpy(msg, &_ctrl_msg, sizeof(SCtrlPwMsg_t));
    mutex_unlock(CTRL_PW_M_ID);
}