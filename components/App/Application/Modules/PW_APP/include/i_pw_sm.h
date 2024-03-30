#ifndef I_PW_SM_H_
#define I_PW_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    PW_INIT,
    PW_READY,
    PW_OPERATIONAL,
    PW_BREAKDOWN,
    PW_UNKNOWN
}EPwTaskState_t;

typedef enum{
    PW_STATE_IDLE,
    PW_STATE_NEXT,
    PW_STATE_PREV,
    PW_STATE_FAULT
}EPwStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IPwSmStateFunc;

typedef struct {
    EPwTaskState_t sm_state;
    EPwTaskState_t sm_prev_state;
    IPwSmStateFunc state_func[PW_UNKNOWN];
    EPwStateEvent_t st_event;
} SPwSmStates;

#endif /* I_PW_SM_H_ */