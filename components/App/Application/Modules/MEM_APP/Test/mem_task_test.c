#include "mem_task_test.h"
#include "safe_memory.h"
#include "mem_task.h"
#include "mem_sm.h"
#include "mem_drv.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#ifndef FAKE_FUNC

void test_mem_task_init() {
    // Initialize the task information structure and delay.
    SMemTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_mem_init(&task_info, &delay);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(6, task_info.ID);
    TEST_ASSERT_EQUAL(delay, task_info.delay);
    TEST_ASSERT_EQUAL(0, task_info.LastWakeTime);
    TEST_ASSERT_EQUAL(MEM_TASK_OK, task_info.status);
}

void test_mem_task_normal_execution() {
    // Initialize the task information structure and delay.
    SMemTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_mem_init(&task_info, &delay);
    // Initialize the analog state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = mem_sm_init(on_mem_init, on_mem_execute, on_mem_breakdown);
    store_error_in_slot(EXT_MEM_ERROR_SLOT,0);
    // Verify that the initial state is ANA_INIT.
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_INIT);
    store_error_in_slot(EXT_MEM_ERROR_SLOT,0);
    remove(".\\sdcard\\device_info.txt");
    // Execute the state machine and verify the transition to ANA_READY.
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);
    
    // Execute the filter 256 times to stabilize it and clear any warnings.

    STime_t start_t = {0};
    STime_t end_t;
    uint32_t data[128];
    SErrorInfo_t alarm;
    SSystemStatus_t status;
    SEnvData_t env_data;
    SPowerData_t power_data;
    SAxisData_t axix_buf[DATA_BUFFER_SIZE];
    end_t.sec = 13;
    for(int i=0; i<128;i++)
    {
        data[i] = rand() % 200;
    }

    ctrl_mem_send(alarm,status,data,env_data,power_data,axix_buf,
                    SYS_BUFFER_MODE,SYS_BUFFER_MODE,start_t,end_t,
                    start_t);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);
    

}

#endif

void mem_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_mem_task_init);
    RUN_TEST(test_mem_task_normal_execution);
    #endif
}