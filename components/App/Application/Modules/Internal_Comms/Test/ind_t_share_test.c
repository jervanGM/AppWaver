#include "ind_t_share_test.h"
#include "ind_t_share.h"
#include "safe_timer.h"

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_indicator_info(void) {
    SIndTaskInfo_t task_info_sent = { .ID = 1, .status = IND_TASK_OK }; // Sample task info to be sent
    SIndTaskInfo_t task_info_received; // Variable to store received task info
    SIndCtrlMsg_t _msg;
    // Set the task information
    set_task_indicator_info(task_info_sent);

    // Read the task information
    ind_ctrl_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_indicator_status(void) {
    EIndTaskStatus_t status_sent = IND_MAYOR_FAULT;
    SIndCtrlMsg_t _msg;
    // Set the task status
    set_task_indicator_status(status_sent);

    // Read the task status
    ind_ctrl_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading indicator controller data before sending.
void test_read_indicator_controller_data_before_sending(void) {
    SIndCtrlMsg_t _msg = {0}; // Initialize _msg with zeros
    SIndTaskInfo_t task_info = {0};

    // Read indicator controller data before sending
    ind_ctrl_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._task_info), sizeof(task_info));
}

// Test function for verifying the setting and reading of indicator controller data.
void test_send_and_read_controller_indicator_data(void) {
    EIndId_t ind_id; 
    EIndSts_t ind_state;
    SCtrlIndMsg_t _msg;
    
    ctrl_ind_send(ind_id,ind_state);

    // Read the indicator controller data
    ctrl_ind_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&ind_id, &_msg._ind_id, sizeof(EIndId_t));
    TEST_ASSERT_EQUAL_MEMORY(&ind_state, &_msg._ind_state, sizeof(EIndSts_t));
}

// Test function for verifying the behavior when reading indicator controller data before sending.
void test_read_controller_indicator_data_before_sending(void) {
    SCtrlIndMsg_t _msg = {0}; // Initialize _msg with zeros
    EIndId_t ind_id = {0}; 
    EIndSts_t ind_state = {0};

    // Read indicator controller data before sending
    ctrl_ind_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._ind_id), sizeof(ind_id));
    TEST_ASSERT_EQUAL(sizeof(_msg._ind_state), sizeof(ind_state));
}

void ind_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_indicator_info);
    RUN_TEST(test_set_and_read_task_indicator_status);
    RUN_TEST(test_read_indicator_controller_data_before_sending);
    RUN_TEST(test_send_and_read_controller_indicator_data);
    RUN_TEST(test_read_controller_indicator_data_before_sending);
}