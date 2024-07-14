#include "control_diag.h"
#include "safe_trace.h"
#include <string.h>

ECtrlTaskAct_t control_diag_process_change_task(uint8_t wls_status, uint8_t mem_status)
{
    static ECtrlTaskAct_t task_active = CTRL_TASK_WLS;
    static STimer_t timer = {
        .type = PERIODIC,
        .id = "wls_wait_status",
        .period = T_1_MIN
    };

    // Handling minor fault in wireless task and timer management
    if (wls_status == WLS_MINOR_FAULT && task_active == CTRL_TASK_WLS)
    {
        // Timer is active, check expiration
        if (safe_timer_is_on(&timer))
        {
            // Timer expired, switch to memory task
            if (safe_timer_is_expired(&timer))
            {
                task_active = CTRL_TASK_MEM;
                TRACE_INFO("TASK_CHANGED_TO_MEMORY_CARD");
                safe_timer_delete(&timer); // Delete timer after task change
            }
            // Timer still running, do nothing
        }
        else
        {
            // Timer not started, initialize it
            safe_timer_init(&timer);
        }
    }
    else
    {
        // No minor fault or task already switched, handle timer deletion
        if (safe_timer_is_on(&timer))
        {
            safe_timer_delete(&timer); // Delete timer if still active
        }
    }
    
    // Handling major fault in wireless task, switch to none
    if (wls_status == WLS_MAJOR_FAULT && task_active == CTRL_TASK_MEM)
    {
        task_active = CTRL_TASK_NONE;
    }

    return task_active; // Return current active task
}

#ifdef ADVANCED
SCtrlBusSensMsg_t control_diag_process_bus_cmd(uint8_t temp, uint8_t moist)
{
    SCtrlBusSensMsg_t msg;

    // Check temperature and moisture thresholds for bus sensor command
    if ((temp < 20) && (moist > 70))
    {
        msg._cmd.heater_cmd = SHT4X_MED_HEATER_1S; // Set medium heater command
        msg._dev_id = TEMP_HUM_SENS; // Set device ID for temperature and humidity sensor
    }
    else
    {
        msg._cmd.heater_cmd = SHT4X_NO_HEATER; // No heater command needed
        msg._dev_id = TEMP_HUM_SENS; // Set device ID for temperature and humidity sensor
    }

    return msg; // Return generated control message
}
#endif