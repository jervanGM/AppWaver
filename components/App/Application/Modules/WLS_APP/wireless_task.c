#include "wireless_task.h"
#include "protocol_drv.h"
#include "network_sm.h"
#include "network_app.h"
#include "wireless_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "objects.h"

/*Main wireless communication task function*/
void task_wireless(void *pvParameters)
{   
    // Initialize task information
    SWlsTaskInfo_t task_info;
    task_wireless_init(&task_info,pvParameters);

    // Initialize network state machine
    task_info.status = network_sm_init(on_wls_init,
                                      on_wls_ready,
                                      on_wls_execute,
                                      on_wls_update,
                                      on_wls_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == WLS_TASK_OK, 
              "Wireless task state machine has not been initialized correctly");
    set_task_wireless_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run wireless state machine
        network_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_wireless_init(SWlsTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = WIRELESS_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = WLS_TASK_OK;
}

/*Init state execute function*/
void on_wls_init()
{
    // Initialize network components
    network_init();
    network_app_init();
    // Check for faults or software update
    if(network_check_fota())
    {
        network_sm_set_st_event(WLS_STATE_UPGRADE);
    }
    else if(network_app_check_faults() != WLS_TASK_OK)
    {
        // Set state machine event to fault
        network_sm_set_st_event(WLS_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        network_sm_set_st_event(WLS_STATE_NEXT);
        set_task_wireless_status(WLS_TASK_OK);
    }
    
}

/*Ready state execute function*/
void on_wls_ready()
{
    network_connect();
    // Check for faults or software update
    if(network_check_fota())
    {
        network_sm_set_st_event(WLS_STATE_UPGRADE);
    }
    else if(network_app_check_faults() != WLS_TASK_OK)
    {
        // Set state machine event to fault
        network_sm_set_st_event(WLS_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        network_sm_set_st_event(WLS_STATE_NEXT);
        set_task_wireless_status(WLS_TASK_OK);
    }
    
}

/*Operational state execute function*/
void on_wls_execute()
{
    network_run();
    SCtrlWlsMsg_t msg;
    SNetworkData_t net_data;
    controller_wireless_read(&msg);
    net_data = update_app_data(msg);
    update_wireless_data(net_data);
    // Check for faults or software update
    if(network_check_fota())
    {
        network_sm_set_st_event(WLS_STATE_UPGRADE);
    }
    else if(network_app_check_faults() != WLS_TASK_OK)
    {
        // Set state machine event to fault
        network_sm_set_st_event(WLS_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        network_sm_set_st_event(WLS_STATE_NEXT);
        set_task_wireless_status(WLS_TASK_OK);
    }
    
}

/*Update state execute function*/
void on_wls_update()
{
    network_deinit();
    network_fota_reboot();
}

/*Breakdown state execute function*/
void on_wls_breakdown()
{
    // Fault reason
    EWlsTaskStatus_t fault_reason = WLS_TASK_OK;
    fault_reason = network_app_check_faults();
    //Clean the error memory
    store_error_in_slot(WIRELESS_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case WLS_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on wireless comunication task");
        // Set state machine event to previous
        network_sm_set_st_event(WLS_STATE_PREV);
        break;
    case WLS_TASK_RECONNECT_FAULT:
        network_disconnect();
        network_sm_set_st_event(WLS_STATE_RECONNECT);
        break;
    case WLS_MAYOR_FAULT:
        // Log major fault
        TRACE_ERROR("A mayor fault has been produced on wireless comunication task");
        network_deinit();
        // Set state machine event to next
        network_sm_set_st_event(WLS_STATE_NEXT);
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on wireless comunication task");    
        break;
    }
    set_task_wireless_status(fault_reason);
}

