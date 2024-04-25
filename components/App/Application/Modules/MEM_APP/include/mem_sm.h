#ifndef MEM_SM_H_
#define MEM_SM_H_

#include <stdbool.h>
#include "i_mem_sm.h"
#include "i_mem_data.h"


/**
 * @brief Initializes the analog state machine.
 * 
 * This function initializes the analog state machine by assigning the
 * provided initialization, ready, operational, and breakdown functions
 * to their respective state function pointers.
 * 
 * @param init_func Pointer to the initialization function.
 * @param operational_func Pointer to the operational function.
 * @param breakdown_func Pointer to the breakdown function.
 * 
 * @return Status of the initialization process.
 */
EMemTaskStatus_t mem_sm_init
(
    void (*init_func)(void), 
    void (*operational_func)(void), 
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the analog state machine.
 * 
 * This function executes the current state's execute function and then
 * triggers the state transition function.
 */
void mem_sm_run();

/**
 * @brief Gets the current state of the analog state machine.
 * 
 * @return Current state of the state machine.
 */
EMemTaskState_t mem_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void mem_sm_set_st_event(EMemStateEvent_t event);

#endif /* MEM_SM_H_ */