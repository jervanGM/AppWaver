#include "mem_task.h"
#include "mem_drv.h"
#include "mem_sm.h"
#include "mem_app.h"
#include "mem_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"



/*Main external memory task function*/
void task_ext_memory(void *pvParameters)
{   
    // Initialize task information
    SMemTaskInfo_t task_info;
    task_mem_init(&task_info,pvParameters);

    // Initialize external memory state machine
    task_info.status = mem_sm_init( on_mem_init,
                                    on_mem_execute,
                                    on_mem_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == MEM_TASK_OK, 
              "External memory task state machine has not been initialized correctly");
    set_task_ext_mem_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run external memory state machine
        mem_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_mem_init(SMemTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = EXT_MEM_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = MEM_TASK_OK;
}

/*Init state execute function*/
void on_mem_init()
{
    mem_drv_init();
    mem_app_init();
    // Check for faults
    if(mem_app_check_faults() != MEM_TASK_OK)
    {
        // Set state machine event to fault
        mem_sm_set_st_event(MEM_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        mem_sm_set_st_event(MEM_STATE_NEXT);
    }
}

/*Operational state execute function*/
void on_mem_execute()
{
    SWavData wav;
    SCtrlMemMsg_t msg;
    ctrl_mem_read(&msg);

    wav = process_data_to_wav(msg._plant_signal.data,msg._plant_signal.start_time,msg._plant_signal.end_time);

    if(msg._power_data.curnt_pw_mode == E_PW_OFF)
    {
        mem_drv_deinit();
    }
    else
    {
        if(wav.average != 0)
        {
            save_wav_data(wav);
        }
    }
    // Check for faults
    if(mem_app_check_faults() != MEM_TASK_OK)
    {
        // Set state machine event to fault
        mem_sm_set_st_event(MEM_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        mem_sm_set_st_event(MEM_STATE_NEXT);
    }
}

/*Breakdown state execute function*/
void on_mem_breakdown()
{
    // Fault reason
    EMemTaskStatus_t fault_reason = MEM_TASK_OK;
    fault_reason = mem_app_check_faults();
    //Clean the error memory
    store_error_in_slot(EXT_MEM_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case MEM_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on external memory task");
        // Set state machine event to previous
        mem_sm_set_st_event(MEM_STATE_PREV);
        break;
    
    case MEM_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on external memory task");
        // Set state machine event to next
        mem_drv_deinit();
        mem_sm_set_st_event(MEM_STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on external memory task");    
        break;
    }
    set_task_ext_mem_status(fault_reason);
}
