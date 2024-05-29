#include "bus_task_test.h"
#include "safe_memory.h"
#include "bus_task.h"
#include "bus_sm.h"
#include "i2c_drv.h"
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
// Test the initialization of the bus task with a fatal error in initialization function.
void test_bus_task_init_fatal_error() {
    // Initialize task info and delay
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_bus_init(&task_info, &delay);
    
    // Initialize bus state machine with task functions pointers and fake port wich cause error
    task_info.status = bus_sm_init(on_bus_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Execute state machine once and verify transition to BUS_BREAKDOWN
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Execute state machine again and verify transition back to BUS_INIT
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);
}

void dummy_init(void) {}
void dummy_ready(void) {}

// Test the breakdown of the bus task with a fatal error in the ready function.
void test_bus_task_breakdown_ready_fatal_error() {
    // Initialize task info and delay
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_bus_init(&task_info, &delay);
    
    // Initialize bus state machine with dummy initialization function and function pointers that cause fatal error in ready function
    
    task_info.status = bus_sm_init(dummy_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Set next state event and execute state machine until it transitions to BUS_BREAKDOWN
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // bus_sm_run();
    // state = bus_sm_get_state();
    // TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // // Execute state machine again and verify transition back to BUS_INIT
    // bus_sm_run();
    // state = bus_sm_get_state();
    // TEST_ASSERT_EQUAL(state, BUS_INIT);
}

// Test the breakdown of the bus task with a fatal error in the operational function.
void test_bus_task_breakdown_operational_fatal_error() {
    // Initialize task info and delay
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_bus_init(&task_info, &delay);
    
    // Initialize bus state machine with dummy initialization and ready functions, and function pointers that cause fatal error in operational function
    task_info.status = bus_sm_init(dummy_init, dummy_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Set next state event and execute state machine until it transitions to BUS_OPERATIONAL
    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    bus_sm_set_st_event(BUS_STATE_NEXT);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

    // Execute state machine again and verify transition to BUS_BREAKDOWN
    while(state == BUS_OPERATIONAL) {
        bus_sm_run();
        state = bus_sm_get_state();
    }
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // // Execute state machine again and verify transition back to BUS_INIT
    // bus_sm_run();
    // state = bus_sm_get_state();
    // TEST_ASSERT_EQUAL(state, BUS_INIT);
}
#endif

#ifndef FAKE_FUNC

static init_registers()
{
    store_error_in_slot(BUS_ERROR_SLOT,0); 
    set_errors(0, 0, 0, 0);
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            set_read_data(i,j,0);
        }
    }
}
// Test the initialization of the bus task.
void test_bus_task_init() {
    // Initialize the task information structure and delay.
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    task_bus_init(&task_info, &delay);
    
    // Verify that the initialization values are correct.
    TEST_ASSERT_EQUAL(8, task_info.ID);
    TEST_ASSERT_EQUAL(delay, task_info.delay);
    TEST_ASSERT_EQUAL(0, task_info.LastWakeTime);
    TEST_ASSERT_EQUAL(BUS_TASK_OK, task_info.status);
}

// Test the normal execution of the bus task.
void test_bus_task_normal_execution() {
    // Initialize the task information structure and delay.
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    init_registers();
    task_bus_init(&task_info, &delay);
    
    // Initialize the bus state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = bus_sm_init(on_bus_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT.
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Execute the state machine and verify the transition to BUS_READY.
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

}

// Test error detection when the bus task is in the BUS_READY state.
void test_bus_task_breakdown_ready_error() {
    // Initialize the task information structure and delay.
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    init_registers();
    task_bus_init(&task_info, &delay);
    
    // Initialize the bus state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = bus_sm_init(on_bus_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT.
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Execute the state machine and verify the transition to BUS_READY.
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Execute the state machine until a transition to BUS_BREAKDOWN occurs.
    //store_error_in_slot(BUS_ERROR_SLOT,-12);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Execute the state machine and verify the transition back to BUS_READY.
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);
}

// Test error detection when the bus task is in the BUS_OPERATIONAL state.
void test_bus_task_breakdown_operational_error() {
    // Initialize the task information structure and delay.
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    init_registers();
    task_bus_init(&task_info, &delay);
    
    // Initialize the bus state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = bus_sm_init(on_bus_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT.
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Execute the state machine and verify the transition to BUS_READY.
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+1,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+2,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+3,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+4,20);
    set_read_data(SHT4x_DEFAULT_ADDR,SHT4x_READSERIAL+5,20);
    set_read_data(LIS3DH_DEFAULT_ADDR,LIS3DH_WHO_AM_I,20);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    bus_sm_run();
    set_errors(0, 0, 0, -1);
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);

    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Execute the state machine and verify the transition back to BUS_READY.
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_OPERATIONAL);
    
}

// Test error detection of an unknown error and execution of panic handling.
void test_bus_task_breakdown_unknown_error() {
    // Initialize the task information structure and delay.
    SBusTaskInfo_t task_info;
    uint32_t delay = 1000;
    init_registers();
    task_bus_init(&task_info, &delay);
    
    // Initialize the bus state machine with initialization, ready, execution, and breakdown functions.
    task_info.status = bus_sm_init(on_bus_init, on_bus_ready, on_bus_execute, on_bus_breakdown);
    
    // Verify that the initial state is BUS_INIT.
    EBusTaskState_t state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_INIT);

    // Execute the state machine and verify the transition to BUS_READY.
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_READY);

    // Execute the state machine until a transition to BUS_BREAKDOWN occurs.
    store_error_in_slot(BUS_ERROR_SLOT,-12);
    bus_sm_run();
    state = bus_sm_get_state();
    TEST_ASSERT_EQUAL(state, BUS_BREAKDOWN);

    // Reset the panic state and store an error in a slot.
    reset_panic();
    store_error_in_slot(BUS_ERROR_SLOT, 0);
    bus_sm_run();

    // Verify that the panic handling function is executed.
    TEST_ASSERT(is_panic_executed() == true);
}

#endif

void bus_task_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_bus_task_init);
    RUN_TEST(test_bus_task_normal_execution);
    RUN_TEST(test_bus_task_breakdown_ready_error);
    RUN_TEST(test_bus_task_breakdown_operational_error);
    RUN_TEST(test_bus_task_breakdown_unknown_error);
    #endif
    #ifdef FAKE_FUNC
    RUN_TEST(test_bus_task_init_fatal_error);
    RUN_TEST(test_bus_task_breakdown_ready_fatal_error);
    RUN_TEST(test_bus_task_breakdown_operational_fatal_error);
    #endif
}