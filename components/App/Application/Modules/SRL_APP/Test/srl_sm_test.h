#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test case to verify initialization with valid function pointers.
 * 
 * It initializes the state machine with valid function pointers and verifies 
 * that the initialization result is SRL_TASK_OK.
 */
void test_serial_sm_init_valid_pointers(); /**< \test */

/**
 * @brief Test case to verify initialization with null function pointers.
 * 
 * It initializes the state machine with null function pointers and verifies 
 * that the initialization result is SRL_TASK_SM_INIT_FAIL.
 */
void test_serial_sm_init_null_pointers(); /**< \test */

/**
 * @brief Test case to verify the transition from initialization to operational state.
 * 
 * It initializes the state machine, triggers the state transition to operational, 
 * and verifies that the state is correctly set to SRL_OPERATIONAL.
 */
void test_serial_sm_init_to_operational_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from initialization to breakdown state.
 * 
 * It initializes the state machine, triggers the state transition to breakdown, 
 * and verifies that the state is correctly set to SRL_BREAKDOWN.
 */
void test_serial_sm_init_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from ready to breakdown state.
 * 
 * It initializes the state machine, transitions to the ready state, 
 * then triggers the state transition to breakdown, and verifies 
 * that the state is correctly set to SRL_BREAKDOWN.
 */
void test_serial_sm_ready_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify the transition from operational to breakdown state.
 * 
 * It initializes the state machine, transitions to the operational state, 
 * then triggers the state transition to breakdown, and verifies 
 * that the state is correctly set to SRL_BREAKDOWN.
 */
void test_serial_sm_operational_to_breakdown_transition(); /**< \test */

/**
 * @brief Test case to verify an unknown state transition from breakdown state.
 * 
 * It initializes the state machine, transitions to the breakdown state, 
 * triggers an unknown state transition, and verifies 
 * that the state remains in SRL_BREAKDOWN.
 */
void test_serial_sm_breakdown_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify an unknown state transition from initialization state.
 * 
 * It initializes the state machine, triggers an unknown state transition, 
 * and verifies that the state remains in SRL_INIT.
 */
void test_serial_sm_init_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify an unknown state transition from ready state.
 * 
 * It initializes the state machine, transitions to the ready state, 
 * triggers an unknown state transition, and verifies 
 * that the state remains in SRL_READY.
 */
void test_serial_sm_ready_unknown_state_transition(); /**< \test */

/**
 * @brief Test case to verify an unknown state transition from operational state.
 * 
 * It initializes the state machine, transitions to the operational state, 
 * triggers an unknown state transition, and verifies 
 * that the state remains in SRL_OPERATIONAL.
 */
void test_serial_sm_operational_unknown_state_transition(); /**< \test */


#endif /* TRACE_TEST_H_ */