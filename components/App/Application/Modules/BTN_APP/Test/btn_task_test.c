#include "btn_task_test.h"
#include "safe_memory.h"
#include "btn_task.h"
#include "cmd_handler.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#ifndef FAKE_FUNC

void test_btn_task_init() {
    // Initialize the task information structure and delay.
    SBtnTaskInfo_t task_info;
    task_btn_init(&task_info);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(0, task_info.ID);
    TEST_ASSERT_EQUAL(BTN_TASK_OK, task_info.status);
}

#endif

void btn_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_btn_task_init);
    #endif
}