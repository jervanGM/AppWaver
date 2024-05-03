#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

void test_mem_app_check_mayor_faults();

void test_mem_app_check_minor_faults();

void test_mem_app_check_no_faults();

void test_mem_app_check_lower_minor_fault_boundary();

void test_mem_app_check_upper_minor_fault_boundary();

void test_mem_app_check_lower_major_fault_boundary();

void test_mem_app_check_upper_major_fault_boundary();

void test_mem_app_process_wav_data();

void test_process_data_to_wav_null_pointer();

void test_mem_app_process_same_wav_data();

void test_mem_app_process_not_init_wav_data();

#endif /* TRACE_TEST_H_ */