#include "acc_it_app_test.h"
#include "safe_memory.h"
#include "acc_it_app.h"

#ifndef FAKE_FUNC
void test_acc_it_app_check_mayor_faults() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, -120);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_MAYOR_FAULT);
}

void test_acc_it_app_check_minor_faults() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, -10);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_MINOR_FAULT);
}

void test_acc_it_app_check_no_faults() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, 10);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_TASK_OK);
}

void test_acc_it_app_check_lower_minor_fault_boundary() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_TASK_OK);
}

void test_acc_it_app_check_upper_minor_fault_boundary() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_MAYOR_FAULT);
}

void test_acc_it_app_check_lower_major_fault_boundary() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_TASK_OK);
}

void test_acc_it_app_check_upper_major_fault_boundary() {
    EBtnTaskStatus_t fault;
    store_error_in_slot(BUTTON_ERROR_SLOT, INT8_MAX);
    fault = acc_it_app_check_faults();
    TEST_ASSERT_EQUAL(fault, BTN_TASK_OK);
}

void test_acc_it_app_process_short_press_cmd() {
    EBtnPulse_t pulse = SHORT_PRESS;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_MODE1);
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_MODE2);
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_MODE3);
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_NORMAL);
}

void test_acc_it_app_process_long_press_cmd() {
    EBtnPulse_t pulse = LONG_PRESS;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_LONG1);
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_NORMAL);
}

void test_acc_it_app_process_power_off_cmd() {
    EBtnPulse_t pulse = POWER_OFF;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_PW_OFF);
}

void test_acc_it_app_process_no_pulse_cmd() {
    EBtnPulse_t pulse = NO_PULSE;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    acc_it_app_init();
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_NORMAL);
}

void test_acc_it_app_process_error_cmd() {
    EBtnPulse_t pulse = PULSE_ERR;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_ERROR);
}

void test_acc_it_app_process_unknown_cmd() {
    EBtnPulse_t pulse = (EBtnPulse_t)255;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    cmd = acc_it_app_process_cmd(pulse);
    TEST_ASSERT_EQUAL(cmd, BTN_CMD_ERROR);
}

// Prueba de combinación de pulsaciones cortas y largas
void test_short_and_long_press_combination() {
    EBtnPulse_t pulse_short = SHORT_PRESS;
    EBtnPulse_t pulse_long = LONG_PRESS;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    acc_it_app_init();
    // Corta, larga, corta
    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE1);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE1);

    // Larga, corta, larga
    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE1);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);

    // Larga, corta, corta
    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE1);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE2);

    // Corta, corta, larga
    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_MODE3);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);

    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);
}

// Prueba de pulsación corta después de una larga
void test_short_press_after_long_press() {
    EBtnPulse_t pulse_long = LONG_PRESS;
    EBtnPulse_t pulse_short = SHORT_PRESS;
    EBtnCmd_t cmd = BTN_CMD_NORMAL;
    acc_it_app_init();
    cmd = acc_it_app_process_cmd(pulse_long);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_LONG1);

    cmd = acc_it_app_process_cmd(pulse_short);
    TEST_ASSERT_EQUAL(cmd , BTN_CMD_NORMAL);
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
    RUN_TEST(test_acc_it_app_process_short_press_cmd);
    RUN_TEST(test_acc_it_app_process_long_press_cmd);
    RUN_TEST(test_acc_it_app_process_power_off_cmd);
    RUN_TEST(test_acc_it_app_process_no_pulse_cmd);
    RUN_TEST(test_acc_it_app_process_error_cmd);
    RUN_TEST(test_acc_it_app_process_unknown_cmd);
    RUN_TEST(test_short_and_long_press_combination);
    RUN_TEST(test_short_press_after_long_press);
    #endif
}