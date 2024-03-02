#include "ana_app_test.h"
#include "safe_memory.h"
#include "analog_app.h"

#ifndef FAKE_FUNC
void test_analog_app_check_mayor_faults() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, -120);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_MAYOR_FAULT);
}

void test_analog_app_check_minor_faults() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, -10);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_MINOR_FAULT);
}

void test_analog_app_check_no_faults() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, 10);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_TASK_OK);
}

void test_analog_app_check_lower_minor_fault_boundary() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_TASK_OK);
}

void test_analog_app_check_upper_minor_fault_boundary() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_MAYOR_FAULT);
}

void test_analog_app_check_lower_major_fault_boundary() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_TASK_OK);
}

void test_analog_app_check_upper_major_fault_boundary() {
    EAnaTaskStatus_t fault;
    store_error_in_slot(ANALOGIC_ERROR_SLOT, INT8_MAX);
    fault = analog_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ANA_TASK_OK);
}

#endif

void ana_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_analog_app_check_mayor_faults);
    RUN_TEST(test_analog_app_check_minor_faults);
    RUN_TEST(test_analog_app_check_no_faults);
    RUN_TEST(test_analog_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_analog_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_analog_app_check_lower_major_fault_boundary);
    RUN_TEST(test_analog_app_check_upper_major_fault_boundary);
    #endif
}