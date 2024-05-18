#include "bus_app_test.h"
#include "safe_memory.h"
#include "bus_app.h"
#include <string.h>

#ifndef FAKE_FUNC
void test_bus_app_check_mayor_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, -120);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MAYOR_FAULT);
}

void test_bus_app_check_minor_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, -10);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MINOR_FAULT);
}

void test_bus_app_check_no_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, 10);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_bus_app_check_lower_minor_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_bus_app_check_upper_minor_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MAYOR_FAULT);
}

void test_bus_app_check_lower_major_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_bus_app_check_upper_major_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, INT8_MAX);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_bus_app_process_data()
{
    SAxisDataBuffer_t axis_buffer = {0};
    SBufTime_t time_buff = {0};
    STemp_t temp = {0};
    SMoist_t moist = {0};
    uint8_t raw_data[RAW_DATA_BYTES] = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};
    for(int i = 0;i< BUFFER_SIZE;i++)
    {
        process_data(raw_data, RAW_DATA_BYTES);
    }
    
    axis_buffer = get_axis_data_buffer();

    time_buff = get_axis_buffer_time();

    temp = get_buffer_average_temp();

    moist = get_buffer_average_moist();

    TEST_ASSERT_EQUAL(axis_buffer.ready,true);
    TEST_ASSERT_EQUAL(axis_buffer.x[0], 5140*ACC_AXIS_CONV_FACTOR);
    TEST_ASSERT_EQUAL(axis_buffer.y[0], 5140*ACC_AXIS_CONV_FACTOR);
    TEST_ASSERT_EQUAL(axis_buffer.z[0], 5140*ACC_AXIS_CONV_FACTOR);
    TEST_ASSERT_EQUAL(temp.temperature, 5140*TEMP_CONV_FACTOR);
    TEST_ASSERT_EQUAL(moist.moist, 5140*MOIST_CONV_FACTOR);
}

void test_bus_app_process_data_error()
{
    SAxisDataBuffer_t axis_buffer = {0};
    SBufTime_t time_buff = {0};
    STemp_t temp = {0};
    SMoist_t moist = {0};
    uint8_t raw_data[RAW_DATA_BYTES] = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};
    for(int i = 0;i< BUFFER_SIZE;i++)
    {
        process_data(NULL, RAW_DATA_BYTES);
    }
    
    axis_buffer = get_axis_data_buffer();

    time_buff = get_axis_buffer_time();

    temp = get_buffer_average_temp();

    moist = get_buffer_average_moist();

    int8_t error = read_error_from_slot(BUS_ERROR_SLOT);

    TEST_ASSERT_EQUAL(error,BUS_APP_BUFFER_EMPTY);
}


#endif

void bus_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_bus_app_check_mayor_faults);
    RUN_TEST(test_bus_app_check_minor_faults);
    RUN_TEST(test_bus_app_check_no_faults);
    RUN_TEST(test_bus_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_bus_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_bus_app_check_lower_major_fault_boundary);
    RUN_TEST(test_bus_app_check_upper_major_fault_boundary);
    RUN_TEST(test_bus_app_process_data);
    RUN_TEST(test_bus_app_process_data_error);
    #endif
}