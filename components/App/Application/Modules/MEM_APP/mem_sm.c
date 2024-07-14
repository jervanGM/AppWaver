#include "mem_sm.h"
#include "safe_trace.h"

/**
 * @brief Transition function for the initialization state.
 * 
 * This function defines the state transitions for the initialization state
 * based on the event triggered.
 */
static void init_transition();

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
SMemSmStates state_mem_sm;

/* Initializes the external memory state machine with the provided transition functions for each state */
EMemTaskStatus_t mem_sm_init(
    void (*init_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
)
{
    /* Verify if any of the function pointers is null */
    if (init_func == NULL || 
        operational_func == NULL || breakdown_func == NULL) {
        TRACE_ERROR("Any execute state function is null or not valid");
        return MEM_TASK_SM_INIT_FAIL; // Return failure if any function pointer is null
    }
    /* Assigns the provided functions to the corresponding states in the state machine */
    state_mem_sm.state_func[MEM_INIT].handle_execute = init_func;
    state_mem_sm.state_func[MEM_INIT].handle_transition = init_transition;

    state_mem_sm.state_func[MEM_OPERATIONAL].handle_execute = operational_func;
    state_mem_sm.state_func[MEM_OPERATIONAL].handle_transition = operational_transition;

    state_mem_sm.state_func[MEM_BREAKDOWN].handle_execute = breakdown_func;
    state_mem_sm.state_func[MEM_BREAKDOWN].handle_transition = breakdown_transition;

    /* Sets the initial state and checks if it's successfully set */
    state_mem_sm.st_event = MEM_STATE_IDLE;
    state_mem_sm.sm_state = MEM_INIT;
    if (state_mem_sm.sm_state == MEM_INIT) {
        return MEM_TASK_OK;
    } else {
        return MEM_TASK_SM_INIT_FAIL;
    }
}

/* Runs the current state's execution function in the external memory state machine */
void mem_sm_run()
{
    state_mem_sm.state_func[state_mem_sm.sm_state].handle_execute();
    state_mem_sm.state_func[state_mem_sm.sm_state].handle_transition();
}

/* Retrieves the current state of the external memory state machine */
EMemTaskState_t mem_sm_get_state()
{
    return state_mem_sm.sm_state;
}

/* Sets the event for the external memory state machine */
void mem_sm_set_st_event(EMemStateEvent_t event)
{
    state_mem_sm.st_event = event;
}

/* Transition function for the initialization state */
static void init_transition()
{
    switch (state_mem_sm.st_event)
    {
    case MEM_STATE_NEXT:
        state_mem_sm.sm_state = MEM_OPERATIONAL;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    case MEM_STATE_FAULT:
        state_mem_sm.sm_prev_state = state_mem_sm.sm_state;
        state_mem_sm.sm_state = MEM_BREAKDOWN;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    default:
        state_mem_sm.sm_state = MEM_INIT;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    }
}

/* Transition function for the operational state */
static void operational_transition()
{
    switch (state_mem_sm.st_event)
    {
    case MEM_STATE_FAULT:
        state_mem_sm.sm_prev_state = state_mem_sm.sm_state;
        state_mem_sm.sm_state = MEM_BREAKDOWN;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    default:
        state_mem_sm.sm_state = MEM_OPERATIONAL;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    }
}

/* Transition function for the breakdown state */
static void breakdown_transition()
{
    switch (state_mem_sm.st_event)
    {
    case MEM_STATE_NEXT:
        state_mem_sm.sm_state = MEM_INIT;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    case MEM_STATE_PREV:
        state_mem_sm.sm_state = state_mem_sm.sm_prev_state;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    default:
        state_mem_sm.sm_state = MEM_BREAKDOWN;
        state_mem_sm.st_event = MEM_STATE_IDLE; 
        break;
    }
}
