#ifndef ANALOG_SM_H_
#define ANALOG_SM_H_

#include <stdbool.h>
#include "i_analog_sm.h"
#include "i_analog_data.h"


/**
 * @brief Initializes the analog state machine.
 * 
 * This function initializes the analog state machine by assigning the
 * provided initialization, ready, operational, and breakdown functions
 * to their respective state function pointers.
 * 
 * @param init_func Pointer to the initialization function.
 * @param ready_func Pointer to the ready function.
 * @param operational_func Pointer to the operational function.
 * @param breakdown_func Pointer to the breakdown function.
 * 
 * @return Status of the initialization process.
 */
ETaskStatus_t analog_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the analog state machine.
 * 
 * This function executes the current state's execute function and then
 * triggers the state transition function.
 */
void analog_sm_run();

/**
 * @brief Gets the current state of the analog state machine.
 * 
 * @return Current state of the state machine.
 */
ETaskState_t analog_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void analog_sm_set_st_event(EStateEvent_t event);
/**
 * @brief Transition function for the initialization state.
 * 
 * This function defines the state transitions for the initialization state
 * based on the event triggered.
 */
void init_transition();

/**
 * @brief Transition function for the ready state.
 * 
 * This function defines the state transitions for the ready state
 * based on the event triggered.
 */
void ready_transition();

/**
 * @brief Transition function for the operational state.
 * 
 * This function defines the state transitions for the operational state
 * based on the event triggered.
 */
void operational_transition();

/**
 * @brief Transition function for the breakdown state.
 * 
 * This function defines the state transitions for the breakdown state
 * based on the event triggered.
 */
void breakdown_transition();


#endif /* ANALOG_SM_H_ */