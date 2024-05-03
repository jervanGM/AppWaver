#include "serial_task.h"
#include "serial_codec.h"
#include "serial_sm.h"
#include "serial_app.h"
#include "srl_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "srl_t_share.h"

/*Main serial sensors task function*/
void task_serial(void *pvParameters)
{   
    // Initialize task information
    SSrlTaskInfo_t task_info;
    task_serial_init(&task_info,pvParameters);
    
    // Initialize serial state machine
    task_info.status = serial_sm_init(on_srl_init,
                                      on_srl_ready,
                                      on_srl_execute,
                                      on_srl_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == SRL_TASK_OK, 
              "Analog task state machine has not been initialized correctly");
    set_task_serial_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run serial state machine
        serial_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_serial_init(SSrlTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = SRL_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = SRL_TASK_OK;
}

/*Init state execute function*/
void on_srl_init()
{
    // Initialize serial components
    serial_init();
    serial_app_init();
    // Check for faults
    if(serial_app_check_faults() != SRL_TASK_OK)
    {
        // Set state machine event to fault
        serial_sm_set_st_event(SRL_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        serial_sm_set_st_event(SRL_STATE_NEXT);
    }
}

/*Ready state execute function*/
void on_srl_ready()
{   

    if(serial_app_check_faults() != SRL_TASK_OK)
    {
        // Set state machine event to fault
        serial_sm_set_st_event(SRL_STATE_FAULT);
    }
    else if(serial_connected())
    {
        // Set state machine event to next
        serial_sm_set_st_event(SRL_STATE_NEXT);
        set_serial_connection_status(SRL_CONNECTED);
    }
    else
    {
        serial_sm_set_st_event(SRL_STATE_IDLE);
    }
    
}

/*Operational state execute function*/
void on_srl_execute()
{
    SSerialCmd_t srl_cmd;
    srl_cmd = serial_process_cmd();
    if(cmd_exist(srl_cmd.cmd))
    {
        set_serial_command(srl_cmd);
    }
    
    if(serial_app_check_faults() != SRL_TASK_OK)
    {
        // Set state machine event to fault
        serial_sm_set_st_event(SRL_STATE_FAULT);
    }
    else if(!serial_connected())
    {
        serial_sm_set_st_event(SRL_STATE_PREV);
        set_serial_connection_status(SRL_DISCONNECTED);
    }
    else
    {
        // Set state machine event to next
        serial_sm_set_st_event(SRL_STATE_NEXT);
    }
}

/*Breakdown state execute function*/
void on_srl_breakdown()
{
    // Fault reason
    ESrlTaskStatus_t fault_reason = SRL_TASK_OK;
    fault_reason = serial_app_check_faults();
    //Clean the error memory
    store_error_in_slot(SERIAL_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case SRL_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on serialic sensors task");
        // Set state machine event to previous
        serial_sm_set_st_event(SRL_STATE_PREV);
        break;
    
    case SRL_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on serialic sensors task");
        // Set state machine event to next
        serial_deinit();
        serial_sm_set_st_event(SRL_STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on serialic sensors task");    
        break;
    }
    set_task_serial_status(fault_reason);
}
