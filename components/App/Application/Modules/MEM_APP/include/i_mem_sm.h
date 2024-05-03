#ifndef I_MEM_SM_H_
#define I_MEM_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    MEM_INIT,
    MEM_OPERATIONAL,
    MEM_BREAKDOWN,
    MEM_UNKNOWN
}EMemTaskState_t;

typedef enum{
    MEM_STATE_IDLE,
    MEM_STATE_NEXT,
    MEM_STATE_PREV,
    MEM_STATE_FAULT
}EMemStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IMemSmStateFunc;

typedef struct {
    EMemTaskState_t sm_state;
    EMemTaskState_t sm_prev_state;
    IMemSmStateFunc state_func[MEM_UNKNOWN];
    EMemStateEvent_t st_event;
} SMemSmStates;

#endif /* I_MEM_SM_H_ */