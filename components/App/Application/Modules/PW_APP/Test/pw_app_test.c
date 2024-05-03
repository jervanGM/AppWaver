#include "pw_app_test.h"
#include "safe_memory.h"
#include "pw_app.h"

#ifndef FAKE_FUNC

void test_pw_app_check_mayor_faults() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, -120);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_MAYOR_FAULT);
}

void test_pw_app_check_minor_faults() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, -10);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_MINOR_FAULT);
}

void test_pw_app_check_no_faults() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, 10);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_TASK_OK);
}

void test_pw_app_check_lower_minor_fault_boundary() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_TASK_OK);
}

void test_pw_app_check_upper_minor_fault_boundary() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_MAYOR_FAULT);
}

void test_pw_app_check_lower_major_fault_boundary() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_TASK_OK);
}

void test_pw_app_check_upper_major_fault_boundary() {
    EPwTaskStatus_t fault;
    store_error_in_slot(POWER_ERROR_SLOT, INT8_MAX);
    fault = power_app_check_faults();
    TEST_ASSERT_EQUAL(fault, PW_TASK_OK);
}

#endif

void pw_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_pw_app_check_mayor_faults);
    RUN_TEST(test_pw_app_check_minor_faults);
    RUN_TEST(test_pw_app_check_no_faults);
    RUN_TEST(test_pw_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_pw_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_pw_app_check_lower_major_fault_boundary);
    RUN_TEST(test_pw_app_check_upper_major_fault_boundary);
    #endif
}