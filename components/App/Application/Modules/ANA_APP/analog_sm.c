#include "analog_sm.h"

SAnaSmStates state_sm;

ETaskStatus_t analog_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
)
{
    state_sm.state_func[INIT].handle_execute = init_func;
    state_sm.state_func[INIT].handle_transition = init_transition;

    state_sm.state_func[READY].handle_execute = ready_func;
    state_sm.state_func[READY].handle_transition = ready_transition;

    state_sm.state_func[OPERATIONAL].handle_execute = operational_func;
    state_sm.state_func[OPERATIONAL].handle_transition = operational_transition;

    state_sm.state_func[BREAKDOWN].handle_execute = breakdown_func;
    state_sm.state_func[BREAKDOWN].handle_transition = breakdown_transition;

    state_sm.change_event = SM_FALSE;
    state_sm.sm_state = INIT;
    if(state_sm.sm_state == INIT)
    {
        return ANA_TASK_OK;
    }
    else
    {
        return ANA_TASK_SM_INIT_FAIL;
    }
}

void analog_sm_run()
{
    state_sm.state_func[state_sm.sm_state].handle_execute();
    state_sm.state_func[state_sm.sm_state].handle_transition();
}

ETaskState_t analog_sm_get_state()
{
     
    return state_sm.sm_state;
}

void analog_sm_set_event()
{
    state_sm.change_event = SM_TRUE;
}

void init_transition()
{
    switch (state_sm.change_event)
    {
    case SM_TRUE:
        state_sm.sm_state = READY;
        state_sm.change_event = SM_FALSE;
        break;
    case SM_FALSE:
        state_sm.sm_state = INIT;
        break;
    default:
        state_sm.sm_state = BREAKDOWN;
        state_sm.change_event = SM_FALSE;
        break;
    }
}

void ready_transition()
{
    switch (state_sm.change_event)
    {
    case SM_TRUE:
        state_sm.sm_state = OPERATIONAL;
        state_sm.change_event = SM_FALSE;
        break;
    case SM_FALSE:
        state_sm.sm_state = READY;
        break;
    default:
        state_sm.sm_state = BREAKDOWN;
        state_sm.change_event = SM_FALSE;
        break;
    }
}

void operational_transition()
{
    switch (state_sm.change_event)
    {
    case SM_TRUE:
        state_sm.sm_state = BREAKDOWN;
        state_sm.change_event = SM_FALSE;
        break;
    case SM_FALSE:
        state_sm.sm_state = OPERATIONAL;
        break;
    default:
        state_sm.sm_state = BREAKDOWN;
        state_sm.change_event = SM_FALSE;
        break;
    }
}

void breakdown_transition()
{
    switch (state_sm.change_event)
    {
    case SM_TRUE:
        state_sm.sm_state = INIT;
        state_sm.change_event = SM_FALSE;
        break;
    case SM_FALSE:
        state_sm.sm_state = BREAKDOWN;
        break;
    default:
        state_sm.sm_state = INIT;
        state_sm.change_event = SM_FALSE;
        break;
    }
}