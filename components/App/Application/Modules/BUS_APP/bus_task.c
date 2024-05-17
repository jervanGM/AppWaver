#include "bus_task.h"
#include "bus_drv.h"
#include "bus_sm.h"
#include "bus_app.h"
#include "bus_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "bus_t_share.h"

/*Main serial sensors task function*/
void task_bus(void *pvParameters)
{   
    // Initialize task information
    SBusTaskInfo_t task_info;
    task_bus_init(&task_info,pvParameters);
    
    // Initialize serial state machine
    task_info.status = bus_sm_init(on_bus_init,
                                      on_bus_ready,
                                      on_bus_execute,
                                      on_bus_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == BUS_TASK_OK, 
              "Analog task state machine has not been initialized correctly");
    set_task_bus_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run serial state machine
        bus_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_bus_init(SBusTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = BUS_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = BUS_TASK_OK;
}

/*Init state execute function*/
void on_bus_init()
{
    // Initialize serial components
    bus_init();
    bus_app_init();
    // Check for faults
    if(bus_app_check_faults() != BUS_TASK_OK)
    {
        // Set state machine event to fault
        bus_sm_set_st_event(BUS_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        bus_sm_set_st_event(BUS_STATE_NEXT);
    }
}

/*Ready state execute function*/
void on_bus_ready()
{   
    devices_init();
    if(bus_app_check_faults() != BUS_TASK_OK)
    {
        // Set state machine event to fault
        bus_sm_set_st_event(BUS_STATE_FAULT);
    }
    else
    {
        bus_sm_set_st_event(BUS_STATE_NEXT);
    }
    
}

/*Operational state execute function*/
void on_bus_execute()
{
    uint8_t raw_data[RAW_DATA_BYTES];
    SAxisDataBuffer_t axis_buffer = {0};
    SCtrlBusSensMsg_t ctrl_msg = {0};
    SBufTime_t axis_buf_time = {0};
    STemp_t temp_data = {0};
    SMoist_t moist_data = {0};
    measure_raw_data(raw_data);
    process_data(raw_data,RAW_DATA_BYTES);
    axis_buffer = get_axis_data_buffer();
    axis_buf_time = get_axis_buffer_time();
    temp_data = get_buffer_average_temp();
    moist_data = get_buffer_average_moist();
    bus_controller_send(axis_buffer,temp_data,moist_data,axis_buf_time);
    bus_controller_read(&ctrl_msg);
    if(ctrl_msg._dev_id == TEMP_HUM_SENS)
    {
        write_temp_moist_cmd(ctrl_msg._cmd.heater_cmd);
    }
    
    if(bus_app_check_faults() != BUS_TASK_OK)
    {
        // Set state machine event to fault
        bus_sm_set_st_event(BUS_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        bus_sm_set_st_event(BUS_STATE_NEXT);
    }
}

/*Breakdown state execute function*/
void on_bus_breakdown()
{
    // Fault reason
    EBusTaskStatus_t fault_reason = BUS_TASK_OK;
    fault_reason = bus_app_check_faults();
    //Clean the error memory
    store_error_in_slot(BUS_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case BUS_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on serial task");
        // Set state machine event to previous
        bus_sm_set_st_event(BUS_STATE_PREV);
        break;
    
    case BUS_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on serial task");
        // Set state machine event to next
        bus_deinit();
        bus_sm_set_st_event(BUS_STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on serial task");    
        break;
    }
    set_task_bus_status(fault_reason);
}
