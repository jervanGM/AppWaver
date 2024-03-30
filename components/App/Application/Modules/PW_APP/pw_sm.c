#include "pw_sm.h"
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
SPwSmStates pw_state_sm;

/* Initializes the analog state machine with the provided transition functions for each state */
EPwTaskStatus_t pw_sm_init(
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
        return PW_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    pw_state_sm.state_func[PW_INIT].handle_execute = init_func;
    pw_state_sm.state_func[PW_INIT].handle_transition = init_transition;

    pw_state_sm.state_func[PW_READY].handle_execute = ready_func;
    pw_state_sm.state_func[PW_READY].handle_transition = ready_transition;

    pw_state_sm.state_func[PW_OPERATIONAL].handle_execute = operational_func;
    pw_state_sm.state_func[PW_OPERATIONAL].handle_transition = operational_transition;

    pw_state_sm.state_func[PW_BREAKDOWN].handle_execute = breakdown_func;
    pw_state_sm.state_func[PW_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    pw_state_sm.st_event = PW_STATE_IDLE;
    pw_state_sm.sm_state = PW_INIT;
    if (pw_state_sm.sm_state == PW_INIT) {
        return PW_TASK_OK;
    } else {
        return PW_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the analog state machine */
void pw_sm_run()
{
    pw_state_sm.state_func[pw_state_sm.sm_state].handle_execute();
    pw_state_sm.state_func[pw_state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the analog state machine */
EPwTaskState_t pw_sm_get_state()
{
    return pw_state_sm.sm_state;
}

/* Sets the event for the analog state machine */
void pw_sm_set_st_event(EPwStateEvent_t event)
{
    pw_state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (pw_state_sm.st_event)
    {
    case PW_STATE_NEXT:
        pw_state_sm.sm_state = PW_READY;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    case PW_STATE_FAULT:
        pw_state_sm.sm_prev_state = pw_state_sm.sm_state;
        pw_state_sm.sm_state = PW_BREAKDOWN;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    default:
        pw_state_sm.sm_state = PW_INIT;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (pw_state_sm.st_event)
    {
    case PW_STATE_NEXT:
        pw_state_sm.sm_state = PW_OPERATIONAL;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    case PW_STATE_FAULT:
        pw_state_sm.sm_prev_state = pw_state_sm.sm_state;
        pw_state_sm.sm_state = PW_BREAKDOWN;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    default:
        pw_state_sm.sm_state = PW_READY;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (pw_state_sm.st_event)
    {
    case PW_STATE_FAULT:
        pw_state_sm.sm_prev_state = pw_state_sm.sm_state;
        pw_state_sm.sm_state = PW_BREAKDOWN;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    default:
        pw_state_sm.sm_state = PW_OPERATIONAL;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (pw_state_sm.st_event)
    {
    case PW_STATE_NEXT:
        pw_state_sm.sm_state = PW_INIT;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    case PW_STATE_PREV:
        pw_state_sm.sm_state = pw_state_sm.sm_prev_state;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    default:
        pw_state_sm.sm_state = PW_BREAKDOWN;
        pw_state_sm.st_event = PW_STATE_IDLE; 
        break;
    }
}
