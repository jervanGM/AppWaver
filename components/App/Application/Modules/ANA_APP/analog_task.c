#include "analog_task.h"
#include "analog_drv.h"
#include "analog_sm.h"
#include "analog_app.h"
#include "analog_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"

/*Main analog sensors task function*/
void task_analog(void *pvParameters)
{   
    // Initialize task information
    SAnaTaskInfo_t task_info;
    task_analog_init(&task_info,pvParameters);

    // Initialize analog state machine
    task_info.status = analog_sm_init(on_ana_init,
                                      on_ana_ready,
                                      on_ana_execute,
                                      on_ana_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == ANA_TASK_OK, 
              "Analog task state machine has not been initialized correctly");
    set_task_analog_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run analog state machine
        analog_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_analog_init(SAnaTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = ANA_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = ANA_TASK_OK;
}

/*Init state execute function*/
void on_ana_init()
{
    // Initialize analog components
    analog_init();
    analog_app_init();
    // Check for faults
    if(analog_app_check_faults() != ANA_TASK_OK)
    {
        // Set state machine event to fault
        analog_sm_set_st_event(STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        analog_sm_set_st_event(STATE_NEXT);
    }
}

/*Ready state execute function*/
void on_ana_ready()
{
    // Buffer for plant data
    static SDataBuffer_t plant_buff = { .size = 0, .ready = false };
    static SBufferTime_t buffer_time;
    // Ignore first data buffer for signal stabilization
    get_data_buffer(&plant_buff,&buffer_time);
    // Read the error from the specified error slot
    
    if(plant_buff.ready && (plant_buff.size > 0))
    {
        // Check for faults
        if(analog_app_check_faults() != ANA_TASK_OK)
        {
            // Set state machine event to fault
            analog_sm_set_st_event(STATE_FAULT);
        }
        else
        {
            // Set state machine event to next
            analog_sm_set_st_event(STATE_NEXT);
        }
    }
}

/*Operational state execute function*/
void on_ana_execute()
{
    // Buffer for plant data
    static SDataBuffer_t plant_buff = { .size = 0, .ready = false };
    static SBufferTime_t buffer_time;
    get_data_buffer(&plant_buff,&buffer_time);
    // Send data to analog controller
    analog_controller_send(plant_buff,buffer_time);
    // Check for faults
    if(analog_app_check_faults() != ANA_TASK_OK)
    {
        // Set state machine event to fault
        analog_sm_set_st_event(STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        analog_sm_set_st_event(STATE_NEXT);
    }
}

/*Breakdown state execute function*/
void on_ana_breakdown()
{
    // Fault reason
    EAnaTaskStatus_t fault_reason = ANA_TASK_OK;
    fault_reason = analog_app_check_faults();
    //Clean the error memory
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case ANA_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on analogic sensors task");
        // Set state machine event to previous
        analog_sm_set_st_event(STATE_PREV);
        break;
    
    case ANA_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on analogic sensors task");
        // Set state machine event to next
        analog_sm_set_st_event(STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on analogic sensors task");    
        break;
    }
    set_task_analog_status(fault_reason);
}
