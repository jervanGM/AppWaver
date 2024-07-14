#ifndef CTRL_SM_TEST_H_
#define CTRL_SM_TEST_H_

#include "test_suite.h"

/**
 * @brief Test case to verify the initialization of the state machine with valid function pointers.
 * 
 * This test initializes the control state machine with valid function pointers for initialization,
 * ready, operational, and breakdown states, and verifies that the initialization status is CTRL_TASK_OK.
 */
void test_control_sm_init_valid_pointers(); /**< \test */

/**
 * @brief Test case to verify the initialization of the state machine with null function pointers.
 * 
 * This test initializes the control state machine with null function pointers and verifies that
 * the initialization status is CTRL_TASK_SM_INIT_FAIL.
 */
void test_control_sm_init_null_pointers(); /**< \test */

/**
 * @brief Test case to verify the transition from initialization to operational in the state machine.
 * 
 * This test initializes the control state machine, transitions through the initialization,
 * ready, and operational states, and verifies that the state transitions occur correctly.
 */
void test_control_sm_init_to_operational_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from initialization to breakdown in the state machine.
 * 
 * This test initializes the control state machine, simulates a fault event to transition to the breakdown state,
 * and verifies the transition to breakdown and back to initialization.
 */
void test_control_sm_init_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from ready to breakdown in the state machine.
 * 
 * This test initializes the control state machine, transitions through initialization and ready states,
 * simulates a fault event to transition to breakdown, and verifies the transition to breakdown and back to ready.
 */
void test_control_sm_ready_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from operational to breakdown in the state machine.
 * 
 * This test initializes the control state machine, transitions through initialization, ready, and operational states,
 * simulates a fault event to transition to breakdown, and verifies the transition to breakdown and back to operational.
 */
void test_control_sm_operational_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify the behavior when transitioning to an unknown state from breakdown.
 * 
 * This test initializes the control state machine, simulates a fault event to transition to breakdown,
 * and attempts to transition to an unknown state. It verifies that the machine remains in the breakdown state.
 */
void test_control_sm_breakdown_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify the behavior when transitioning to an unknown state from initialization.
 * 
 * This test initializes the control state machine and attempts to transition to an unknown state
 * from the initialization state. It verifies that the machine remains in the initialization state.
 */
void test_control_sm_init_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify the behavior when transitioning to an unknown state from ready.
 * 
 * This test initializes the control state machine, transitions to the ready state, and attempts
 * to transition to an unknown state. It verifies that the machine remains in the ready state.
 */
void test_control_sm_ready_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify the behavior when transitioning to an unknown state from operational.
 * 
 * This test initializes the control state machine, transitions to the operational state, and attempts
 * to transition to an unknown state. It verifies that the machine remains in the operational state.
 */
void test_control_sm_operational_unknown_state_transition(); /**< \test */

#endif /* CTRL_SM_TEST_H_ */
