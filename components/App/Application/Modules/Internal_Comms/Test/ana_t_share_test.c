#include "ana_t_share_test.h"
#include "analog_t_share.h"
#include "safe_timer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#endif

void setUp(void)
{
}

void tearDown(void)
{
}

// Test function for verifying the setting and reading of task information.
void test_set_and_read_task_analog_info(void) {
    SAnaTaskInfo_t task_info_sent = { .ID = 1, .status = ANA_TASK_OK }; // Sample task info to be sent
    SAnaTaskInfo_t task_info_received; // Variable to store received task info
    SAnalogSensMsg_t _msg;
    // Set the task information
    set_task_analog_info(task_info_sent);

    // Read the task information
    analog_controller_read(&_msg);

    // Assert that the sent task information matches the received task information
    TEST_ASSERT_EQUAL_UINT32(task_info_sent.ID, _msg._task_info.ID);
    TEST_ASSERT_EQUAL(task_info_sent.status, _msg._task_info.status);
}

// Test function for verifying the setting and reading of analog controller data.
void test_send_and_read_analog_controller_data(void) {
    SDataBuffer_t plant_buff_sent = { .data = {1, 2, 3, 4, 5} }; // Sample plant buffer to be sent
    SBufferTime_t buff_time_sent;   // Sample buffer time to be sent
    SDataBuffer_t plant_buff_received; // Variable to store received plant buffer
    SBufferTime_t buff_time_received;  // Variable to store received buffer time
    SAnalogSensMsg_t _msg;
#ifdef _WIN32
    // Send the analog controller data
    buff_time_sent.start_time = GetTickCount(); // Use GetTickCount() for Windows
    Sleep(1000);
    buff_time_sent.end_time = GetTickCount();
#else
    // Send the analog controller data
    buff_time_sent.start_time = get_system_time(); // Use get_system_time() for POSIX
    usleep(1000000); // Use usleep() for POSIX
    buff_time_sent.end_time = get_system_time();
#endif
    analog_controller_send(plant_buff_sent, buff_time_sent);

    // Read the analog controller data
    analog_controller_read(&_msg);

    // Assert that the sent plant buffer and buffer time match the received plant buffer and buffer time
    TEST_ASSERT_EQUAL_MEMORY(&plant_buff_sent, &_msg._plant_buff, sizeof(SDataBuffer_t));
    TEST_ASSERT_EQUAL_MEMORY(&buff_time_sent, &_msg._buff_time, sizeof(SBufferTime_t));
}

// Test function for verifying the setting and reading of task status.
void test_set_and_read_task_analog_status(void) {
    EAnaTaskStatus_t status_sent = ANA_MAYOR_FAULT; // Sample task status to be sent
    EAnaTaskStatus_t status_received; // Variable to store received task status
    SAnalogSensMsg_t _msg;
    // Set the task status
    set_task_analog_status(status_sent);

    // Read the task status
    analog_controller_read(&_msg);

    // Assert that the sent task status matches the received task status
    TEST_ASSERT_EQUAL(status_sent, _msg._task_info.status);
}

// Test function for verifying the setting and reading of analog controller data with large buffer sizes.
void test_send_and_read_analog_controller_data_large_buffers(void) {
    SDataBuffer_t plant_buff_sent;
    SBufferTime_t buff_time_sent;
    SDataBuffer_t plant_buff_received;
    SBufferTime_t buff_time_received;
    SAnalogSensMsg_t _msg;
    // Fill the plant buffer with large values
    for (int i = 0; i < 128; ++i) {
        plant_buff_sent.data[i] = i * 1000; // Large values
    }

#ifdef _WIN32
    // Send the analog controller data
    buff_time_sent.start_time = GetTickCount(); // Use GetTickCount() for Windows
    Sleep(1000);
    buff_time_sent.end_time = GetTickCount();
#else
    // Send the analog controller data
    buff_time_sent.start_time = get_system_time(); // Use get_system_time() for POSIX
    usleep(1000000); // Use usleep() for POSIX
    buff_time_sent.end_time = get_system_time();
#endif
    analog_controller_send(plant_buff_sent, buff_time_sent);

    // Read the analog controller data
    analog_controller_read(&_msg);

    // Assert that the sent and received plant buffers match
    TEST_ASSERT_EQUAL_MEMORY(&plant_buff_sent, &_msg._plant_buff, sizeof(SDataBuffer_t));

    // Assert that the sent and received buffer times match
    TEST_ASSERT_EQUAL_MEMORY(&buff_time_sent, &_msg._buff_time, sizeof(SBufferTime_t));
}

// Test function for verifying the behavior when reading analog controller data before sending.
void test_read_analog_controller_data_before_sending(void) {
    SAnalogSensMsg_t _msg = {0}; // Initialize _msg with zeros
    SDataBuffer_t plant_buff = {0}; // Initialize plant_buff with zeros
    SBufferTime_t buff_time = {0}; // Initialize buff_time with zeros

    // Read analog controller data before sending
    analog_controller_read(&_msg);

    // Ensure that the size of _msg's _plant_buff and _buff_time members is equal to the size of plant_buff and buff_time, respectively
    TEST_ASSERT_EQUAL(sizeof(_msg._plant_buff), sizeof(plant_buff));
    TEST_ASSERT_EQUAL(sizeof(_msg._buff_time), sizeof(buff_time));
}

void ana_t_share_test_suite()
{
    RUN_TEST(test_set_and_read_task_analog_info);
    RUN_TEST(test_send_and_read_analog_controller_data);
    RUN_TEST(test_set_and_read_task_analog_status);
    RUN_TEST(test_send_and_read_analog_controller_data_large_buffers);
    RUN_TEST(test_read_analog_controller_data_before_sending);
}