#ifndef NETWORK_SM_H_
#define NETWORK_SM_H_

#include <stdbool.h>
#include "i_network_sm.h"
#include "i_wireless_data.h"

/**
 * @brief Initializes the network state machine.
 * 
 * This function initializes the network state machine by assigning the
 * provided initialization, ready, operational, and breakdown functions
 * to their respective state function pointers.
 * 
 * @param init_func Pointer to the initialization function.
 * @param ready_func Pointer to the ready function.
 * @param operational_func Pointer to the operational function.
 * @param update_func Pointer to the software update function.
 * @param breakdown_func Pointer to the breakdown function.
 * 
 * @return Status of the initialization process.
 */
EWlsTaskStatus_t network_sm_init
(
    void (*init_func)(void), 
    void (*ready_func)(void), 
    void (*operational_func)(void), 
    void (*update_func)(void), 
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the network state machine.
 * 
 * This function executes the current state's execute function and then
 * triggers the state transition function.
 */
void network_sm_run();

/**
 * @brief Gets the current state of the network state machine.
 * 
 * @return Current state of the state machine.
 */
EWlsTaskState_t network_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void network_sm_set_st_event(EWlsStateEvent_t event);

#endif /* NETWORK_SM_H_ */