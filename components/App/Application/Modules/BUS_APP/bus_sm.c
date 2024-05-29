#include "bus_sm.h"
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
SBusSmStates_t bus_state_sm;

/* Initializes the serial state machine with the provided transition functions for each state */
EBusTaskStatus_t bus_sm_init(
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
        return BUS_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    bus_state_sm.state_func[BUS_INIT].handle_execute = init_func;
    bus_state_sm.state_func[BUS_INIT].handle_transition = init_transition;

    bus_state_sm.state_func[BUS_READY].handle_execute = ready_func;
    bus_state_sm.state_func[BUS_READY].handle_transition = ready_transition;

    bus_state_sm.state_func[BUS_OPERATIONAL].handle_execute = operational_func;
    bus_state_sm.state_func[BUS_OPERATIONAL].handle_transition = operational_transition;

    bus_state_sm.state_func[BUS_BREAKDOWN].handle_execute = breakdown_func;
    bus_state_sm.state_func[BUS_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    bus_state_sm.st_event = BUS_STATE_IDLE;
    bus_state_sm.sm_state = BUS_INIT;
    if (bus_state_sm.sm_state == BUS_INIT) {
        return BUS_TASK_OK;
    } else {
        return BUS_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the serial state machine */
void bus_sm_run()
{
    bus_state_sm.state_func[bus_state_sm.sm_state].handle_execute();
    bus_state_sm.state_func[bus_state_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the serial state machine */
EBusTaskState_t bus_sm_get_state()
{
    return bus_state_sm.sm_state;
}

/* Sets the event for the serial state machine */
void bus_sm_set_st_event(EBusStateEvent_t event)
{
    bus_state_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (bus_state_sm.st_event)
    {
    case BUS_STATE_NEXT:
        bus_state_sm.sm_state = BUS_READY;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    case BUS_STATE_FAULT:
        bus_state_sm.sm_prev_state = bus_state_sm.sm_state;
        bus_state_sm.sm_state = BUS_BREAKDOWN;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    default:
        bus_state_sm.sm_state = BUS_INIT;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the ready state */
static void ready_transition()
{
    switch (bus_state_sm.st_event)
    {
    case BUS_STATE_NEXT:
        bus_state_sm.sm_state = BUS_OPERATIONAL;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    case BUS_STATE_FAULT:
        bus_state_sm.sm_prev_state = bus_state_sm.sm_state;
        bus_state_sm.sm_state = BUS_BREAKDOWN;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    default:
        bus_state_sm.sm_state = BUS_READY;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (bus_state_sm.st_event)
    {
    case BUS_STATE_FAULT:
        bus_state_sm.sm_prev_state = bus_state_sm.sm_state;
        bus_state_sm.sm_state = BUS_BREAKDOWN;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;  
    default:
        bus_state_sm.sm_state = BUS_OPERATIONAL;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (bus_state_sm.st_event)
    {
    case BUS_STATE_NEXT:
        bus_state_sm.sm_state = BUS_INIT;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    case BUS_STATE_PREV:
        bus_state_sm.sm_state = bus_state_sm.sm_prev_state;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    default:
        bus_state_sm.sm_state = BUS_BREAKDOWN;
        bus_state_sm.st_event = BUS_STATE_IDLE; 
        break;
    }
}
