#ifndef I_SERIAL_SM_H_
#define I_SERIAL_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    SRL_INIT,
    SRL_READY,
    SRL_OPERATIONAL,
    SRL_BREAKDOWN,
    SRL_UNKNOWN
}ESrlTaskState_t;

typedef enum{
    SRL_STATE_IDLE,
    SRL_STATE_NEXT,
    SRL_STATE_PREV,
    SRL_STATE_FAULT
}ESrlStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} ISrlSmStateFunc;

typedef struct {
    ESrlTaskState_t sm_state;
    ESrlTaskState_t sm_prev_state;
    ISrlSmStateFunc state_func[SRL_UNKNOWN];
    ESrlStateEvent_t st_event;
} SSrlSmStates;

#endif /* I_SERIAL_SM_H_ */