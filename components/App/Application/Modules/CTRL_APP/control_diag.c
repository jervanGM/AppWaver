#include "control_diag.h"
#include "safe_trace.h"
#include <string.h>

ECtrlTaskAct_t control_diag_process_change_task(EWlsTaskStatus_t wls_status,EMemTaskStatus_t mem_status)
{
    static ECtrlTaskAct_t task_active = CTRL_TASK_WLS;
    static STimer_t timer = {
        .type = PERIODIC,
        .id = "wls_wait_status",
        .period = T_1_MIN
    };

    if(wls_status == WLS_MINOR_FAULT && task_active == CTRL_TASK_WLS)
    {
        if(safe_timer_is_on(&timer))
        {

            if(safe_timer_is_expired(&timer))
            {
                task_active = CTRL_TASK_MEM;
                TRACE_INFO("TASK_CHANGED_TO_MEMORY_CARD");
                safe_timer_delete(&timer);
            }
            else{}

        }
        else
        {
            safe_timer_init(&timer);
        }
        
    }
    else
    {
        if(safe_timer_is_on(&timer))
        {
            safe_timer_delete(&timer);
        }
    }
    
    if(wls_status == WLS_MAYOR_FAULT && task_active == CTRL_TASK_MEM)
    {
        task_active = CTRL_TASK_NONE;
    }

    return task_active;
}

#ifdef ADVANCED
SCtrlBusSensMsg_t control_diag_process_bus_cmd(STemp_t temp, SMoist_t moist)
{
    SCtrlBusSensMsg_t msg;
    if(((temp.temperature < 20) && (moist.moist > 70)))
    {
        msg._cmd.heater_cmd = SHT4X_MED_HEATER_1S;
        msg._dev_id = TEMP_HUM_SENS;
    }
    else{
        msg._cmd.heater_cmd = SHT4X_NO_HEATER;
        msg._dev_id = TEMP_HUM_SENS;
    }
    return msg;
}
#endif