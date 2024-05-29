#ifndef BUS_SM_H_
#define BUS_SM_H_

#include <stdbool.h>
#include "i_bus_sm.h"
#include "i_bus_data.h"


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
EBusTaskStatus_t bus_sm_init
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
void bus_sm_run();

/**
 * @brief Gets the current state of the serial state machine.
 * 
 * @return Current state of the state machine.
 */
EBusTaskState_t bus_sm_get_state();

/**
 * @brief Sets the state machine event.
 * 
 * This function sets the event that triggers state transitions in the
 * state machine.
 * 
 * @param event State machine event.
 */
void bus_sm_set_st_event(EBusStateEvent_t event);



#endif /* BUS_SM_H_ */