#ifndef MEM_TASK_TEST_H_
#define MEM_TASK_TEST_H_

#include "test_suite.h"

/**
 * @brief Test function for initializing the memory task information structure.
 *
 * This test function initializes the memory task information structure and verifies
 * that the initialization values are correct.
 */
void test_mem_task_init(); /**< \test */

/**
 * @brief Test function for normal execution of the memory task.
 *
 * This test function initializes the memory task, simulates the state machine execution,
 * and verifies the correct transition and execution of the task.
 */
void test_mem_task_normal_execution(); /**< \test */

#endif /* MEM_TASK_TEST_H_ */
