#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

void test_btn_app_check_mayor_faults();

void test_btn_app_check_minor_faults();

void test_btn_app_check_no_faults();

void test_btn_app_check_lower_minor_fault_boundary();

void test_btn_app_check_upper_minor_fault_boundary();

void test_btn_app_check_lower_major_fault_boundary();

void test_btn_app_check_upper_major_fault_boundary();

void test_btn_app_process_short_press_cmd();

void test_btn_app_process_long_press_cmd();

void test_btn_app_process_power_off_cmd();

void test_btn_app_process_no_pulse_cmd();

void test_btn_app_process_error_cmd();

void test_btn_app_process_unknown_cmd();

void test_short_and_long_press_combination();

void test_short_press_after_long_press();

#endif /* TRACE_TEST_H_ */