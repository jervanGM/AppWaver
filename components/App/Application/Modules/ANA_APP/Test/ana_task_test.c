#include "ana_task_test.h"
#include "safe_memory.h"
#include "analog_task.h"
#include "analog_sm.h"
#include "adc_drv.h"
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
// Test the initialization of the analog task with a fatal error in initialization function.
void test_ana_task_init_fatal_error() {
    // Initialize task info and delay
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize analog state machine with task functions pointers and fake port wich cause error
    task_info.status = analog_sm_init(on_ana_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Execute state machine once and verify transition to ANA_BREAKDOWN
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Execute state machine again and verify transition back to ANA_INIT
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);
}

// Test the breakdown of the analog task with a fatal error in the ready function.
void test_ana_task_breakdown_ready_fatal_error() {
    // Initialize task info and delay
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize analog state machine with dummy initialization function and function pointers that cause fatal error in ready function
    void dummy_init(void) {}
    task_info.status = analog_sm_init(dummy_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Set next state event and execute state machine until it transitions to ANA_BREAKDOWN
    analog_sm_set_st_event(STATE_NEXT);
    while(state == ANA_READY) {
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Execute state machine again and verify transition back to ANA_INIT
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);
}

// Test the breakdown of the analog task with a fatal error in the operational function.
void test_ana_task_breakdown_operational_fatal_error() {
    // Initialize task info and delay
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize analog state machine with dummy initialization and ready functions, and function pointers that cause fatal error in operational function
    void dummy_init(void) {}
    void dummy_ready(void) {}
    task_info.status = analog_sm_init(dummy_init, dummy_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Set next state event and execute state machine until it transitions to ANA_OPERATIONAL
    analog_sm_set_st_event(STATE_NEXT);
    while(state == ANA_READY) {
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);

    // Execute state machine again and verify transition to ANA_BREAKDOWN
    while(state == ANA_OPERATIONAL) {
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Execute state machine again and verify transition back to ANA_INIT
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);
}
#endif

#ifndef FAKE_FUNC
// Test the initialization of the analog task.
void test_ana_task_init() {
    // Initialize the task information structure and delay.
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(0, task_info.ID);
    TEST_ASSERT_EQUAL(delay, task_info.delay);
    TEST_ASSERT_EQUAL(0, task_info.LastWakeTime);
    TEST_ASSERT_EQUAL(ANA_TASK_OK, task_info.status);
}

// Test the normal execution of the analog task.
void test_ana_task_normal_execution() {
    // Initialize the task information structure and delay.
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize the analog state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = analog_sm_init(on_ana_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT.
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Execute the state machine and verify the transition to ANA_READY.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);
    
    // Execute the filter 256 times to stabilize it and clear any warnings.
    for(int i = 0; i < 256; i++) {
        set_adc_value(50);
        analog_sm_run();
        state = analog_sm_get_state();
    }

    // Verify that the filter is ready and there are no errors.
    for(int i = 0; i < 256; i++) {
        set_adc_value(50);
        analog_sm_run();
        state = analog_sm_get_state();
        TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);
    }
}

// Test error detection when the analog task is in the ANA_READY state.
void test_ana_task_breakdown_ready_error() {
    // Initialize the task information structure and delay.
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize the analog state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = analog_sm_init(on_ana_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT.
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Execute the state machine and verify the transition to ANA_READY.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Execute the state machine until a transition to ANA_BREAKDOWN occurs.
    while(state == ANA_READY) {
        set_adc_value(UINT32_MAX);
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Execute the state machine and verify the transition back to ANA_READY.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);
}

// Test error detection when the analog task is in the ANA_OPERATIONAL state.
void test_ana_task_breakdown_operational_error() {
    // Initialize the task information structure and delay.
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize the analog state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = analog_sm_init(on_ana_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT.
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Execute the state machine and verify the transition to ANA_READY.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);
    
    // Execute the filter 256 times to stabilize it and clear any warnings.
    while(state == ANA_READY || state == ANA_BREAKDOWN) {
        set_adc_value(50);
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);

    // Execute the state machine until a transition to ANA_BREAKDOWN occurs.
    while(state == ANA_OPERATIONAL) {
        set_adc_value(UINT32_MAX);
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Execute the state machine and verify the transition back to ANA_OPERATIONAL.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);
}

// Test error detection of an unknown error and execution of panic handling.
void test_ana_task_breakdown_unknown_error() {
    // Initialize the task information structure and delay.
    SAnaTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_analog_init(&task_info, &delay);
    
    // Initialize the analog state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = analog_sm_init(on_ana_init, on_ana_ready, on_ana_execute, on_ana_breakdown);
    
    // Verify that the initial state is ANA_INIT.
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Execute the state machine and verify the transition to ANA_READY.
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Execute the state machine until a transition to ANA_BREAKDOWN occurs.
    while(state == ANA_READY) {
        set_adc_value(UINT32_MAX);
        analog_sm_run();
        state = analog_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Reset the panic state and store an error in a slot.
    reset_panic();
    store_error_in_slot(0, 0);
    analog_sm_run();

    // Verify that the panic handling function is executed.
    TEST_ASSERT(is_panic_executed() == true);
}

#endif

void ana_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_ana_task_init);
    RUN_TEST(test_ana_task_normal_execution);
    RUN_TEST(test_ana_task_breakdown_ready_error);
    RUN_TEST(test_ana_task_breakdown_operational_error);
    RUN_TEST(test_ana_task_breakdown_unknown_error);
    #endif
    #ifdef FAKE_FUNC
    RUN_TEST(test_ana_task_init_fatal_error);
    RUN_TEST(test_ana_task_breakdown_ready_fatal_error);
    RUN_TEST(test_ana_task_breakdown_operational_fatal_error);
    #endif
}