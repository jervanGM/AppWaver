#include "ctrl_sm_test.h"
#include "safe_memory.h"
#include "control_sm.h"

// Test the initialization of the state machine with valid function pointers.
void test_control_sm_init_valid_pointers() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    
    // Verify that the result is CTRL_TASK_OK
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_control_sm_init_null_pointers() {
    // Test initialization with null function pointers
    ECtrlTaskStatus_t result = control_sm_init(NULL, NULL, NULL, NULL);

    // Verify that the result is CTRL_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, CTRL_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_control_sm_init_to_operational_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);

    // Move to the next state and verify that it remains in operational
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);
}

// Test the transition from initialization to breakdown in the state machine.
void test_control_sm_init_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Simulate a fault event and verify the transition to breakdown
    control_sm_set_st_event(CTRL_STATE_FAULT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_control_sm_ready_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);

    // Simulate a fault event and verify the transition to breakdown
    control_sm_set_st_event(CTRL_STATE_FAULT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);
}

// Test the transition from operational to breakdown in the state machine.
void test_control_sm_operational_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);

    // Simulate a fault event and verify the transition to breakdown
    control_sm_set_st_event(CTRL_STATE_FAULT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_BREAKDOWN);

    // Simulate a previous event and verify the return to the operational state
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_control_sm_breakdown_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Simulate a fault event and verify the transition to breakdown
    control_sm_set_st_event(CTRL_STATE_FAULT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    control_sm_set_st_event((ECtrlStateEvent_t)10);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_control_sm_init_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_control_sm_ready_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);

    // Simulate a transition to an unknown state and verify that it remains in ready
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);
}

// Test the behavior of the state machine when transitioning to an unknown state from operational.
void test_control_sm_operational_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    ECtrlTaskStatus_t result = control_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    ECtrlTaskState_t state = control_sm_get_state();
    TEST_ASSERT_EQUAL(result, CTRL_TASK_OK);
    TEST_ASSERT_EQUAL(state, CTRL_INIT);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_READY);

    // Move to the next state and verify
    control_sm_set_st_event(CTRL_STATE_NEXT);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);

    // Simulate a transition to an unknown state and verify that it remains in operational
    control_sm_set_st_event(CTRL_STATE_PREV);
    control_sm_run();
    state = control_sm_get_state();
    TEST_ASSERT_EQUAL(state, CTRL_OPERATIONAL);
}

void ctrl_sm_test_suite()
{
    RUN_TEST(test_control_sm_init_valid_pointers);
    RUN_TEST(test_control_sm_init_null_pointers);
    RUN_TEST(test_control_sm_init_to_operational_transition);
    RUN_TEST(test_control_sm_init_to_breakdown_transition);
    RUN_TEST(test_control_sm_ready_to_breakdown_transition);
    RUN_TEST(test_control_sm_operational_to_breakdown_transition);
    RUN_TEST(test_control_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_control_sm_init_unknown_state_transition);
    RUN_TEST(test_control_sm_ready_unknown_state_transition);
    RUN_TEST(test_control_sm_operational_unknown_state_transition);
}