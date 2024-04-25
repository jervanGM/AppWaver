#include "pw_sm_test.h"
#include "safe_memory.h"
#include "pw_sm.h"

#ifndef FAKE_FUNC
// Test the initialization of the state machine with valid function pointers.
void test_pw_sm_init_valid_pointers() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    
    // Verify that the result is PW_TASK_OK
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_pw_sm_init_null_pointers() {
    // Test initialization with null function pointers
    EPwTaskStatus_t result = pw_sm_init(NULL, NULL, NULL, NULL, NULL);

    // Verify that the result is PW_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, PW_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_pw_sm_init_to_full_pw_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);
}

// Test the transition from initialization to operational in the state machine.
void test_pw_sm_full_pw_to_low_pw_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);
}

// Test the transition from initialization to operational in the state machine.
void test_pw_sm_low_pw_to_full_pw_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);
}

// Test the transition from initialization to breakdown in the state machine.
void test_pw_sm_init_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_FAULT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_pw_sm_full_pw_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_FAULT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);
}

// Test the transition from operational to breakdown in the state machine.
void test_pw_sm_low_power_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_FAULT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);

    // Simulate a previous event and verify the return to the operational state
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);
}

// Test the transition from initialization to breakdown in the state machine.
void test_pw_sm_power_off_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_OFF);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_FAULT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);
}

// Test the transition from initialization to breakdown in the state machine.
void test_pw_sm_init_to_power_off_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_OFF);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_pw_sm_full_pw_to_power_off_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_OFF);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);
}

// Test the transition from operational to breakdown in the state machine.
void test_pw_sm_low_power_to_power_off_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_OFF);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_pw_sm_breakdown_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Simulate a fault event and verify the transition to breakdown
    pw_sm_set_st_event(PW_STATE_FAULT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    pw_sm_set_st_event((EPwStateEvent_t)10);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_pw_sm_init_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_pw_sm_full_pw_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Simulate a transition to an unknown state and verify that it remains in ready
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);
}

// Test the behavior of the state machine when transitioning to an unknown state from operational.
void test_pw_sm_low_pw_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);

    // Simulate a transition to an unknown state and verify that it remains in operational
    pw_sm_set_st_event((EPwStateEvent_t)15);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_LOW);
}

void test_pw_sm_pw_off_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_full_pw(void) {}
    void dummy_low_pw(void) {}
    void dummy_power_off(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EPwTaskStatus_t result = pw_sm_init(dummy_init, dummy_full_pw, dummy_low_pw, dummy_power_off, dummy_breakdown);
    EPwTaskState_t state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(result, PW_TASK_OK);
    TEST_ASSERT_EQUAL(state, PW_INIT);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_NEXT);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_FULL);

    // Move to the next state and verify
    pw_sm_set_st_event(PW_STATE_OFF);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);

    // Simulate a transition to an unknown state and verify that it remains in operational
    pw_sm_set_st_event(PW_STATE_PREV);
    pw_sm_run();
    state = pw_sm_get_state();
    TEST_ASSERT_EQUAL(state, PW_OFF);
}

#endif

void pw_sm_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_pw_sm_init_valid_pointers);
    RUN_TEST(test_pw_sm_init_null_pointers);
    RUN_TEST(test_pw_sm_init_to_full_pw_transition);
    RUN_TEST(test_pw_sm_init_to_breakdown_transition);
    RUN_TEST(test_pw_sm_full_pw_to_breakdown_transition);
    RUN_TEST(test_pw_sm_low_power_to_breakdown_transition);
    RUN_TEST(test_pw_sm_power_off_to_breakdown_transition);
    RUN_TEST(test_pw_sm_init_to_power_off_transition);
    RUN_TEST(test_pw_sm_full_pw_to_power_off_transition);
    RUN_TEST(test_pw_sm_low_power_to_power_off_transition);
    RUN_TEST(test_pw_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_pw_sm_init_unknown_state_transition);
    RUN_TEST(test_pw_sm_full_pw_unknown_state_transition);
    RUN_TEST(test_pw_sm_low_pw_unknown_state_transition);
    RUN_TEST(test_pw_sm_pw_off_unknown_state_transition);
    RUN_TEST(test_pw_sm_full_pw_to_low_pw_transition);
    RUN_TEST(test_pw_sm_low_pw_to_full_pw_transition);
    #endif
}