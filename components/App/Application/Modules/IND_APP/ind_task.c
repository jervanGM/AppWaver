#include "ind_task.h"
#include "ind_codec.h"
#include "ind_app.h"
#include "ind_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "safe_timer.h"

/*Main indicator task function*/
void task_indicator(void *pvParameters)
{   
    // Initialize task information
    SIndTaskInfo_t task_info;
    SCtrlIndMsg_t msg;
    task_indicator_init(&task_info,pvParameters);

    ASSERT_PANIC(task_info.status == IND_TASK_OK, 
              "Indicator task has not been initialized correctly");
    set_task_indicator_info(task_info);

    ind_app_init();
    ind_init();
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        task_info.status = ind_app_check_faults();
        ctrl_ind_read(&msg);
        set_indicator_state(msg._ind_id,msg._ind_state);
        set_task_indicator_status(task_info.status);
        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
  
}

/*Init task function*/
void task_indicator_init(SIndTaskInfo_t *task_info,void *pvParams)
{
    // Set task ID
    task_info->ID = INDICATOR_HANDLER_ID;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = IND_TASK_OK;
}