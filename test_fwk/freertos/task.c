#include "task.h"


TickType_t xTaskGetTickCount( void )
{
    static uint32_t tickCount = 0;
    return tickCount++;
}