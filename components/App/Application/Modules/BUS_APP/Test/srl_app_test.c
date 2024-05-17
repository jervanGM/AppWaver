#include "srl_app_test.h"
#include "safe_memory.h"
#include "serial_app.h"
#include <string.h>

#ifndef FAKE_FUNC
void test_serial_app_check_mayor_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, -120);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MAYOR_FAULT);
}

void test_serial_app_check_minor_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, -10);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MINOR_FAULT);
}

void test_serial_app_check_no_faults() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, 10);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_serial_app_check_lower_minor_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_serial_app_check_upper_minor_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_MAYOR_FAULT);
}

void test_serial_app_check_lower_major_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_serial_app_check_upper_major_fault_boundary() {
    EBusTaskStatus_t fault;
    store_error_in_slot(BUS_ERROR_SLOT, INT8_MAX);
    fault = bus_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BUS_TASK_OK);
}

void test_serial_app_command_exist()
{
    char str[20] = {"system_off"};
    bool exist = false;
    exist = cmd_exist(str);
    TEST_ASSERT_EQUAL(exist, true);
    TEST_ASSERT_EQUAL(strcmp(str,"system_off"),0);

}

void test_serial_app_command_not_exist()
{
    char str[20] = {"system_null"};
    bool exist = false;
    exist = cmd_exist(str);
    TEST_ASSERT_EQUAL(exist, false);
    TEST_ASSERT_EQUAL(strcmp(str,"cmd_none"),0);
}

void test_serial_app_null_command()
{
    bool exist = false;
    exist = cmd_exist(NULL);
    TEST_ASSERT_EQUAL(exist, false);
}

void test_serial_app_empty_command()
{
    char str[20] = {""};
    bool exist = false;
    exist = cmd_exist(str);
    TEST_ASSERT_EQUAL(exist, false);
    TEST_ASSERT_EQUAL(strcmp(str,"cmd_none"),0);
}

#endif

void srl_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_serial_app_check_mayor_faults);
    RUN_TEST(test_serial_app_check_minor_faults);
    RUN_TEST(test_serial_app_check_no_faults);
    RUN_TEST(test_serial_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_serial_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_serial_app_check_lower_major_fault_boundary);
    RUN_TEST(test_serial_app_check_upper_major_fault_boundary);
    RUN_TEST(test_serial_app_command_exist);
    RUN_TEST(test_serial_app_command_not_exist);
    RUN_TEST(test_serial_app_null_command);
    RUN_TEST(test_serial_app_empty_command);
    #endif
}