#ifndef I_CONTROL_SM_H_
#define I_CONTROL_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    CTRL_INIT,
    CTRL_READY,
    CTRL_OPERATIONAL,
    CTRL_BREAKDOWN,
    CTRL_UNKNOWN
}ECtrlTaskState_t;

typedef enum{
    CTRL_STATE_IDLE,
    CTRL_STATE_NEXT,
    CTRL_STATE_PREV,
    CTRL_STATE_FAULT
}ECtrlStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} ICtrlSmStateFunc;

typedef struct {
    ECtrlTaskState_t sm_state;
    ECtrlTaskState_t sm_prev_state;
    ICtrlSmStateFunc state_func[CTRL_UNKNOWN];
    ECtrlTaskState_t st_event;
} SCtrlSmStates;

#endif /* I_CONTROL_SM_H_ */