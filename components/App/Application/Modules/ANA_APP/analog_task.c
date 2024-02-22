#include "analog_task.h"
#include "analog_drv.h"
#include "analog_sm.h"
#include "analog_app.h"
#include "analog_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"

STaskInfo_t task_info;

void task_analog(void *pvParameters)
{   
  
  task_analog_init(&task_info,pvParameters);

  task_info.status = analog_sm_init(on_ana_init,
                                  on_ana_ready,
                                  on_ana_execute,
                                  on_ana_breakdown);
  /* Infinite loop */
  for(;;)
  {
		task_info.LastWakeTime = get_task_tick_count();	
    analog_sm_run();
		task_delay_until(&task_info.LastWakeTime, task_info.delay);
  }
}

void task_analog_init(STaskInfo_t *task_info,void *pvParams) 
{
  task_info->ID = 0;
  task_info->delay = *(uint32_t *)pvParams;
  task_info->LastWakeTime = 0;
  task_info->status = ANA_TASK_OK;
}

void on_ana_init()
{
  analog_init();
  analog_app_init();
  analog_sm_set_event();
}

void on_ana_ready()
{
  static SDataBuffer_t plant_buff = { .size = 0, .ready = false };
  static SBufferTime_t buffer_time;
  analog_app_check();
  //Ignore first data buffer for signal stabilization
  get_data_buffer(&plant_buff,&buffer_time);
  analog_app_check();
  if(plant_buff.ready)
  {
    analog_sm_set_event();
  }
  else
  {
    //TBD
  }

}

void on_ana_execute()
{
  static SDataBuffer_t plant_buff = { .size = 0, .ready = false };
  static SBufferTime_t buffer_time;
  get_data_buffer(&plant_buff,&buffer_time);
  analog_app_check();
  analog_controller_send(task_info,plant_buff,buffer_time);
}

void on_ana_breakdown()
{

}
