#include "control_task.h"
#include "analog_t_share.h"
#include "assert_panic.h"
#include "safe_trace.h"
#include "rtos.h"

void task_control(void *pvParameters)
{   
  SAnaTaskInfo_t task_info;
  task_info.delay = *(uint32_t *)pvParameters;
  /* Infinite loop */
  for(;;)
  {
		task_info.LastWakeTime = get_task_tick_count();	
    SAnalogSensMsg_t msg;
    analog_controller_read(&msg);
    if(msg._plant_buff.size>0 && msg._plant_buff.ready)
    {
      for(uint16_t i = 0;i<msg._plant_buff.size;i++)
      {
        TRACE_INFO("PLANT INFO:", TO_STRING(msg._plant_buff.data[i]));
      }
      TRACE_INFO("CONTROL START TIME:", TO_STRING(msg._buff_time.start_time.sec));
      TRACE_INFO("CONTROL END TIME:", TO_STRING(msg._buff_time.end_time.sec));
    }
		task_delay_until(&task_info.LastWakeTime, task_info.delay);
  }
}

void task_control_init(SAnaTaskInfo_t *task_info,void *pvParams) 
{
}

void on_ctrl_init()
{
}

void on_ctrl_ready()
{
}

void on_ctrl_execute()
{
}

void on_ctrl_breakdown()
{
}