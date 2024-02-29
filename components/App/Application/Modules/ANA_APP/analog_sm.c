#include "analog_sm.h"
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
SAnaSmStates state_sm;

/* Initializes the analog state machine with the provided transition functions for each state */
ETaskStatus_t analog_sm_init(
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
        return ANA_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    state_sm.state_func[ANA_INIT].handle_execute = init_func;
    state_sm.state_func[ANA_INIT].handle_transition = init_transition;

    state_sm.state_func[ANA_READY].handle_execute = ready_func;
    state_sm.state_func[ANA_READY].handle_transition = ready_transition;

    state_sm.state_func[ANA_OPERATIONAL].handle_execute = operational_func;
    state_sm.state_func[ANA_OPERATIONAL].handle_transition = operational_transition;

    state_sm.state_func[ANA_BREAKDOWN].handle_execute = breakdown_func;
    state_sm.state_func[ANA_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    state_sm.st_event = STATE_IDLE;
    state_sm.sm_state = ANA_INIT;
    if (state_sm.sm_state == ANA_INIT) {
        return ANA_TASK_OK;
    } else {
        return ANA_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the analog state machine */
void analog_sm_run()
{
    state_sm.state_func[state_sm.sm_state].handle_execute();
    state_sm.state_func[state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the analog state machine */
ETaskState_t analog_sm_get_state()
{
    return state_sm.sm_state;
}

/* Sets the event for the analog state machine */
void analog_sm_set_st_event(EStateEvent_t event)
{
    state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (state_sm.st_event)
    {
    case STATE_NEXT:
        state_sm.sm_state = ANA_READY;
        state_sm.st_event = STATE_IDLE; 
        break;
    case STATE_FAULT:
        state_sm.sm_prev_state = state_sm.sm_state;
        state_sm.sm_state = ANA_BREAKDOWN;
        state_sm.st_event = STATE_IDLE; 
        break;
    default:
        state_sm.sm_state = ANA_INIT;
        state_sm.st_event = STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (state_sm.st_event)
    {
    case STATE_NEXT:
        state_sm.sm_state = ANA_OPERATIONAL;
        state_sm.st_event = STATE_IDLE; 
        break;
    case STATE_FAULT:
        state_sm.sm_prev_state = state_sm.sm_state;
        state_sm.sm_state = ANA_BREAKDOWN;
        state_sm.st_event = STATE_IDLE; 
        break;
    default:
        state_sm.sm_state = ANA_READY;
        state_sm.st_event = STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (state_sm.st_event)
    {
    case STATE_FAULT:
        state_sm.sm_prev_state = state_sm.sm_state;
        state_sm.sm_state = ANA_BREAKDOWN;
        state_sm.st_event = STATE_IDLE; 
        break;
    default:
        state_sm.sm_state = ANA_OPERATIONAL;
        state_sm.st_event = STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (state_sm.st_event)
    {
    case STATE_NEXT:
        state_sm.sm_state = ANA_INIT;
        state_sm.st_event = STATE_IDLE; 
        break;
    case STATE_PREV:
        state_sm.sm_state = state_sm.sm_prev_state;
        state_sm.st_event = STATE_IDLE; 
        break;
    default:
        state_sm.sm_state = ANA_BREAKDOWN;
        state_sm.st_event = STATE_IDLE; 
        break;
    }
}
