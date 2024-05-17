#ifndef I_BUS_SM_H_
#define I_BUS_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    BUS_INIT,
    BUS_READY,
    BUS_OPERATIONAL,
    BUS_BREAKDOWN,
    BUS_UNKNOWN
}EBusTaskState_t;

typedef enum{
    BUS_STATE_IDLE,
    BUS_STATE_NEXT,
    BUS_STATE_PREV,
    BUS_STATE_FAULT
}EBusStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IBusSmStateFunc;

typedef struct {
    EBusTaskState_t sm_state;
    EBusTaskState_t sm_prev_state;
    IBusSmStateFunc state_func[BUS_UNKNOWN];
    EBusStateEvent_t st_event;
} SBusSmStates_t;

#endif /* I_BUS_SM_H_ */