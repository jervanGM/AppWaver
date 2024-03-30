#include "ind_task.h"
#include "ind_codec.h"
#include "ind_app.h"
#include "ind_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"
#include "safe_timer.h"

/*Main button task function*/
void task_indicator(void *pvParameters)
{   
    // Initialize task information
    SIndTaskInfo_t task_info;
    task_indicator_init(&task_info,pvParameters);

    ASSERT_PANIC(task_info.status == IND_TASK_OK, 
              "Analog task state machine has not been initialized correctly");
    set_task_indicator_info(task_info);
  
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  

        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
  
}

/*Init task function*/
void task_indicator_init(SIndTaskInfo_t *task_info,void *pvParams)
{
    // Set task ID
    task_info->ID = 4;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = IND_TASK_OK;
}