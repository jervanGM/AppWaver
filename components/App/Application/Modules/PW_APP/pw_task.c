#include "pw_task.h"
#include "pw_mng.h"
#include "pw_sm.h"
#include "pw_app.h"
#include "pw_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"

/*Main analog sensors task function*/
void task_power(void *pvParameters)
{   
    // Initialize task information
    SPwTaskInfo_t task_info;
    task_pw_init(&task_info,pvParameters);

    // Initialize analog state machine
    task_info.status = pw_sm_init(on_pw_init,
                                      on_pw_ready,
                                      on_pw_execute,
                                      on_pw_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == PW_TASK_OK, 
              "Analog task state machine has not been initialized correctly");
    set_task_power_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run analog state machine
        pw_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_pw_init(SPwTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = 5;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = PW_TASK_OK;
}

/*Init state execute function*/
void on_pw_init()
{
    // Initialize analog components
    pw_init();
    power_app_init();
    // Check for faults
    if(power_app_check_faults() != PW_TASK_OK)
    {
        // Set state machine event to fault
        pw_sm_set_st_event(PW_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        pw_sm_set_st_event(PW_STATE_NEXT);
    }
}

/*Ready state execute function*/
void on_pw_ready()
{
    // Check for faults
    if(power_app_check_faults() != PW_TASK_OK)
    {
        // Set state machine event to fault
        pw_sm_set_st_event(PW_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        pw_sm_set_st_event(PW_STATE_NEXT);
    }
}

/*Operational state execute function*/
void on_pw_execute()
{
    // Check for faults
    if(power_app_check_faults() != PW_TASK_OK)
    {
        // Set state machine event to fault
        pw_sm_set_st_event(PW_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        pw_sm_set_st_event(PW_STATE_NEXT);
    }
}

/*Breakdown state execute function*/
void on_pw_breakdown()
{
    // Fault reason
    EPwTaskStatus_t fault_reason = PW_TASK_OK;
    fault_reason = power_app_check_faults();
    //Clean the error memory
    store_error_in_slot(POWER_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case PW_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on power management task");
        // Set state machine event to previous
        pw_sm_set_st_event(PW_STATE_PREV);
        break;
    
    case PW_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on power management task");
        // Set state machine event to next
        pw_sm_set_st_event(PW_STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on power management task");    
        break;
    }
    set_task_power_status(fault_reason);
}
