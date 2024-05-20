#include "bus_t_share_test.h"
#include "bus_t_share.h"
#include "safe_timer.h"

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_bus_info(void) {
    SBusTaskInfo_t task_info_sent = { .ID = 8, .status = BUS_TASK_OK }; // Sample task info to be sent
    SBusTaskInfo_t task_info_received; // Variable to store received task info
    SBusSensCtrlMsg_t _msg;
    // Set the task information
    set_task_bus_info(task_info_sent);

    // Read the task information
    bus_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_bus_status(void) {
    EBusTaskStatus_t status_sent = BUS_MAYOR_FAULT;
    SBusSensCtrlMsg_t _msg;
    // Set the task status
    set_task_bus_status(status_sent);

    // Read the task status
    bus_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the setting and reading of indicator controller data.
void test_send_and_read_bus_controller_data(void) {
    SAxisDataBuffer_t axis_buff = {.ready = true, .size = 128, .x[0] = 2.34, .y[0] = 4.32, .z[0] = 0.22 };
    STemp_t temp_data = {.temperature = 27};
    SMoist_t moist_data = {.moist = 30};
    SBufTime_t buff_time = {.start_time.sec = 2};

    SBusSensCtrlMsg_t _msg;
    
    bus_controller_send(axis_buff,temp_data, moist_data,buff_time);

    // Read the indicator controller data
    bus_controller_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&axis_buff, &_msg._axis_buff, sizeof(SAxisDataBuffer_t));
    TEST_ASSERT_EQUAL_MEMORY(&temp_data, &_msg._temp_data, sizeof(STemp_t));
    TEST_ASSERT_EQUAL_MEMORY(&moist_data, &_msg._moist_data, sizeof(SMoist_t));
    TEST_ASSERT_EQUAL_MEMORY(&buff_time, &_msg._buff_time, sizeof(SBufTime_t));
}

// Test function for verifying the behavior when reading indicator controller data before sending.
void test_read_bus_controller_data_before_sending(void) {
    SBusSensCtrlMsg_t _msg = {0}; // Initialize _msg with zeros
    SAxisDataBuffer_t axis_buff = {0};
    STemp_t temp_data = {0};
    SMoist_t moist_data = {0};
    SBufTime_t buff_time = {0};

    // Read indicator controller data before sending
    bus_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._axis_buff), sizeof(axis_buff));
    TEST_ASSERT_EQUAL(sizeof(_msg._temp_data), sizeof(temp_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._moist_data), sizeof(moist_data));
    TEST_ASSERT_EQUAL(sizeof(_msg._buff_time), sizeof(buff_time));
}

// Test function for verifying the setting and reading of indicator controller data.
void test_send_and_read_controller_bus_data(void) {
    EDevID_t dev_id = TEMP_HUM_SENS;
    SDevCmd_t cmd = {.heater_cmd = SHT4X_HIGH_HEATER_1S , .force = false};
    SCtrlBusSensMsg_t _msg;
    
    controller_bus_send(dev_id,cmd);

    // Read the indicator controller data
    controller_bus_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&dev_id, &_msg._dev_id, sizeof(EDevID_t));
    TEST_ASSERT_EQUAL_MEMORY(&cmd, &_msg._cmd, sizeof(SDevCmd_t));
}

// Test function for verifying the behavior when reading indicator controller data before sending.
void test_read_controller_bus_data_before_sending(void) {
    SCtrlBusSensMsg_t _msg = {0}; // Initialize _msg with zeros
    EDevID_t dev_id = {0};
    SDevCmd_t cmd = {0};

    // Read indicator controller data before sending
    controller_bus_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._dev_id), sizeof(dev_id));
    TEST_ASSERT_EQUAL(sizeof(_msg._cmd), sizeof(cmd));
}

void bus_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_bus_info);
    RUN_TEST(test_set_and_read_task_bus_status);
    RUN_TEST(test_send_and_read_bus_controller_data);
    RUN_TEST(test_read_bus_controller_data_before_sending);
    RUN_TEST(test_send_and_read_controller_bus_data);
    RUN_TEST(test_read_controller_bus_data_before_sending);
}