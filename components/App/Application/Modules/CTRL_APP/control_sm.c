#include "control_sm.h"
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
SCtrlSmStates ctrl_state_sm;

/* Initializes the control state machine with the provided transition functions for each state */
ECtrlTaskStatus_t control_sm_init(
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
        return CTRL_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    ctrl_state_sm.state_func[CTRL_INIT].handle_execute = init_func;
    ctrl_state_sm.state_func[CTRL_INIT].handle_transition = init_transition;

    ctrl_state_sm.state_func[CTRL_READY].handle_execute = ready_func;
    ctrl_state_sm.state_func[CTRL_READY].handle_transition = ready_transition;

    ctrl_state_sm.state_func[CTRL_OPERATIONAL].handle_execute = operational_func;
    ctrl_state_sm.state_func[CTRL_OPERATIONAL].handle_transition = operational_transition;

    ctrl_state_sm.state_func[CTRL_BREAKDOWN].handle_execute = breakdown_func;
    ctrl_state_sm.state_func[CTRL_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    ctrl_state_sm.st_event = CTRL_STATE_IDLE;
    ctrl_state_sm.sm_state = CTRL_INIT;
    if (ctrl_state_sm.sm_state == CTRL_INIT) {
        return CTRL_TASK_OK;
    } else {
        return CTRL_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the controller state machine */
void control_sm_run()
{
    ctrl_state_sm.state_func[ctrl_state_sm.sm_state].handle_execute();
    ctrl_state_sm.state_func[ctrl_state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the controller state machine */
ECtrlTaskState_t control_sm_get_state()
{
    return ctrl_state_sm.sm_state;
}

/* Sets the event for the controller state machine */
void control_sm_set_st_event(ECtrlStateEvent_t event)
{
    ctrl_state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (ctrl_state_sm.st_event)
    {
    case CTRL_STATE_NEXT:
        ctrl_state_sm.sm_state = CTRL_READY;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    case CTRL_STATE_FAULT:
        ctrl_state_sm.sm_prev_state = ctrl_state_sm.sm_state;
        ctrl_state_sm.sm_state = CTRL_BREAKDOWN;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    default:
        ctrl_state_sm.sm_state = CTRL_INIT;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (ctrl_state_sm.st_event)
    {
    case CTRL_STATE_NEXT:
        ctrl_state_sm.sm_state = CTRL_OPERATIONAL;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    case CTRL_STATE_FAULT:
        ctrl_state_sm.sm_prev_state = ctrl_state_sm.sm_state;
        ctrl_state_sm.sm_state = CTRL_BREAKDOWN;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    default:
        ctrl_state_sm.sm_state = CTRL_READY;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (ctrl_state_sm.st_event)
    {
    case CTRL_STATE_FAULT:
        ctrl_state_sm.sm_prev_state = ctrl_state_sm.sm_state;
        ctrl_state_sm.sm_state = CTRL_BREAKDOWN;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    default:
        ctrl_state_sm.sm_state = CTRL_OPERATIONAL;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (ctrl_state_sm.st_event)
    {
    case CTRL_STATE_NEXT:
        ctrl_state_sm.sm_state = CTRL_INIT;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    case CTRL_STATE_PREV:
        ctrl_state_sm.sm_state = ctrl_state_sm.sm_prev_state;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    default:
        ctrl_state_sm.sm_state = CTRL_BREAKDOWN;
        ctrl_state_sm.st_event = CTRL_STATE_IDLE; 
        break;
    }
}
