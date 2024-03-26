#ifndef CONTROL_SM_H_
#define CONTROL_SM_H_

#include <stdbool.h>
#include "i_control_sm.h"
#include "i_control_data.h"

/**
 * @brief Initializes the control state machine.
 * 
 * This function initializes the control state machine by assigning the
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
ECtrlTaskStatus_t control_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the control state machine.
 * 
 * This function executes the current state's execute function and then
 * triggers the state transition function.
 */
void control_sm_run();

/**
 * @brief Gets the current state of the control state machine.
 * 
 * @return Current state of the state machine.
 */
ECtrlTaskState_t control_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void control_sm_set_st_event(ECtrlStateEvent_t event);

#endif /* CONTROL_SM_H_ */