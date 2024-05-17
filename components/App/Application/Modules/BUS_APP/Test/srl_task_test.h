#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test the initialization of the serial task with a fatal error in the initialization function.
 * 
 * This test case verifies the behavior of the serial task initialization when a fatal error occurs 
 * in the initialization function. It initializes the task information and delay, then initializes 
 * the serial state machine executing a fake hal port with errors. The test ensures that 
 * the initial state is BUS_INIT, executes the state machine once to verify the transition to 
 * BUS_BREAKDOWN, and then executes it again to verify the transition back to BUS_INIT.
 */
void test_srl_task_init_fatal_error(); /**< \test */

/**
 * @brief Test the breakdown of the serial task with a fatal error in the ready function.
 * 
 * This test case validates the behavior of the serial task breakdown when a fatal error occurs 
 * in the ready function. It initializes the task information and delay, then initializes the 
 * serial state machine with a dummy initialization function and function pointers that cause 
 * a fatal error in the ready function. The test ensures that the initial state is BUS_INIT, 
 * sets next state event, executes the state machine until it transitions to BUS_BREAKDOWN, 
 * and verifies the transition back to BUS_INIT upon subsequent execution.
 */
void test_srl_task_breakdown_ready_fatal_error(); /**< \test */

/**
 * @brief Test the breakdown of the serial task with a fatal error in the operational function.
 * 
 * This test case examines the breakdown of the serial task when a fatal error occurs in the 
 * operational function. It initializes the task information and delay, then initializes the 
 * serial state machine with dummy initialization and ready functions, along with function 
 * pointers that cause a fatal error in the operational function. The test ensures that the 
 * initial state is BUS_INIT, sets next state event, executes the state machine until it 
 * transitions to BUS_OPERATIONAL, further executes until transition to BUS_BREAKDOWN, 
 * and finally verifies the transition back to BUS_INIT upon subsequent execution.
 */
void test_srl_task_breakdown_operational_fatal_error(); /**< \test */

/**
 * @brief Test the initialization of the serial task.
 * 
 * This test case validates the initialization process of the serial task. It initializes 
 * the task information structure and delay, then verifies the correctness of the initialization 
 * values. This includes checking the ID, delay, last wake time, and status of the task.
 */
void test_srl_task_init(); /**< \test */

/**
 * @brief Test the normal execution of the serial task.
 * 
 * This test case evaluates the normal execution flow of the serial task. It initializes the 
 * task information structure and delay, then initializes the serial state machine with 
 * appropriate function pointers. The test verifies the transition from BUS_INIT to BUS_READY, 
 * stabilizes the filter by executing it multiple times, and ensures that the filter reaches 
 * the operational state without errors.
 */
void test_srl_task_normal_execution(); /**< \test */

/**
 * @brief Test error detection when the serial task is in the BUS_READY state.
 * 
 * This test case focuses on error detection during the BUS_READY state of the serial task. 
 * It initializes the task information structure and delay, then sets up the serial state machine. 
 * The test executes the state machine until it transitions to BUS_BREAKDOWN upon error detection, 
 * and verifies the subsequent transition back to BUS_READY.
 */
void test_srl_task_breakdown_ready_error(); /**< \test */

/**
 * @brief Test error detection when the serial task is in the BUS_OPERATIONAL state.
 * 
 * This test case examines error detection during the BUS_OPERATIONAL state of the serial task. 
 * It initializes the task information structure and delay, sets up the serial state machine, 
 * and ensures that the filter stabilizes. The test then simulates an error condition, causing 
 * a transition to BUS_BREAKDOWN, and verifies the subsequent transition back to BUS_OPERATIONAL.
 */
void test_srl_task_breakdown_operational_error(); /**< \test */

/**
 * @brief Test error detection of an unknown error and execution of panic handling.
 * 
 * This test case verifies the handling of an unknown error by the serial task. It initializes 
 * the task information structure and delay, sets up the serial state machine, and simulates 
 * an error condition leading to a transition to BUS_BREAKDOWN. The test ensures that panic 
 * handling is executed, indicating the detection of an unknown error.
 */
void test_srl_task_breakdown_unknown_error(); /**< \test */


#endif /* TRACE_TEST_H_ */