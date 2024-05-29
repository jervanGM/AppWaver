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

void test_analog_app_process_enviromental_data()
{
    SAnaEnvData_t processed_data;
    uint32_t env_data[3] = {1250,600,3310};
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(env_data);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,48);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,49);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,33);
}

void test_analog_app_process_null_enviromental_data()
{
    SAnaEnvData_t processed_data;
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(NULL);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,ANA_APP_ENV_DATA_EMPTY);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,0);
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);
}

void test_analog_app_process_enviromental_data_max_values()
{
    SAnaEnvData_t processed_data;
    uint32_t env_data[3] = {UINT32_MAX,UINT32_MAX,UINT32_MAX};
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(env_data);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,100);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,100);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,100);
}

void test_analog_app_process_enviromental_data_max_limits()
{
    SAnaEnvData_t processed_data;
    uint32_t env_data[3] = {MAX_I_SOLAR_VALUE_THRESHOLD,MAX_V_SOLAR_VALUE_THRESHOLD,MAX_SOIL_MOIST_THRESHOLD};
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(env_data);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,100);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,100);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,100);
}

void test_analog_app_process_enviromental_data_min_values()
{
    SAnaEnvData_t processed_data;
    uint32_t env_data[3] = {0,0,0};
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(env_data);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,0);
}

void test_analog_app_process_enviromental_data_min_limits()
{
    SAnaEnvData_t processed_data;
    uint32_t env_data[3] = {MIN_I_SOLAR_VALUE_THRESHOLD,MIN_V_SOLAR_VALUE_THRESHOLD,MIN_SOIL_MOIST_THRESHOLD};
    store_error_in_slot(ANALOGIC_ERROR_SLOT,0);

    processed_data = process_enviromental_data(env_data);

    int8_t error = read_error_from_slot(ANALOGIC_ERROR_SLOT);
    TEST_ASSERT_EQUAL(error,0);
    TEST_ASSERT_EQUAL(processed_data.direct_sun_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.light_percentage,0);
    TEST_ASSERT_EQUAL(processed_data.soil_moist_percentage,0);
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
    RUN_TEST(test_analog_app_process_enviromental_data);
    RUN_TEST(test_analog_app_process_null_enviromental_data);
    RUN_TEST(test_analog_app_process_enviromental_data_max_values);
    RUN_TEST(test_analog_app_process_enviromental_data_min_values);
    RUN_TEST(test_analog_app_process_enviromental_data_max_limits);
    RUN_TEST(test_analog_app_process_enviromental_data_min_limits);
    #endif
}