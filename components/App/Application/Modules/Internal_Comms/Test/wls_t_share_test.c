#include "wls_t_share_test.h"
#include "wireless_t_share.h"
#include "safe_timer.h"
#include <windows.h>

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_wireless_info(void) {
    SWlsTaskInfo_t task_info_sent = { .ID = 1, .status = WLS_TASK_OK }; // Sample task info to be sent
    SWlsTaskInfo_t task_info_received; // Variable to store received task info
    SWlsCtrlMsg_t _msg;
    // Set the task information
    set_task_wireless_info(task_info_sent);

    // Read the task information
    wireless_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_wireless_status(void) {
    EWlsTaskStatus_t status_sent = WLS_MAYOR_FAULT;
    SWlsCtrlMsg_t _msg;
    // Set the task status
    set_task_wireless_status(status_sent);

    // Read the task status
    wireless_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading wireless controller data before sending.
void test_read_wireless_controller_data_before_sending(void) {
    SWlsCtrlMsg_t _msg = {0}; // Initialize _msg with zeros
    SWlsTaskInfo_t task_info = {0};

    // Read wireless controller data before sending
    wireless_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._task_info), sizeof(task_info));
}

// Test function for verifying the setting and reading of wireless controller data.
void test_send_and_read_controller_wireless_data(void) {
    SErrorInfo_t alarm;
    SSystemStatus_t status;
    uint32_t plant_signal[128];
    SEnvData_t env_data;
    SPowerData_t power_data;
    SAxisData_t axis_buff[128];
    ESysMode_t current_mode;
    ESysMode_t previous_mode;
    STime_t system_time;
    SCtrlWlsMsg_t _msg;
    
    controller_wireless_send(alarm,status,plant_signal,env_data,power_data,axis_buff,current_mode,previous_mode,system_time);

    // Read the wireless controller data
    controller_wireless_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&alarm, &_msg._alarm, sizeof(SErrorInfo_t));
    TEST_ASSERT_EQUAL_MEMORY(&status, &_msg._status, sizeof(SSystemStatus_t));
    TEST_ASSERT_EQUAL_MEMORY(&plant_signal, &_msg._plant_signal, sizeof(uint32_t)*128);
    TEST_ASSERT_EQUAL_MEMORY(&env_data, &_msg._env_data, sizeof(SEnvData_t));
    TEST_ASSERT_EQUAL_MEMORY(&power_data, &_msg._power_data, sizeof(SPowerData_t));
    TEST_ASSERT_EQUAL_MEMORY(&axis_buff, &_msg._axis_buff, sizeof(SAxisData_t)*128);
    TEST_ASSERT_EQUAL_MEMORY(&current_mode, &_msg._current_mode, sizeof(ESysMode_t));
    TEST_ASSERT_EQUAL_MEMORY(&previous_mode, &_msg._previous_mode, sizeof(ESysMode_t));
    TEST_ASSERT_EQUAL_MEMORY(&system_time, &_msg._system_time, sizeof(STime_t));
}

// Test function for verifying the behavior when reading wireless controller data before sending.
void test_read_controller_wireless_data_before_sending(void) {
    SCtrlWlsMsg_t _msg = {0};
    SErrorInfo_t alarm = {0};
    SSystemStatus_t status = {0};
    uint32_t plant_signal[128];
    SEnvData_t env_data = {0};
    SPowerData_t power_data = {0};
    SAxisData_t axis_buff[128];
    ESysMode_t current_mode = {0};
    ESysMode_t previous_mode = {0};
    STime_t system_time = {0};

    // Read wireless controller data before sending
    controller_wireless_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._alarm), sizeof(alarm));
    TEST_ASSERT_EQUAL(sizeof(_msg._status), sizeof(status));
    TEST_ASSERT_EQUAL(sizeof(_msg._plant_signal), sizeof(plant_signal));
    TEST_ASSERT_EQUAL(sizeof(_msg._env_data), sizeof(env_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._power_data), sizeof(power_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._axis_buff), sizeof(axis_buff));
    TEST_ASSERT_EQUAL(sizeof(_msg._current_mode), sizeof(current_mode));
    TEST_ASSERT_EQUAL(sizeof(_msg._previous_mode), sizeof(previous_mode));
    TEST_ASSERT_EQUAL(sizeof(_msg._system_time), sizeof(system_time));
}

void wls_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_wireless_info);
    RUN_TEST(test_set_and_read_task_wireless_status);
    RUN_TEST(test_read_wireless_controller_data_before_sending);
    RUN_TEST(test_send_and_read_controller_wireless_data);
    RUN_TEST(test_read_controller_wireless_data_before_sending);
}