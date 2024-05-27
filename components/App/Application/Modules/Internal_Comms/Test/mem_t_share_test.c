#include "mem_t_share_test.h"
#include "mem_t_share.h"
#include "safe_timer.h"

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_memory_info(void) {
    SMemTaskInfo_t task_info_sent = { .ID = 1, .status = MEM_TASK_OK }; // Sample task info to be sent
    SMemTaskInfo_t task_info_received; // Variable to store received task info
    SMemCtrlMsg_t _msg;
    // Set the task information
    set_task_ext_mem_info(task_info_sent);

    // Read the task information
    mem_ctrl_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_memory_status(void) {
    EMemTaskStatus_t status_sent = MEM_MAYOR_FAULT;
    SMemCtrlMsg_t _msg;
    // Set the task status
    set_task_ext_mem_status(status_sent);

    // Read the task status
    mem_ctrl_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading power controller data before sending.
void test_read_memory_controller_data_before_sending(void) {
    SMemCtrlMsg_t _msg = {0}; // Initialize _msg with zeros
    SMemTaskInfo_t task_info = {0};

    // Read power controller data before sending
    mem_ctrl_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._task_info), sizeof(task_info));
}

// Test function for verifying the setting and reading of power controller data.
void test_send_and_read_controller_memory_data(void) {
    SErrorInfo_t alarm;
    SSystemStatus_t status;
    uint32_t plant_signal[128];
    SEnvData_t env_data;
    SPowerData_t power_data;
    SAxisData_t axis_buff[128];
    ESysMode_t current_mode;
    ESysMode_t previous_mode;
    int64_t start_time;
    int64_t end_time;
    int64_t system_time;
    SCtrlMemMsg_t _msg;
    
    ctrl_mem_send(alarm,status,plant_signal,env_data,power_data, axis_buff,current_mode,previous_mode,start_time,end_time,system_time);

    // Read the power controller data
    ctrl_mem_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&alarm, &_msg._alarm, sizeof(SErrorInfo_t));
    TEST_ASSERT_EQUAL_MEMORY(&status, &_msg._status, sizeof(SSystemStatus_t));
    TEST_ASSERT_EQUAL_MEMORY(&plant_signal, &_msg._plant_signal, sizeof(uint32_t)*128);
    TEST_ASSERT_EQUAL_MEMORY(&env_data, &_msg._env_data, sizeof(SEnvData_t));
    TEST_ASSERT_EQUAL_MEMORY(&power_data, &_msg._power_data, sizeof(SPowerData_t));
    TEST_ASSERT_EQUAL_MEMORY(&axis_buff, &_msg._axis_buff, sizeof(SAxisData_t)*128);
    TEST_ASSERT_EQUAL_MEMORY(&current_mode, &_msg._current_mode, sizeof(ESysMode_t));
    TEST_ASSERT_EQUAL_MEMORY(&previous_mode, &_msg._previous_mode, sizeof(ESysMode_t));
    TEST_ASSERT_EQUAL_MEMORY(&start_time, &_msg._start_time, sizeof(int64_t));
    TEST_ASSERT_EQUAL_MEMORY(&end_time, &_msg._end_time, sizeof(int64_t));
    TEST_ASSERT_EQUAL_MEMORY(&system_time, &_msg._system_time, sizeof(int64_t));
}

// Test function for verifying the behavior when reading power controller data before sending.
void test_read_controller_memory_data_before_sending(void) {
    SCtrlMemMsg_t _msg = {0}; // Initialize _msg with zeros
    SErrorInfo_t alarm = {0};
    SSystemStatus_t status = {0};
    uint32_t plant_signal[128];
    SEnvData_t env_data = {0};
    SPowerData_t power_data = {0};
    SAxisData_t axis_buff[128];
    ESysMode_t current_mode = {0};
    ESysMode_t previous_mode = {0};
    int64_t start_time = {0};
    int64_t end_time = {0};
    int64_t system_time = {0};

    // Read power controller data before sending
    ctrl_mem_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._alarm), sizeof(alarm));
    TEST_ASSERT_EQUAL(sizeof(_msg._status), sizeof(status));
    TEST_ASSERT_EQUAL(sizeof(_msg._plant_signal), sizeof(plant_signal));
    TEST_ASSERT_EQUAL(sizeof(_msg._env_data), sizeof(env_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._power_data), sizeof(power_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._axis_buff), sizeof(axis_buff));
    TEST_ASSERT_EQUAL(sizeof(_msg._current_mode), sizeof(current_mode));
    TEST_ASSERT_EQUAL(sizeof(_msg._previous_mode), sizeof(previous_mode));
    TEST_ASSERT_EQUAL(sizeof(_msg._start_time), sizeof(start_time));
    TEST_ASSERT_EQUAL(sizeof(_msg._end_time), sizeof(end_time));
    TEST_ASSERT_EQUAL(sizeof(_msg._system_time), sizeof(system_time));
}

void mem_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_memory_info);
    RUN_TEST(test_set_and_read_task_memory_status);
    RUN_TEST(test_read_memory_controller_data_before_sending);
    RUN_TEST(test_send_and_read_controller_memory_data);
    RUN_TEST(test_read_controller_memory_data_before_sending);
}