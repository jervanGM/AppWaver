#include "mem_sm_test.h"
#include "safe_memory.h"
#include "mem_sm.h"

#ifndef FAKE_FUNC
// Test the initialization of the state machine with valid function pointers.
void test_mem_sm_init_valid_pointers() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    
    // Verify that the result is MEM_TASK_OK
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_mem_sm_init_null_pointers() {
    // Test initialization with null function pointers
    EMemTaskStatus_t result = mem_sm_init(NULL, NULL, NULL);

    // Verify that the result is MEM_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, MEM_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_mem_sm_init_to_operational_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Move to the next state and verify
    mem_sm_set_st_event(MEM_STATE_NEXT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);
}


// Test the transition from initialization to breakdown in the state machine.
void test_mem_sm_init_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Simulate a fault event and verify the transition to breakdown
    mem_sm_set_st_event(MEM_STATE_FAULT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    mem_sm_set_st_event(MEM_STATE_PREV);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_mem_sm_operational_to_breakdown_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Move to the next state and verify
    mem_sm_set_st_event(MEM_STATE_NEXT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);

    // Simulate a fault event and verify the transition to breakdown
    mem_sm_set_st_event(MEM_STATE_FAULT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    mem_sm_set_st_event(MEM_STATE_PREV);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_mem_sm_breakdown_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Simulate a fault event and verify the transition to breakdown
    mem_sm_set_st_event(MEM_STATE_FAULT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    mem_sm_set_st_event((EMemStateEvent_t)10);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_mem_sm_init_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    mem_sm_set_st_event(MEM_STATE_PREV);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_mem_sm_operational_unknown_state_transition() {
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}

    // Test initialization with valid function pointers
    EMemTaskStatus_t result = mem_sm_init(dummy_init, dummy_operational, dummy_breakdown);
    EMemTaskState_t state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(result, MEM_TASK_OK);
    TEST_ASSERT_EQUAL(state, MEM_INIT);

    // Move to the next state and verify
    mem_sm_set_st_event(MEM_STATE_NEXT);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);

    // Simulate a transition to an unknown state and verify that it remains in ready
    mem_sm_set_st_event(MEM_STATE_PREV);
    mem_sm_run();
    state = mem_sm_get_state();
    TEST_ASSERT_EQUAL(state, MEM_OPERATIONAL);
}

#endif

void mem_sm_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_mem_sm_init_valid_pointers);
    RUN_TEST(test_mem_sm_init_null_pointers);
    RUN_TEST(test_mem_sm_init_to_operational_transition);
    RUN_TEST(test_mem_sm_init_to_breakdown_transition);
    RUN_TEST(test_mem_sm_operational_to_breakdown_transition);
    RUN_TEST(test_mem_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_mem_sm_init_unknown_state_transition);
    RUN_TEST(test_mem_sm_operational_unknown_state_transition);
    #endif
}