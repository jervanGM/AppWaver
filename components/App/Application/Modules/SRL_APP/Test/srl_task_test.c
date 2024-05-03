#include "srl_task_test.h"
#include "safe_memory.h"
#include "serial_task.h"
#include "serial_sm.h"
#include "usb_drv.h"
#include "assert_panic.h"
#include "panic_mock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//Execute functions with a fake hal_port defined on dsp_test
#ifdef FAKE_FUNC
// Test the initialization of the serial task with a fatal error in initialization function.
void test_srl_task_init_fatal_error() {
    // Initialize task info and delay
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize serial state machine with task functions pointers and fake port wich cause error
    task_info.status = serial_sm_init(on_srl_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Execute state machine once and verify transition to SRL_BREAKDOWN
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Execute state machine again and verify transition back to SRL_INIT
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);
}

void dummy_init(void) {}
void dummy_ready(void) {}

// Test the breakdown of the serial task with a fatal error in the ready function.
void test_srl_task_breakdown_ready_fatal_error() {
    // Initialize task info and delay
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize serial state machine with dummy initialization function and function pointers that cause fatal error in ready function
    
    task_info.status = serial_sm_init(dummy_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Set next state event and execute state machine until it transitions to SRL_BREAKDOWN
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // serial_sm_run();
    // state = serial_sm_get_state();
    // TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // // Execute state machine again and verify transition back to SRL_INIT
    // serial_sm_run();
    // state = serial_sm_get_state();
    // TEST_ASSERT_EQUAL(state, SRL_INIT);
}

// Test the breakdown of the serial task with a fatal error in the operational function.
void test_srl_task_breakdown_operational_fatal_error() {
    // Initialize task info and delay
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize serial state machine with dummy initialization and ready functions, and function pointers that cause fatal error in operational function
    task_info.status = serial_sm_init(dummy_init, dummy_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Set next state event and execute state machine until it transitions to SRL_OPERATIONAL
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    // Execute state machine again and verify transition to SRL_BREAKDOWN
    while(state == SRL_OPERATIONAL) {
        serial_sm_run();
        state = serial_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Execute state machine again and verify transition back to SRL_INIT
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);
}
#endif

#ifndef FAKE_FUNC
// Test the initialization of the serial task.
void test_srl_task_init() {
    // Initialize the task information structure and delay.
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(7, task_info.ID);
    TEST_ASSERT_EQUAL(delay, task_info.delay);
    TEST_ASSERT_EQUAL(0, task_info.LastWakeTime);
    TEST_ASSERT_EQUAL(SRL_TASK_OK, task_info.status);
}

// Test the normal execution of the serial task.
void test_srl_task_normal_execution() {
    // Initialize the task information structure and delay.
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize the serial state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = serial_sm_init(on_srl_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT.
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Execute the state machine and verify the transition to SRL_READY.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);
    
    // Execute the filter 256 times to stabilize it and clear any warnings.
    set_serial_connection(true);
    set_serial_msg("/system_off/");
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    set_serial_connection(false);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    set_serial_connection(true);
    set_serial_msg("/system_reset/");
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);
}

// Test error detection when the serial task is in the SRL_READY state.
void test_srl_task_breakdown_ready_error() {
    // Initialize the task information structure and delay.
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize the serial state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = serial_sm_init(on_srl_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT.
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Execute the state machine and verify the transition to SRL_READY.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Execute the state machine until a transition to SRL_BREAKDOWN occurs.
    store_error_in_slot(SERIAL_ERROR_SLOT,-12);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Execute the state machine and verify the transition back to SRL_READY.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);
}

// Test error detection when the serial task is in the SRL_OPERATIONAL state.
void test_srl_task_breakdown_operational_error() {
    // Initialize the task information structure and delay.
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize the serial state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = serial_sm_init(on_srl_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT.
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Execute the state machine and verify the transition to SRL_READY.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);
    
    set_serial_connection(true);
    set_serial_msg("/system_off/");
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    char overflow_cmd[1024 + 1];
    memset(overflow_cmd, 'A', 1024);
    overflow_cmd[1024] = '\0';
    set_serial_msg(overflow_cmd);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Execute the state machine and verify the transition back to SRL_OPERATIONAL.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);
}

// Test error detection of an unknown error and execution of panic handling.
void test_srl_task_breakdown_unknown_error() {
    // Initialize the task information structure and delay.
    SSrlTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_serial_init(&task_info, &delay);
    
    // Initialize the serial state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = serial_sm_init(on_srl_init, on_srl_ready, on_srl_execute, on_srl_breakdown);
    
    // Verify that the initial state is SRL_INIT.
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Execute the state machine and verify the transition to SRL_READY.
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Execute the state machine until a transition to SRL_BREAKDOWN occurs.
    store_error_in_slot(SERIAL_ERROR_SLOT,-12);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Reset the panic state and store an error in a slot.
    reset_panic();
    store_error_in_slot(SERIAL_ERROR_SLOT, 0);
    serial_sm_run();

    // Verify that the panic handling function is executed.
    TEST_ASSERT(is_panic_executed() == true);
}

#endif

void srl_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_srl_task_init);
    RUN_TEST(test_srl_task_normal_execution);
    RUN_TEST(test_srl_task_breakdown_ready_error);
    RUN_TEST(test_srl_task_breakdown_operational_error);
    RUN_TEST(test_srl_task_breakdown_unknown_error);
    #endif
    #ifdef FAKE_FUNC
    RUN_TEST(test_srl_task_init_fatal_error);
    RUN_TEST(test_srl_task_breakdown_ready_fatal_error);
    RUN_TEST(test_srl_task_breakdown_operational_fatal_error);
    #endif
}