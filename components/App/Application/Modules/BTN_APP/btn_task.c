#include "btn_task.h"
#include "cmd_handler.h"
#include "btn_app.h"
#include "btn_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "safe_timer.h"

/*Main button task function*/
void task_button(void *pvParameters)
{   
    // Initialize task information
    SBtnTaskInfo_t task_info;
    task_btn_init(&task_info);
    // Verify initialization success
    ASSERT_PANIC(task_info.status == BTN_TASK_OK, 
              "Button task info has not been initialized correctly");
    set_task_button_info(task_info);
    btn_app_init();
    for (;;) {
        // Espera una notificación para activarse
        task_wait_for_event();
        EBtnPulse_t pulse = btn_handle_pulse(BUTTON_PIN);
        EBtnCmd_t btn_cmd = btn_app_process_cmd(pulse);
        button_controller_send(btn_cmd);
    }
  
}

/*Init task function*/
void task_btn_init(SBtnTaskInfo_t *task_info)
{
    // Set task ID
    task_info->ID = 3;
    // Set task status
    task_info->status = BTN_TASK_OK;
}