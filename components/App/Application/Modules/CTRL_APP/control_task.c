#include "control_task.h"
#include "analog_t_share.h"
#include "wireless_t_share.h"
#include "mem_t_share.h"
#include "btn_t_share.h"
#include "acc_it_t_share.h"
#include "pw_t_share.h"
#include "ind_t_share.h"
#include "srl_t_share.h"
#include "bus_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "safe_timer.h"
#include "rtos.h"
#include "control_sm.h"
#include "control_app.h"
#include "control_diag.h"
#include "safe_memory.h"
#include <string.h>

extern const char *srl_cmd_list[];

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
    task_info->ID = CONTROL_HANDLER_ID;
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
    SAnalogSensMsg_t ana_msg = {0};
    SAnalogSensMsg_t processed_ana_msg = {0};
    SWlsCtrlMsg_t wls_msg = {0};
    SMemCtrlMsg_t mem_msg = {0};
    SBtnMsg_t btn_msg = {0};
    SErrorInfo_t alarm = {0};
    SSystemStatus_t status = {0};
    SEnvData_t env_data = {0};
    SPowerData_t power_data = {0};
    SPPlantData_t plant_buf = {0};
    SAxisData_t axis_buf = {0};
    SSerialMsg_t srl_msg = {0};

    static ECtrlTaskAct_t task_active = CTRL_TASK_WLS; 
    static EWifiActSts_t wifi_pw_sts = PW_WIFI_ON;

    analog_controller_read(&ana_msg);
    wireless_controller_read(&wls_msg);
    button_controller_read(&btn_msg);
    serial_controller_read(&srl_msg);
    mem_ctrl_read(&mem_msg);

    plant_buf = control_app_process_plant_data(ana_msg);

#ifdef ADVANCED
    SBusSensCtrlMsg_t bus_msg = {0};
    SCtrlBusSensMsg_t ctrl_msg = {0};
    SAccItMsg_t acc_it_msg = {0};
    bus_controller_read(&bus_msg);
    acc_it_controller_read(&acc_it_msg);
    env_data = control_app_process_env_data(ana_msg,bus_msg);
    axis_buf = control_app_process_acc_data(bus_msg,acc_it_msg);
    ctrl_msg = control_diag_process_bus_cmd(bus_msg._temp_data, bus_msg._moist_data);
    controller_bus_send(ctrl_msg._dev_id,ctrl_msg._cmd);
#endif

    if((btn_msg._btn_cmd == BTN_CMD_PW_OFF) || (strcmp(srl_msg._command.cmd, srl_cmd_list[0]) == 0))
    {
        ctrl_pw_send(PW_SENS_OFF,PW_MAIN_OFF,PW_SOIL_OFF,PW_WIFI_OFF,PW_MODE_FULL);
        ctrl_ind_send(IND_LED1,FIXED_OFF);
        power_data.curnt_pw_mode = E_PW_OFF;
        
    }
    else if(btn_msg._btn_cmd == BTN_CMD_NORMAL || (strcmp(srl_msg._command.cmd, srl_cmd_list[1]) == 0))
    {
        ctrl_pw_send(PW_SENS_ON,PW_MAIN_ON,PW_SOIL_ON,wifi_pw_sts,PW_MODE_FULL);
        ctrl_ind_send(IND_LED1,FIXED_ON);
        task_active = control_diag_process_change_task(wls_msg._task_info.status,mem_msg._task_info.status);
    }
    else
    {
        ctrl_pw_send(PW_SENS_ON,PW_MAIN_ON,PW_SOIL_ON,wifi_pw_sts,PW_MODE_FULL);
        ctrl_ind_send(IND_LED1,BLINK_500_MS);
        task_active = CTRL_TASK_BOTH;
    }
    
#ifdef BASIC
    switch (task_active)
    {
    case CTRL_TASK_WLS:
        if(get_task_rtos_state(mem_msg._task_info.ID) != TASK_SUSPENDED)
        {
            suspend_task(mem_msg._task_info.ID);
        }
        if(get_task_rtos_state(wls_msg._task_info.ID) == TASK_SUSPENDED)
        {
            resume_task(wls_msg._task_info.ID);
            wifi_pw_sts = PW_WIFI_ON;
        }
        
        break;
    case CTRL_TASK_MEM:
        if(get_task_rtos_state(mem_msg._task_info.ID) == TASK_SUSPENDED)
        {
            resume_task(mem_msg._task_info.ID);
        }
        if(get_task_rtos_state(wls_msg._task_info.ID) != TASK_SUSPENDED)
        {
            suspend_task(wls_msg._task_info.ID);
            wifi_pw_sts = PW_WIFI_OFF;
        }
        
        break;
    case CTRL_TASK_BOTH:
        if(get_task_rtos_state(mem_msg._task_info.ID) == TASK_SUSPENDED)
        {
            resume_task(mem_msg._task_info.ID);
        }
        if(get_task_rtos_state(wls_msg._task_info.ID) == TASK_SUSPENDED)
        {
            resume_task(wls_msg._task_info.ID);
            wifi_pw_sts = PW_WIFI_ON;
        }
        break;
    default:
        ASSERT_PANIC(false, "Task change state not available");
        break;
    }

#endif
    controller_wireless_send(alarm,status,plant_buf,env_data,power_data,axis_buf,
                            SYS_BUFFER_MODE,SYS_BUFFER_MODE,
                            get_system_time());
    ctrl_mem_send(alarm,status,plant_buf,env_data,power_data,axis_buf,
                            SYS_BUFFER_MODE,SYS_BUFFER_MODE,
                            get_system_time());

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
    case CTRL_MINOR_FAULT:
        // Log minor fault
        TRACE_WARNING("A minor fault has been produced on controller task");
        // Set state machine event to previous
        control_sm_set_st_event(CTRL_STATE_PREV);
        break;
    
    case CTRL_MAYOR_FAULT:
        // Log major fault
        ASSERT_PANIC(false,"A mayor fault reason has been produced on controller task, reboot application");   
        break;
    default:
        // Assert if unknown fault reason
        ASSERT_PANIC(false,"Unknown fault reason has been produced on controller task");    
        break;
    }
}

