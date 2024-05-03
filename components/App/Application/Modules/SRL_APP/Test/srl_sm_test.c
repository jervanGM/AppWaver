#include "srl_sm_test.h"
#include "safe_memory.h"
#include "serial_sm.h"

#ifndef FAKE_FUNC
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}
// Test the initialization of the state machine with valid function pointers.
void test_serial_sm_init_valid_pointers() {
    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    
    // Verify that the result is SRL_TASK_OK
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_serial_sm_init_null_pointers() {
    // Test initialization with null function pointers
    ESrlTaskStatus_t result = serial_sm_init(NULL, NULL, NULL, NULL);

    // Verify that the result is SRL_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, SRL_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_serial_sm_init_to_operational_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    // Move to the next state and verify that it remains in operational
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    serial_sm_set_st_event(SRL_STATE_PREV);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);
}

// Test the transition from initialization to breakdown in the state machine.
void test_serial_sm_init_to_breakdown_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Simulate a fault event and verify the transition to breakdown
    serial_sm_set_st_event(SRL_STATE_FAULT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    serial_sm_set_st_event(SRL_STATE_PREV);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_serial_sm_ready_to_breakdown_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Simulate a fault event and verify the transition to breakdown
    serial_sm_set_st_event(SRL_STATE_FAULT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    serial_sm_set_st_event(SRL_STATE_PREV);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);
}

// Test the transition from operational to breakdown in the state machine.
void test_serial_sm_operational_to_breakdown_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    // Simulate a fault event and verify the transition to breakdown
    serial_sm_set_st_event(SRL_STATE_FAULT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the operational state
    serial_sm_set_st_event(SRL_STATE_PREV);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_serial_sm_breakdown_unknown_state_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Simulate a fault event and verify the transition to breakdown
    serial_sm_set_st_event(SRL_STATE_FAULT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    serial_sm_set_st_event((ESrlStateEvent_t)10);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_serial_sm_init_unknown_state_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    serial_sm_set_st_event((ESrlStateEvent_t)10);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_serial_sm_ready_unknown_state_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Simulate a transition to an unknown state and verify that it remains in ready
    serial_sm_set_st_event((ESrlStateEvent_t)10);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);
}

// Test the behavior of the state machine when transitioning to an unknown state from operational.
void test_serial_sm_operational_unknown_state_transition() {

    // Test initialization with valid function pointers
    ESrlTaskStatus_t result = serial_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ESrlTaskState_t state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(result, SRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, SRL_INIT);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_READY);

    // Move to the next state and verify
    serial_sm_set_st_event(SRL_STATE_NEXT);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);

    // Simulate a transition to an unknown state and verify that it remains in operational
    serial_sm_set_st_event((ESrlStateEvent_t)10);
    serial_sm_run();
    state = serial_sm_get_state();
    TEST_ASSERT_EQUAL(state, SRL_OPERATIONAL);
}

#endif

void srl_sm_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_serial_sm_init_valid_pointers);
    RUN_TEST(test_serial_sm_init_null_pointers);
    RUN_TEST(test_serial_sm_init_to_operational_transition);
    RUN_TEST(test_serial_sm_init_to_breakdown_transition);
    RUN_TEST(test_serial_sm_ready_to_breakdown_transition);
    RUN_TEST(test_serial_sm_operational_to_breakdown_transition);
    RUN_TEST(test_serial_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_serial_sm_init_unknown_state_transition);
    RUN_TEST(test_serial_sm_ready_unknown_state_transition);
    RUN_TEST(test_serial_sm_operational_unknown_state_transition);
    #endif
}