#include "acc_it_t_share_test.h"
#include "acc_it_t_share.h"
#include "safe_timer.h"

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_acc_it_info(void) {
    SAccItTaskInfo_t task_info_sent = { .ID = 1, .status = ACC_IT_TASK_OK }; // Sample task info to be sent
    SAccItTaskInfo_t task_info_received; // Variable to store received task info
    SAccItMsg_t _msg;
    // Set the task information
    set_task_acc_it_info(task_info_sent);

    // Read the task information
    acc_it_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of button controller data.
void test_send_and_read_acc_it_controller_data(void) {
    EIntCmd_t int_cmd = ACT_IT1;
    int64_t it_moment = {.sec = 1, .min = 2, .hour = 3, .day = 4, .month = 5, .year = 6};
    SAccItMsg_t _msg;
    
    acc_it_controller_send(int_cmd,it_moment);

    // Read the button controller data
    acc_it_controller_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&int_cmd, &_msg._int_cmd, sizeof(EIntCmd_t));
    TEST_ASSERT_EQUAL_MEMORY(&it_moment, &_msg._it_moment, sizeof(int64_t));
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_acc_it_status(void) {
    EAccItTaskStatus_t status_sent = ACC_IT_MAYOR_FAULT;
    SAccItMsg_t _msg;
    // Set the task status
    set_task_acc_it_status(status_sent);

    // Read the task status
    acc_it_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the behavior when reading button controller data before sending.
void test_read_acc_it_controller_data_before_sending(void) {
    SAccItMsg_t _msg = {0}; // Initialize _msg with zeros
    EIntCmd_t int_cmd = {0};
    int64_t it_moment = {0};

    // Read button controller data before sending
    acc_it_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._int_cmd), sizeof(int_cmd));
    TEST_ASSERT_EQUAL(sizeof(_msg._it_moment), sizeof(it_moment));
}

void acc_it_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_acc_it_info);
    RUN_TEST(test_send_and_read_acc_it_controller_data);
    RUN_TEST(test_set_and_read_task_acc_it_status);
    RUN_TEST(test_read_acc_it_controller_data_before_sending);
}