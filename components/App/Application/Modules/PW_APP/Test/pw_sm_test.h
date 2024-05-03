#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

void test_pw_sm_init_valid_pointers();

void test_pw_sm_init_null_pointers();

void test_pw_sm_init_to_full_pw_transition();

void test_pw_sm_init_to_breakdown_transition();

void test_pw_sm_full_pw_to_breakdown_transition();

void test_pw_sm_low_power_to_breakdown_transition();

void test_pw_sm_power_off_to_breakdown_transition();

void test_pw_sm_init_to_power_off_transition();

void test_pw_sm_full_pw_to_power_off_transition();

void test_pw_sm_low_power_to_power_off_transition();

void test_pw_sm_breakdown_unknown_state_transition();

void test_pw_sm_init_unknown_state_transition();

void test_pw_sm_full_pw_unknown_state_transition();

void test_pw_sm_low_pw_unknown_state_transition();

void test_pw_sm_pw_off_unknown_state_transition();

void test_pw_sm_full_pw_to_low_pw_transition();

void test_pw_sm_low_pw_to_full_pw_transition();


#endif /* TRACE_TEST_H_ */