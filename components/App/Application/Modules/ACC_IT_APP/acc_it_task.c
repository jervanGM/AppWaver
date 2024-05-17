#include "acc_it_task.h"
#include "ev_handler.h"
#include "acc_it_app.h"
#include "acc_it_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "safe_timer.h"

/*Main button task function*/
void task_acc_it(void *pvParameters)
{   
    // Initialize task information
    SAccItTaskInfo_t task_info;
    task_acc_it_init(&task_info);
    // Verify initialization success
    ASSERT_PANIC(task_info.status == ACC_IT_TASK_OK, 
              "Button task info has not been initialized correctly");
    set_task_acc_it_info(task_info);
    acc_it_app_init();
    for (;;) {
        // Espera una notificación para activarse
        task_wait_for_event();
        STime_t irs_time = get_system_time();
        EIntCmd_t it = acc_it_handle_pulse();
        acc_it_controller_send(it,irs_time);
    }
  
}

/*Init task function*/
void task_acc_it_init(SAccItTaskInfo_t *task_info)
{
    // Set task ID
    task_info->ID = 9;
    // Set task status
    task_info->status = ACC_IT_TASK_OK;
}