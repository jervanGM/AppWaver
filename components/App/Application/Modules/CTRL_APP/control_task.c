#include "control_task.h"
#include "analog_t_share.h"
#include "wireless_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "safe_timer.h"
#include "rtos.h"
#include "control_sm.h"
#include "control_app.h"
#include "control_diag.h"
#include "safe_memory.h"
#include <string.h>

void task_control(void *pvParameters)
{   
    // Initialize task information
    SCtrlTaskInfo_t task_info;
    task_control_init(&task_info,pvParameters);

    // Initialize network state machine
    task_info.status = control_sm_init(on_ctrl_init,
                                      on_ctrl_ready,
                                      on_ctrl_execute,
                                      on_ctrl_breakdown);

    // Verify initialization success
    ASSERT_PANIC(task_info.status == CTRL_TASK_OK, 
              "Control task state machine has not been initialized correctly");
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run control state machine
        control_sm_run();
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

void task_control_init(SAnaTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = 1;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status =CTRL_TASK_OK;
}

void on_ctrl_init()
{
    if(control_app_check_faults() != CTRL_TASK_OK)
    {
        // Set state machine event to fault
        control_sm_set_st_event(CTRL_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        control_sm_set_st_event(CTRL_STATE_NEXT);
    }
}

void on_ctrl_ready()
{
    if(control_app_check_faults() != CTRL_TASK_OK)
    {
        // Set state machine event to fault
        control_sm_set_st_event(CTRL_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        control_sm_set_st_event(CTRL_STATE_NEXT);
    }
}

void on_ctrl_execute()
{
    SAnalogSensMsg_t msg;
    SErrorInfo_t alarm;
    SSystemStatus_t status;
    SEnvData_t env_data;
    SPowerData_t power_data;
    SAxisData_t axix_buf[DATA_BUFFER_SIZE];
    static uint8_t plant_data[DATA_BUFFER_SIZE];
    analog_controller_read(&msg);
    if(msg._plant_buff.size>0 && msg._plant_buff.ready)
    {
      memcpy(plant_data,msg._plant_buff.data,DATA_BUFFER_SIZE*sizeof(uint8_t));
      // for(uint16_t i = 0;i<msg._plant_buff.size;i++)
      // {
      //   TRACE_INFO("PLANT INFO:", TO_STRING(msg._plant_buff.data[i]));
      // }
      // TRACE_INFO("CONTROL START TIME:", TO_STRING(msg._buff_time.start_time.sec));
      // TRACE_INFO("CONTROL END TIME:", TO_STRING(msg._buff_time.end_time.sec));
    }
    // else
    // {
    //   memset(plant_data, 0, DATA_BUFFER_SIZE * sizeof(uint8_t));
    // }

    controller_wireless_send(alarm,status,plant_data,env_data,power_data,
                            axix_buf,SYS_BUFFER_MODE,SYS_BUFFER_MODE,get_system_time());
    if(control_app_check_faults() != CTRL_TASK_OK)
    {
        // Set state machine event to fault
        control_sm_set_st_event(CTRL_STATE_FAULT);
    }
    else
    {
        // Set state machine event to next
        control_sm_set_st_event(CTRL_STATE_NEXT);
    }
}

void on_ctrl_breakdown()
{
    // Fault reason
    ECtrlTaskStatus_t fault_reason = CTRL_TASK_OK;
    fault_reason = control_app_check_faults();
    //Clean the error memory
    store_error_in_slot(CONTROL_ERROR_SLOT,0);
    switch (fault_reason)
    {
    case WLS_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on controller task");
        // Set state machine event to previous
        control_sm_set_st_event(CTRL_STATE_PREV);
        break;
    
    case WLS_MAYOR_FAULT:
        // Log major fault
        ASSERT_PANIC(false,"A mayor fault reason has been produced on controller task, reboot application");   
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on controller task");    
        break;
    }
}

