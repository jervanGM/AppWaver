#include "serial_sm.h"
#include "safe_trace.h"

/**
 * @brief Transition function for the initialization state.
 * 
 * This function defines the state transitions for the initialization state
 * based on the event triggered.
 */
static void init_transition();

/**
 * @brief Transition function for the ready state.
 * 
 * This function defines the state transitions for the ready state
 * based on the event triggered.
 */
static void ready_transition();

/**
 * @brief Transition function for the operational state.
 * 
 * This function defines the state transitions for the operational state
 * based on the event triggered.
 */
static void operational_transition();

/**
 * @brief Transition function for the breakdown state.
 * 
 * This function defines the state transitions for the breakdown state
 * based on the event triggered.
 */
static void breakdown_transition();

/* Define the state machine states */
SSrlSmStates srl_state_sm;

/* Initializes the serial state machine with the provided transition functions for each state */
ESrlTaskStatus_t serial_sm_init(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
)
{
    /* Verify if any of the function pointers is null */
    if (init_func == NULL || ready_func == NULL || 
        operational_func == NULL || breakdown_func == NULL) {
        TRACE_ERROR("Any execute state function is null or not valid");
        return SRL_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    srl_state_sm.state_func[SRL_INIT].handle_execute = init_func;
    srl_state_sm.state_func[SRL_INIT].handle_transition = init_transition;

    srl_state_sm.state_func[SRL_READY].handle_execute = ready_func;
    srl_state_sm.state_func[SRL_READY].handle_transition = ready_transition;

    srl_state_sm.state_func[SRL_OPERATIONAL].handle_execute = operational_func;
    srl_state_sm.state_func[SRL_OPERATIONAL].handle_transition = operational_transition;

    srl_state_sm.state_func[SRL_BREAKDOWN].handle_execute = breakdown_func;
    srl_state_sm.state_func[SRL_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    srl_state_sm.st_event = SRL_STATE_IDLE;
    srl_state_sm.sm_state = SRL_INIT;
    if (srl_state_sm.sm_state == SRL_INIT) {
        return SRL_TASK_OK;
    } else {
        return SRL_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the serial state machine */
void serial_sm_run()
{
    srl_state_sm.state_func[srl_state_sm.sm_state].handle_execute();
    srl_state_sm.state_func[srl_state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the serial state machine */
ESrlTaskState_t serial_sm_get_state()
{
    return srl_state_sm.sm_state;
}

/* Sets the event for the serial state machine */
void serial_sm_set_st_event(ESrlStateEvent_t event)
{
    srl_state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (srl_state_sm.st_event)
    {
    case SRL_STATE_NEXT:
        srl_state_sm.sm_state = SRL_READY;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    case SRL_STATE_FAULT:
        srl_state_sm.sm_prev_state = srl_state_sm.sm_state;
        srl_state_sm.sm_state = SRL_BREAKDOWN;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    default:
        srl_state_sm.sm_state = SRL_INIT;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (srl_state_sm.st_event)
    {
    case SRL_STATE_NEXT:
        srl_state_sm.sm_state = SRL_OPERATIONAL;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    case SRL_STATE_FAULT:
        srl_state_sm.sm_prev_state = srl_state_sm.sm_state;
        srl_state_sm.sm_state = SRL_BREAKDOWN;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    default:
        srl_state_sm.sm_state = SRL_READY;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (srl_state_sm.st_event)
    {
    case SRL_STATE_FAULT:
        srl_state_sm.sm_prev_state = srl_state_sm.sm_state;
        srl_state_sm.sm_state = SRL_BREAKDOWN;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    case SRL_STATE_PREV:
        srl_state_sm.sm_state = SRL_READY;
        srl_state_sm.st_event = SRL_STATE_IDLE;  
        break;   
    default:
        srl_state_sm.sm_state = SRL_OPERATIONAL;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (srl_state_sm.st_event)
    {
    case SRL_STATE_NEXT:
        srl_state_sm.sm_state = SRL_INIT;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    case SRL_STATE_PREV:
        srl_state_sm.sm_state = srl_state_sm.sm_prev_state;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    default:
        srl_state_sm.sm_state = SRL_BREAKDOWN;
        srl_state_sm.st_event = SRL_STATE_IDLE; 
        break;
    }
}
