#ifndef CONTROL_DIAG_H_
#define CONTROL_DIAG_H_

#include <stdbool.h>
#include "i_control_data.h"
#include "control_task.h"
#include "analog_t_share.h"
#include "wireless_t_share.h"
#include "mem_t_share.h"
#include "bus_t_share.h"
#include "btn_t_share.h"
#include "pw_t_share.h"
#include "ind_t_share.h"
#include "srl_t_share.h"

ECtrlTaskAct_t control_diag_process_change_task(EWlsTaskStatus_t wls_status,EMemTaskStatus_t mem_status);

#ifdef ADVANCED
SCtrlBusSensMsg_t control_diag_process_bus_cmd(STemp_t temp, SMoist_t moist);
#endif

#endif /* CONTROL_DIAG_H_ */