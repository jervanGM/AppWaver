#ifndef I_NETWORK_SM_H_
#define I_NETWORK_SM_H_
#include <stdint.h>

// #define SM_TRUE 1
// #define SM_FALSE 0

typedef enum{
    WLS_INIT,
    WLS_READY,
    WLS_OPERATIONAL,
    WLS_UPDATE,
    WLS_BREAKDOWN,
    WLS_UNKNOWN
}EWlsTaskState_t;

typedef enum{
    WLS_STATE_IDLE,
    WLS_STATE_NEXT,
    WLS_STATE_PREV,
    WLS_STATE_FAULT,
    WLS_STATE_UPGRADE
}EWlsStateEvent_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IWlsSmStateFunc;

typedef struct {
    EWlsTaskState_t sm_state;
    EWlsTaskState_t sm_prev_state;
    IWlsSmStateFunc state_func[WLS_UNKNOWN];
    EWlsStateEvent_t st_event;
} SWlsSmStates;

#endif /* I_NETWORK_SM_H_ */