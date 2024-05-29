#include "bus_sm_test.h"
#include "safe_memory.h"
#include "bus_sm.h"

#ifndef FAKE_FUNC
    // Define dummy functions
    void dummy_init(void) {}
    void dummy_ready(void) {}
    void dummy_operational(void) {}
    void dummy_breakdown(void) {}
// Test the initialization of the state machine with valid function pointers.
void test_bus_sm_init_valid_pointers() {
    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    
    // Verify that the result is BUS_TASK_OK
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
}

// Test the initialization of the state machine with null function pointers.
void test_bus_sm_init_null_pointers() {
    // Test initialization with null function pointers
    EBusTaskStatus_t result = bus_sm_init(NULL, NULL, NULL, NULL);

    // Verify that the result is BUS_TASK_SM_INIT_FAIL
    TEST_ASSERT_EQUAL(result, BUS_TASK_SM_INIT_FAIL);
}

// Test the transition from initialization to operational in the state machine.
void test_bus_sm_init_to_operational_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

    // Move to the next state and verify that it remains in operational
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);
}

// Test the transition from initialization to breakdown in the state machine.
void test_bus_sm_init_to_breakdown_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Simulate a fault event and verify the transition to breakdown
    bus_sm_set_st_event(BUS_STATE_FAULT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Simulate a previous event and verify the return to the initial state
    bus_sm_set_st_event(BUS_STATE_PREV);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);
}

// Test the transition from ready to breakdown in the state machine.
void test_bus_sm_ready_to_breakdown_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Simulate a fault event and verify the transition to breakdown
    bus_sm_set_st_event(BUS_STATE_FAULT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Simulate a previous event and verify the return to the ready state
    bus_sm_set_st_event(BUS_STATE_PREV);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);
}

// Test the transition from operational to breakdown in the state machine.
void test_bus_sm_operational_to_breakdown_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

    // Simulate a fault event and verify the transition to breakdown
    bus_sm_set_st_event(BUS_STATE_FAULT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Simulate a previous event and verify the return to the operational state
    bus_sm_set_st_event(BUS_STATE_PREV);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);
}

// Test the behavior of the state machine when transitioning to an unknown state from breakdown.
void test_bus_sm_breakdown_unknown_state_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Simulate a fault event and verify the transition to breakdown
    bus_sm_set_st_event(BUS_STATE_FAULT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Simulate a transition to an unknown state and verify that it remains in breakdown
    bus_sm_set_st_event((EBusStateEvent_t)10);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);
}

// Test the behavior of the state machine when transitioning to an unknown state from initialization.
void test_bus_sm_init_unknown_state_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Simulate a transition to an unknown state and verify that it remains in initialization
    bus_sm_set_st_event((EBusStateEvent_t)10);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);
}

// Test the behavior of the state machine when transitioning to an unknown state from ready.
void test_bus_sm_ready_unknown_state_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Simulate a transition to an unknown state and verify that it remains in ready
    bus_sm_set_st_event((EBusStateEvent_t)10);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);
}

// Test the behavior of the state machine when transitioning to an unknown state from operational.
void test_bus_sm_operational_unknown_state_transition() {

    // Test initialization with valid function pointers
    EBusTaskStatus_t result = bus_sm_init(dummy_init, dummy_ready, dummy_operational, dummy_breakdown);
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(result, BUS_TASK_OK);
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Move to the next state and verify
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

    // Simulate a transition to an unknown state and verify that it remains in operational
    bus_sm_set_st_event((EBusStateEvent_t)10);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);
}

#endif

void bus_sm_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_bus_sm_init_valid_pointers);
    RUN_TEST(test_bus_sm_init_null_pointers);
    RUN_TEST(test_bus_sm_init_to_operational_transition);
    RUN_TEST(test_bus_sm_init_to_breakdown_transition);
    RUN_TEST(test_bus_sm_ready_to_breakdown_transition);
    RUN_TEST(test_bus_sm_operational_to_breakdown_transition);
    RUN_TEST(test_bus_sm_breakdown_unknown_state_transition);
    RUN_TEST(test_bus_sm_init_unknown_state_transition);
    RUN_TEST(test_bus_sm_ready_unknown_state_transition);
    RUN_TEST(test_bus_sm_operational_unknown_state_transition);
    #endif
}