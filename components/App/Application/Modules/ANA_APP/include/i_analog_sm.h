#ifndef I_ANALOG_SM_H_
#define I_ANALOG_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    ANA_INIT,
    ANA_READY,
    ANA_OPERATIONAL,
    ANA_BREAKDOWN,
    ANA_UNKNOWN
}ETaskState_t;

typedef enum{
    STATE_IDLE,
    STATE_NEXT,
    STATE_PREV,
    STATE_FAULT
}EStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IAnaSmStateFunc;

typedef struct {
    ETaskState_t sm_state;
    ETaskState_t sm_prev_state;
    IAnaSmStateFunc state_func[ANA_UNKNOWN];
    EStateEvent_t st_event;
} SAnaSmStates;

#endif /* I_ANALOG_SM_H_ */