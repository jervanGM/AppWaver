#include "analog_task.h"
#include "data_buffer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "assert_panic.h"
#include "safe_trace.h"


void taskAnalog(void *pvParameters)
{   
  TickType_t delay = pdMS_TO_TICKS(100);
	TickType_t xLastWakeTime;
  SDataBuffer_t plantbuffer = { .size = 0, .ready = false };
  /* Infinite loop */
  for(;;)
  {
		xLastWakeTime = xTaskGetTickCount();		
    plantbuffer = getSDataBuffer_t();
    if(plantbuffer.size>0 && plantbuffer.ready)
    {
      for(c_uint16_t i = 0;i<plantbuffer.size;i++)
      {
        TRACE_INFO("PLANT INFO:", TO_STRING(plantbuffer.data[i]));
      }
      TRACE_INFO("START TIME:", TO_STRING(plantbuffer.buffer_timestamp.start_time.sec));
      TRACE_INFO("END TIME:", TO_STRING(plantbuffer.buffer_timestamp.end_time.sec));
    }
		vTaskDelayUntil( &xLastWakeTime, delay);
  }
}

void taskAnalogInit()
{

}

void taskAnalogQGet()
{

}

void taskAnalogQSet()
{

}