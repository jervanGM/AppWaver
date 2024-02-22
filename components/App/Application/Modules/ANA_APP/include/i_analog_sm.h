#ifndef I_ANALOG_SM_H_
#define I_ANALOG_SM_H_
#include <stdint.h>

#define SM_TRUE 1
#define SM_FALSE 0

typedef enum{
    INIT,
    READY,
    OPERATIONAL,
    BREAKDOWN,
    UNKNOWN
}ETaskState_t;

typedef struct {
    void            (*handle_execute)  (void);
    void            (*handle_transition) (void);
} IAnaSmStateFunc;

typedef struct {
    ETaskState_t sm_state;
    IAnaSmStateFunc state_func[UNKNOWN];
    uint8_t change_event;
} SAnaSmStates;

#endif /* I_ANALOG_SM_H_ */