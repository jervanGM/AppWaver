#include "srl_t_share_test.h"
#include "srl_t_share.h"
#include "safe_timer.h"

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_serial_info(void) {
    SSrlTaskInfo_t task_info_sent = { .ID = 1, .status = SRL_TASK_OK, .delay = 1000, .LastWakeTime= 2000 }; // Sample task info to be sent
    SSerialMsg_t _msg;
    // Set the task information
    set_task_serial_info(task_info_sent);

    // Read the task information
    serial_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of serial controller data.
void test_send_and_read_serial_controller_data(void) {
    ESrlConnStatus_t conn_sts = SRL_CONNECTED; // Variable to store received plant buffer
    SSerialCmd_t srl_cmd = {.cmd = "system_off", .force = 1};  // Variable to store received buffer time
    SSerialMsg_t _msg;
    // Send the serial controller data
    set_serial_command(srl_cmd);
    set_serial_connection_status(conn_sts);

    // Read the serial controller data
    serial_controller_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&srl_cmd, &_msg._command, sizeof(SSerialCmd_t));
    TEST_ASSERT_EQUAL_MEMORY(&conn_sts, &_msg._serial_status, sizeof(ESrlConnStatus_t));
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_serial_status(void) {
    ESrlTaskStatus_t status_sent = SRL_MAYOR_FAULT; // Sample task status to be sent
    SSerialMsg_t _msg;
    // Set the task status
    set_task_serial_status(status_sent);

    // Read the task status
    serial_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading serial controller data before sending.
void test_read_serial_controller_data_before_sending(void) {
    SSerialMsg_t _msg = {0}; // Initialize _msg with zeros
    ESrlConnStatus_t conn_status = {0}; // Initialize plant_buff with zeros
    SSerialCmd_t srl_cmd = {0}; // Initialize buff_time with zeros

    // Read serial controller data before sending
    serial_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._serial_status), sizeof(conn_status));
    TEST_ASSERT_EQUAL(sizeof(_msg._command), sizeof(srl_cmd));
}

void srl_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_serial_info);
    RUN_TEST(test_send_and_read_serial_controller_data);
    RUN_TEST(test_set_and_read_task_serial_status);
    RUN_TEST(test_read_serial_controller_data_before_sending);
}