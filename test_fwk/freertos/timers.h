#ifndef TIMERS_H_
#define TIMERS_H_

#include "task.h"
typedef int BaseType_t;
// Definición del tipo de la función de callback del temporizador
typedef void (*TimerCallbackFunction_t)(void *);
// Definición de las constantes para los comandos
#define tmrCOMMAND_DELETE         1
#define tmrCOMMAND_CHANGE_PERIOD  2
#define pdFALSE                                  ( ( BaseType_t ) 0 )
#define pdTRUE                                   ( ( BaseType_t ) 1 )

#define pdPASS                                   ( pdTRUE )
#define pdFAIL                                   ( pdFALSE )
#define errQUEUE_EMPTY                           ( ( BaseType_t ) 0 )
#define errQUEUE_FULL                            ( ( BaseType_t ) 0 )

// Definición del tipo de la estructura de handle del temporizador
typedef struct TimerHandle {
    const char *name;
    uint32_t period;
    bool autoReload;
    int isActive;
    void *timerID;
    TickType_t expiryTime;
    TimerCallbackFunction_t callback;
} TimerHandle_t;

TimerHandle_t *xTimerCreate(const char * const pcTimerName,
                            const uint32_t xTimerPeriodInTicks,
                            const bool uxAutoReload,
                            void * const pvTimerID,
                            TimerCallbackFunction_t pxCallbackFunction);

TickType_t xTimerGetExpiryTime( TimerHandle_t xTimer );
BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer );
BaseType_t xTimerGenericCommand(TimerHandle_t xTimer,
                                 const BaseType_t xCommandID,
                                 const TickType_t xOptionalValue,
                                 BaseType_t * const pxHigherPriorityTaskWoken,
                                 const TickType_t xTicksToWait);

#define xTimerChangePeriod( xTimer, xNewPeriod, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_CHANGE_PERIOD, ( xNewPeriod ), NULL, ( xTicksToWait ) )

#define xTimerDelete( xTimer, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_DELETE, 0U, NULL, ( xTicksToWait ) )

#endif /* TIMERS_H_ */