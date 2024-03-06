#include "wireless_task.h"
#include "protocol_drv.h"
#include "network_sm.h"
#include "network_app.h"
#include "wireless_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"
#include "safe_memory.h"

/*Main wireless communication task function*/
void task_wireless(void *pvParameters)
{   
    // Initialize task information
    SWlsTaskInfo_t task_info;
    task_wireless_init(&task_info,pvParameters);
    init();
    anjay_main();
    /* Infinite loop */
    for(;;)
    {
        // Update task wake time
        task_info.LastWakeTime = get_task_tick_count();  
        // Run analog state machine

        // Delay task until next execution
        task_delay_until(&task_info.LastWakeTime, task_info.delay);
    }
}

/*Init task function*/
void task_wireless_init(SWlsTaskInfo_t *task_info,void *pvParams) 
{
    // Set task ID
    task_info->ID = 0;
    // Set task delay
    task_info->delay = *(uint32_t *)pvParams;
    // Initialize last wake time
    task_info->LastWakeTime = 0;
    // Set task status
    task_info->status = WLS_TASK_OK;
}


