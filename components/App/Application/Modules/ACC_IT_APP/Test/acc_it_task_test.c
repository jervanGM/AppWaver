#include "acc_it_task_test.h"
#include "safe_memory.h"
#include "acc_it_task.h"
#include "ev_handler.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#ifndef FAKE_FUNC

void test_acc_it_task_init() {
    // Initialize the task information structure and delay.
    SAccItTaskInfo_t task_info;
    task_acc_it_init(&task_info);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(9, task_info.ID);
    TEST_ASSERT_EQUAL(ACC_IT_TASK_OK, task_info.status);
}

#endif

void acc_it_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_acc_it_task_init);
    #endif
}