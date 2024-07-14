#ifndef PW_SM_H_
#define PW_SM_H_

#include <stdbool.h>
#include "i_pw_sm.h"
#include "i_pw_data.h"


/**
 * @brief Initializes the power state machine with the provided transition functions for each state.
 * 
 * @param init_func Initialization state function pointer
 * @param full_pw_func Full power state function pointer
 * @param low_pw_func Low power state function pointer
 * @param power_off_func Power off state function pointer
 * @param breakdown_func Breakdown state function pointer
 * @return EPwTaskStatus_t Status of the power state machine initialization
 */
EPwTaskStatus_t pw_sm_init(
    void (*init_func)(void),
    void (*full_pw_func)(void),
    void (*low_pw_func)(void),
    void (*power_off_func)(void),
    void (*breakdown_func)(void)
);

/**
 * @brief Runs the current state's execution function in the power state machine.
 */
void pw_sm_run();

/**
 * @brief Retrieves the current state of the power state machine.
 * 
 * @return EPwTaskState_t Current state of the power state machine
 */
EPwTaskState_t pw_sm_get_state();

/**
 * @brief Sets the event for the power state machine.
 * 
 * @param event Event to set for the power state machine
 */
void pw_sm_set_st_event(EPwStateEvent_t event);



#endif /* PW_SM_H_ */