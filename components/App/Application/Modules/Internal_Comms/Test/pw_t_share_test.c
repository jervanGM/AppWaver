#include "pw_t_share_test.h"
#include "pw_t_share.h"
#include "safe_timer.h"
#include <windows.h>

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_power_info(void) {
    SPwTaskInfo_t task_info_sent = { .ID = 1, .status = PW_TASK_OK }; // Sample task info to be sent
    SPwTaskInfo_t task_info_received; // Variable to store received task info
    SPwCtrlMsg_t _msg;
    // Set the task information
    set_task_power_info(task_info_sent);

    // Read the task information
    pw_ctrl_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_power_status(void) {
    EPwTaskStatus_t status_sent = PW_MAYOR_FAULT;
    SPwCtrlMsg_t _msg;
    // Set the task status
    set_task_power_status(status_sent);

    // Read the task status
    pw_ctrl_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading power controller data before sending.
void test_read_power_controller_data_before_sending(void) {
    SPwCtrlMsg_t _msg = {0}; // Initialize _msg with zeros
    SPwTaskInfo_t task_info = {0};

    // Read power controller data before sending
    pw_ctrl_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._task_info), sizeof(task_info));
}

// Test function for verifying the setting and reading of power controller data.
void test_send_and_read_controller_power_data(void) {
    ESensSwSts_t sens_sw_sts;
    EMainSwSts_t main_sw_sts;
    ESoilActSts_t soil_act_sts;
    EPwMode_t pw_mode;
    EWifiActSts_t wifi_act_sts;
    SCtrlPwMsg_t _msg;
    
    ctrl_pw_send(sens_sw_sts,main_sw_sts,soil_act_sts,wifi_act_sts,pw_mode);

    // Read the power controller data
    ctrl_pw_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&sens_sw_sts, &_msg._sens_sw_sts, sizeof(ESensSwSts_t));
    TEST_ASSERT_EQUAL_MEMORY(&main_sw_sts, &_msg._main_sw_sts, sizeof(EMainSwSts_t));
    TEST_ASSERT_EQUAL_MEMORY(&soil_act_sts, &_msg._soil_act_sts, sizeof(ESoilActSts_t));
    TEST_ASSERT_EQUAL_MEMORY(&wifi_act_sts, &_msg._wifi_act_sts, sizeof(EWifiActSts_t));
    TEST_ASSERT_EQUAL_MEMORY(&pw_mode, &_msg._pw_mode, sizeof(EPwMode_t));
}

// Test function for verifying the behavior when reading power controller data before sending.
void test_read_controller_power_data_before_sending(void) {
    SCtrlPwMsg_t _msg = {0}; // Initialize _msg with zeros
    ESensSwSts_t sens_sw_sts = {0};
    EMainSwSts_t main_sw_sts = {0};
    ESoilActSts_t soil_act_sts = {0};
    EWifiActSts_t wifi_act_sts = {0};
    EPwMode_t pw_mode = {0};

    // Read power controller data before sending
    ctrl_pw_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._sens_sw_sts), sizeof(sens_sw_sts));
    TEST_ASSERT_EQUAL(sizeof(_msg._main_sw_sts), sizeof(main_sw_sts));
    TEST_ASSERT_EQUAL(sizeof(_msg._soil_act_sts), sizeof(soil_act_sts));
    TEST_ASSERT_EQUAL(sizeof(_msg._wifi_act_sts), sizeof(wifi_act_sts));
    TEST_ASSERT_EQUAL(sizeof(_msg._pw_mode), sizeof(pw_mode));
}

void pw_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_power_info);
    RUN_TEST(test_set_and_read_task_power_status);
    RUN_TEST(test_read_power_controller_data_before_sending);
    RUN_TEST(test_send_and_read_controller_power_data);
    RUN_TEST(test_read_controller_power_data_before_sending);
}