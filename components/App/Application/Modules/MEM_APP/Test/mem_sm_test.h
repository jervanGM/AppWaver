#ifndef MEM_SM_TEST_H_
#define MEM_SM_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for initializing the state machine with valid function pointers.
 *
 * This test function initializes the state machine with dummy initialization, operational, and breakdown functions.
 * It verifies that the state machine initialization returns MEM_TASK_OK.
 */
void test_mem_sm_init_valid_pointers(); /**< \test */

/**
 * @brief Test function for initializing the state machine with null function pointers.
 *
 * This test function initializes the state machine with null initialization, operational, and breakdown function pointers.
 * It verifies that the state machine initialization returns MEM_TASK_SM_INIT_FAIL.
 */
void test_mem_sm_init_null_pointers(); /**< \test */

/**
 * @brief Test function for verifying the transition from initialization to operational state in the state machine.
 *
 * This test function initializes the state machine with dummy functions, transitions to the operational state,
 * and verifies that the state transitions correctly.
 */
void test_mem_sm_init_to_operational_transition(); /**< \test */

/**
 * @brief Test function for verifying the transition from initialization to breakdown state in the state machine.
 *
 * This test function initializes the state machine with dummy functions, simulates a fault event to transition to the breakdown state,
 * and verifies that the state transitions correctly.
 */
void test_mem_sm_init_to_breakdown_transition(); /**< \test */

/**
 * @brief Test function for verifying the transition from operational to breakdown state in the state machine.
 *
 * This test function initializes the state machine with dummy functions, transitions to the operational state,
 * simulates a fault event to transition to the breakdown state, and verifies that the state transitions correctly.
 */
void test_mem_sm_operational_to_breakdown_transition(); /**< \test */

/**
 * @brief Test function for verifying the behavior of the state machine when transitioning to an unknown state from breakdown.
 *
 * This test function initializes the state machine with dummy functions, simulates a fault event to transition to the breakdown state,
 * and simulates a transition to an unknown state to verify that the state remains in breakdown.
 */
void test_mem_sm_breakdown_unknown_state_transition(); /**< \test */

/**
 * @brief Test function for verifying the behavior of the state machine when transitioning to an unknown state from initialization.
 *
 * This test function initializes the state machine with dummy functions and simulates a transition to an unknown state
 * during initialization to verify that the state remains in initialization.
 */
void test_mem_sm_init_unknown_state_transition(); /**< \test */

/**
 * @brief Test function for verifying the behavior of the state machine when transitioning to an unknown state from operational.
 *
 * This test function initializes the state machine with dummy functions, transitions to the operational state,
 * and simulates a transition to an unknown state to verify that the state remains in operational.
 */
void test_mem_sm_operational_unknown_state_transition(); /**< \test */

#endif /* MEM_SM_TEST_H_ */
