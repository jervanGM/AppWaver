#include "ind_task_test.h"
#include "safe_memory.h"
#include "ind_task.h"
#include "ind_codec.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#ifndef FAKE_FUNC

void test_ind_task_init() {
    // Initialize the task information structure and delay.
    SIndTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_indicator_init(&task_info, &delay);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(4, task_info.ID);
    TEST_ASSERT_EQUAL(delay, task_info.delay);
    TEST_ASSERT_EQUAL(0, task_info.LastWakeTime);
    TEST_ASSERT_EQUAL(IND_TASK_OK, task_info.status);
}

#endif

void ind_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_ind_task_init);
    #endif
}