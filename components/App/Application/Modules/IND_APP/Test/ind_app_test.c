#include "ind_app_test.h"
#include "safe_memory.h"
#include "ind_app.h"

#ifndef FAKE_FUNC

void test_ind_app_check_mayor_faults() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, -120);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_MAYOR_FAULT);
}

void test_ind_app_check_minor_faults() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, -10);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_MINOR_FAULT);
}

void test_ind_app_check_no_faults() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, 10);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_TASK_OK);
}

void test_ind_app_check_lower_minor_fault_boundary() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_TASK_OK);
}

void test_ind_app_check_upper_minor_fault_boundary() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_MAYOR_FAULT);
}

void test_ind_app_check_lower_major_fault_boundary() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_TASK_OK);
}

void test_ind_app_check_upper_major_fault_boundary() {
    EIndTaskStatus_t fault;
    store_error_in_slot(INDICATOR_ERROR_SLOT, INT8_MAX);
    fault = ind_app_check_faults();
    TEST_ASSERT_EQUAL(fault, IND_TASK_OK);
}

#endif

void ind_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_ind_app_check_mayor_faults);
    RUN_TEST(test_ind_app_check_minor_faults);
    RUN_TEST(test_ind_app_check_no_faults);
    RUN_TEST(test_ind_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_ind_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_ind_app_check_lower_major_fault_boundary);
    RUN_TEST(test_ind_app_check_upper_major_fault_boundary);
    #endif
}