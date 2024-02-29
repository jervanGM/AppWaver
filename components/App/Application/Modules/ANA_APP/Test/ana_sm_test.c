#include "ana_sm_test.h"
#include "safe_memory.h"
#include "analog_sm.h"

#ifndef FAKE_FUNC
// Test the initialization of the state machine with valid function pointers.
void test_analog_sm_init_valid_pointers() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    
    // Verify that the result is ANA_TASK_OK
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_analog_sm_init_null_pointers() {
    // Test initialization with null function pointers
    ETaskStatus_t result = analog_sm_init(NULL, NULL, NULL, NULL);

    // Verify that the result is ANA_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, ANA_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_analog_sm_init_to_operational_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);

    // Move to the next state and verify that it remains in operational
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);
}

// Test the transition from initialization to breakdown in the state machine.
void test_analog_sm_init_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Simulate a fault event and verify the transition to breakdown
    analog_sm_set_st_event(STATE_FAULT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_analog_sm_ready_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Simulate a fault event and verify the transition to breakdown
    analog_sm_set_st_event(STATE_FAULT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);
}

// Test the transition from operational to breakdown in the state machine.
void test_analog_sm_operational_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);

    // Simulate a fault event and verify the transition to breakdown
    analog_sm_set_st_event(STATE_FAULT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Simulate a previous event and verify the return to the operational state
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_analog_sm_breakdown_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Simulate a fault event and verify the transition to breakdown
    analog_sm_set_st_event(STATE_FAULT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    analog_sm_set_st_event((EStateEvent_t)10);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_analog_sm_init_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_analog_sm_ready_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Simulate a transition to an unknown state and verify that it remains in ready
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);
}

// Test the behavior of the state machine when transitioning to an unknown state from operational.
void test_analog_sm_operational_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ETaskStatus_t result = analog_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ETaskState_t state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(result, ANA_TASK_OK);
    TEST_ASSERT_EQUAL(state, ANA_INIT);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_READY);

    // Move to the next state and verify
    analog_sm_set_st_event(STATE_NEXT);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);

    // Simulate a transition to an unknown state and verify that it remains in operational
    analog_sm_set_st_event(STATE_PREV);
    analog_sm_run();
    state = analog_sm_get_state();
    TEST_ASSERT_EQUAL(state, ANA_OPERATIONAL);
}

#endif

void ana_sm_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_analog_sm_init_valid_pointers);
    RUN_TEST(test_analog_sm_init_null_pointers);
    RUN_TEST(test_analog_sm_init_to_operational_transition);
    RUN_TEST(test_analog_sm_init_to_breakdown_transition);
    RUN_TEST(test_analog_sm_ready_to_breakdown_transition);
    RUN_TEST(test_analog_sm_operational_to_breakdown_transition);
    RUN_TEST(test_analog_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_analog_sm_init_unknown_state_transition);
    RUN_TEST(test_analog_sm_ready_unknown_state_transition);
    RUN_TEST(test_analog_sm_operational_unknown_state_transition);
    #endif
}