#ifndef PW_SM_TEST_H_
#define PW_SM_TEST_H_

#include "test_suite.h"


/**
 * @brief Test the initialization of the state machine with valid function pointers.
 *
 * This test initializes the power state machine with valid function pointers
 * and verifies that the initialization succeeds.
 */
void test_pw_sm_init_valid_pointers(); /**< \test */

/**
 * @brief Test the initialization of the state machine with null function pointers.
 *
 * This test initializes the power state machine with null function pointers
 * and verifies that the initialization fails with the expected error code.
 */
void test_pw_sm_init_null_pointers(); /**< \test */

/**
 * @brief Test the transition from initialization to full power state in the state machine.
 *
 * This test verifies the transition from the initialization state to the full power state
 * in the power state machine.
 */
void test_pw_sm_init_to_full_pw_transition(); /**< \test */

/**
 * @brief Test the transition from initialization to breakdown state in the state machine.
 *
 * This test verifies the transition from the initialization state to the breakdown state
 * in the power state machine.
 */
void test_pw_sm_init_to_breakdown_transition(); /**< \test */

/**
 * @brief Test the transition from full power to breakdown state in the state machine.
 *
 * This test verifies the transition from the full power state to the breakdown state
 * in the power state machine.
 */
void test_pw_sm_full_pw_to_breakdown_transition(); /**< \test */

/**
 * @brief Test the transition from low power to breakdown state in the state machine.
 *
 * This test verifies the transition from the low power state to the breakdown state
 * in the power state machine.
 */
void test_pw_sm_low_power_to_breakdown_transition(); /**< \test */

/**
 * @brief Test the transition from power off to breakdown state in the state machine.
 *
 * This test verifies the transition from the power off state to the breakdown state
 * in the power state machine.
 */
void test_pw_sm_power_off_to_breakdown_transition(); /**< \test */

/**
 * @brief Test the transition from initialization to power off state in the state machine.
 *
 * This test verifies the transition from the initialization state to the power off state
 * in the power state machine.
 */
void test_pw_sm_init_to_power_off_transition(); /**< \test */

/**
 * @brief Test the transition from full power to power off state in the state machine.
 *
 * This test verifies the transition from the full power state to the power off state
 * in the power state machine.
 */
void test_pw_sm_full_pw_to_power_off_transition(); /**< \test */

/**
 * @brief Test the transition from low power to power off state in the state machine.
 *
 * This test verifies the transition from the low power state to the power off state
 * in the power state machine.
 */
void test_pw_sm_low_power_to_power_off_transition(); /**< \test */

/**
 * @brief Test the behavior of the state machine when transitioning to an unknown state from breakdown.
 *
 * This test verifies the behavior of the power state machine when transitioning
 * to an unknown state from the breakdown state.
 */
void test_pw_sm_breakdown_unknown_state_transition(); /**< \test */

/**
 * @brief Test the behavior of the state machine when transitioning to an unknown state from initialization.
 *
 * This test verifies the behavior of the power state machine when transitioning
 * to an unknown state from the initialization state.
 */
void test_pw_sm_init_unknown_state_transition(); /**< \test */

/**
 * @brief Test the behavior of the state machine when transitioning to an unknown state from full power.
 *
 * This test verifies the behavior of the power state machine when transitioning
 * to an unknown state from the full power state.
 */
void test_pw_sm_full_pw_unknown_state_transition(); /**< \test */

/**
 * @brief Test the behavior of the state machine when transitioning to an unknown state from low power.
 *
 * This test verifies the behavior of the power state machine when transitioning
 * to an unknown state from the low power state.
 */
void test_pw_sm_low_pw_unknown_state_transition(); /**< \test */

/**
 * @brief Test the behavior of the state machine when transitioning to an unknown state from power off.
 *
 * This test verifies the behavior of the power state machine when transitioning
 * to an unknown state from the power off state.
 */
void test_pw_sm_pw_off_unknown_state_transition(); /**< \test */

/**
 * @brief Test the transition from full power to low power state in the state machine.
 *
 * This test verifies the transition from the full power state to the low power state
 * in the power state machine.
 */
void test_pw_sm_full_pw_to_low_pw_transition(); /**< \test */

/**
 * @brief Test the transition from low power to full power state in the state machine.
 *
 * This test verifies the transition from the low power state to the full power state
 * in the power state machine.
 */
void test_pw_sm_low_pw_to_full_pw_transition(); /**< \test */

#endif /* PW_SM_TEST_H_ */
