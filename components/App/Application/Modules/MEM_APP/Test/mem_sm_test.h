#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

void test_mem_sm_init_valid_pointers();

void test_mem_sm_init_null_pointers();

void test_mem_sm_init_to_operational_transition();

void test_mem_sm_init_to_breakdown_transition();

void test_mem_sm_operational_to_breakdown_transition();

void test_mem_sm_breakdown_unknown_state_transition();

void test_mem_sm_init_unknown_state_transition();

void test_mem_sm_operational_unknown_state_transition();


#endif /* TRACE_TEST_H_ */