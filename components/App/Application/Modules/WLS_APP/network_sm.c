#include "network_sm.h"
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
SWlsSmStates wls_state_sm;

/* Initializes the network state machine with the provided transition functions for each state */
EWlsTaskStatus_t network_sm_init(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*update_func)(void), 
    void (*breakdown_func)(void)
)
{
    /* Verify if any of the function pointers is null */
    if (init_func == NULL || ready_func == NULL || 
        operational_func == NULL || update_func == NULL ||
        breakdown_func == NULL) {
        TRACE_ERROR("Any execute state function is null or not valid");
        return WLS_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    wls_state_sm.state_func[WLS_INIT].handle_execute = init_func;
    wls_state_sm.state_func[WLS_INIT].handle_transition = init_transition;

    wls_state_sm.state_func[WLS_READY].handle_execute = ready_func;
    wls_state_sm.state_func[WLS_READY].handle_transition = ready_transition;

    wls_state_sm.state_func[WLS_OPERATIONAL].handle_execute = operational_func;
    wls_state_sm.state_func[WLS_OPERATIONAL].handle_transition = operational_transition;

    wls_state_sm.state_func[WLS_UPDATE].handle_execute = update_func;

    wls_state_sm.state_func[WLS_BREAKDOWN].handle_execute = breakdown_func;
    wls_state_sm.state_func[WLS_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    wls_state_sm.st_event = WLS_STATE_IDLE;
    wls_state_sm.sm_state = WLS_INIT;
    if (wls_state_sm.sm_state == WLS_INIT) {
        return WLS_TASK_OK;
    } else {
        return WLS_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the network state machine */
void network_sm_run()
{
    wls_state_sm.state_func[wls_state_sm.sm_state].handle_execute();
    wls_state_sm.state_func[wls_state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the network state machine */
EWlsTaskState_t network_sm_get_state()
{
    return wls_state_sm.sm_state;
}

/* Sets the event for the network state machine */
void network_sm_set_st_event(EWlsStateEvent_t event)
{
    wls_state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (wls_state_sm.st_event)
    {
    case WLS_STATE_NEXT:
        wls_state_sm.sm_state = WLS_READY;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_UPGRADE:
        wls_state_sm.sm_state = WLS_UPDATE;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_FAULT:
        wls_state_sm.sm_prev_state = wls_state_sm.sm_state;
        wls_state_sm.sm_state = WLS_BREAKDOWN;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    default:
        wls_state_sm.sm_state = WLS_INIT;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (wls_state_sm.st_event)
    {
    case WLS_STATE_NEXT:
        wls_state_sm.sm_state = WLS_OPERATIONAL;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_UPGRADE:
        wls_state_sm.sm_state = WLS_UPDATE;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_FAULT:
        wls_state_sm.sm_prev_state = wls_state_sm.sm_state;
        wls_state_sm.sm_state = WLS_BREAKDOWN;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    default:
        wls_state_sm.sm_state = WLS_READY;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (wls_state_sm.st_event)
    {
    case WLS_STATE_UPGRADE:
        wls_state_sm.sm_state = WLS_UPDATE;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_FAULT:
        wls_state_sm.sm_prev_state = wls_state_sm.sm_state;
        wls_state_sm.sm_state = WLS_BREAKDOWN;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    default:
        wls_state_sm.sm_state = WLS_OPERATIONAL;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (wls_state_sm.st_event)
    {
    case WLS_STATE_NEXT:
        wls_state_sm.sm_state = WLS_INIT;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_PREV:
        wls_state_sm.sm_state = wls_state_sm.sm_prev_state;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    case WLS_STATE_RECONNECT:
        wls_state_sm.sm_state = WLS_READY;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;  
    default:
        wls_state_sm.sm_state = WLS_BREAKDOWN;
        wls_state_sm.st_event = WLS_STATE_IDLE; 
        break;
    }
}
