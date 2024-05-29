#include "acc_it_app_test.h"
#include "safe_memory.h"
#include "acc_it_app.h"

#ifndef FAKE_FUNC
void test_acc_it_app_check_mayor_faults() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, -120);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_MAYOR_FAULT);
}

void test_acc_it_app_check_minor_faults() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, -10);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_MINOR_FAULT);
}

void test_acc_it_app_check_no_faults() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, 10);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_TASK_OK);
}

void test_acc_it_app_check_lower_minor_fault_boundary() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_TASK_OK);
}

void test_acc_it_app_check_upper_minor_fault_boundary() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_MAYOR_FAULT);
}

void test_acc_it_app_check_lower_major_fault_boundary() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_TASK_OK);
}

void test_acc_it_app_check_upper_major_fault_boundary() {
    EAccItTaskStatus_t fault;
    store_error_in_slot(ACC_IT_ERROR_SLOT, INT8_MAX);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, ACC_IT_TASK_OK);
}

#endif

void acc_it_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_acc_it_app_check_mayor_faults);
    RUN_TEST(test_acc_it_app_check_minor_faults);
    RUN_TEST(test_acc_it_app_check_no_faults);
    RUN_TEST(test_acc_it_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_acc_it_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_acc_it_app_check_lower_major_fault_boundary);
    RUN_TEST(test_acc_it_app_check_upper_major_fault_boundary);
    #endif
}