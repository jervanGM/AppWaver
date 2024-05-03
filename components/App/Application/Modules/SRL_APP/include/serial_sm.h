#ifndef SERIAL_SM_H_
#define SERIAL_SM_H_

#include <stdbool.h>
#include "i_serial_sm.h"
#include "i_serial_data.h"


/**
 * @brief Initializes the serial state machine.
 * 
 * This function initializes the serial state machine by assigning the
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
ESrlTaskStatus_t serial_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the serial state machine.
 * 
 * This function executes the current state's execute function and then
 * triggers the state transition function.
 */
void serial_sm_run();

/**
 * @brief Gets the current state of the serial state machine.
 * 
 * @return Current state of the state machine.
 */
ESrlTaskState_t serial_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void serial_sm_set_st_event(ESrlStateEvent_t event);



#endif /* SERIAL_SM_H_ */