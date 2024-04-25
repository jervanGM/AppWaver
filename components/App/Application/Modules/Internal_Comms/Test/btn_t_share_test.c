#include "btn_t_share_test.h"
#include "btn_t_share.h"
#include "safe_timer.h"
#include <windows.h>

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_button_info(void) {
    SBtnTaskInfo_t task_info_sent = { .ID = 1, .status = BTN_TASK_OK }; // Sample task info to be sent
    SBtnTaskInfo_t task_info_received; // Variable to store received task info
    SBtnMsg_t _msg;
    // Set the task information
    set_task_button_info(task_info_sent);

    // Read the task information
    button_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of button controller data.
void test_send_and_read_button_controller_data(void) {
    EBtnCmd_t cmd_sent;
    SBtnMsg_t _msg;
    
    button_controller_send(cmd_sent);

    // Read the button controller data
    button_controller_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&cmd_sent, &_msg._btn_cmd, sizeof(EBtnCmd_t));
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_button_status(void) {
    EBtnTaskStatus_t status_sent = BTN_MAYOR_FAULT;
    SBtnMsg_t _msg;
    // Set the task status
    set_task_button_status(status_sent);

    // Read the task status
    button_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading button controller data before sending.
void test_read_button_controller_data_before_sending(void) {
    SBtnMsg_t _msg = {0}; // Initialize _msg with zeros
    EBtnCmd_t cmd_sent = {0};

    // Read button controller data before sending
    button_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._btn_cmd), sizeof(cmd_sent));
}

void btn_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_button_info);
    RUN_TEST(test_send_and_read_button_controller_data);
    RUN_TEST(test_set_and_read_task_button_status);
    RUN_TEST(test_read_button_controller_data_before_sending);
}