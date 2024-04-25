#include "mem_app_test.h"
#include "safe_memory.h"
#include "mem_app.h"
#include <string.h>

#ifndef FAKE_FUNC

void test_mem_app_check_mayor_faults() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, -120);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_MAYOR_FAULT);
}

void test_mem_app_check_minor_faults() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, -10);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_MINOR_FAULT);
}

void test_mem_app_check_no_faults() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, 10);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_TASK_OK);
}

void test_mem_app_check_lower_minor_fault_boundary() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_TASK_OK);
}

void test_mem_app_check_upper_minor_fault_boundary() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_MAYOR_FAULT);
}

void test_mem_app_check_lower_major_fault_boundary() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_TASK_OK);
}

void test_mem_app_check_upper_major_fault_boundary() {
    EMemTaskStatus_t fault;
    store_error_in_slot(EXT_MEM_ERROR_SLOT, INT8_MAX);
    fault = mem_app_check_faults();
    TEST_ASSERT_EQUAL(fault, MEM_TASK_OK);
}

void test_mem_app_process_wav_data()
{
    SWavData wav;
    STime_t start_t = {0};
    STime_t end_t;
    uint32_t data[128];
    end_t.sec = 13;
    for(int i=0; i<128;i++)
    {
        data[i] = rand() % 200;
    }

    mem_app_init();
    wav = process_data_to_wav(data,start_t,end_t);
    TEST_ASSERT_EQUAL(memcmp(wav.header.riff, "RIFF", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.wave,"WAVE", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.fmt,"fmt ", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.data,"data", 4), 0);
    TEST_ASSERT_EQUAL(wav.header.chunk_size,16);
    TEST_ASSERT_EQUAL(wav.header.format_tag,1);
    TEST_ASSERT_EQUAL(wav.header.num_chans,1);
    TEST_ASSERT_EQUAL(wav.header.srate,9);
    TEST_ASSERT_EQUAL(wav.header.bits_per_samp,16);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_sec,18);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_samp,2);
    TEST_ASSERT_EQUAL(wav.header.dlength,256);
    TEST_ASSERT_EQUAL(wav.header.flength,300);
    for (int i = 0; i < 128; i++) {
        TEST_ASSERT_EQUAL(wav.data[i], data[i]);  
    }
}

void test_mem_app_process_same_wav_data()
{
    SWavData wav;
    STime_t start_t = {0};
    STime_t end_t;
    uint32_t data[128];
    end_t.sec = 13;
    for(int i=0; i<128;i++)
    {
        data[i] = rand() % 200;
    }

    mem_app_init();
    wav = process_data_to_wav(data,start_t,end_t);
    TEST_ASSERT_EQUAL(memcmp(wav.header.riff, "RIFF", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.wave,"WAVE", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.fmt,"fmt ", 4), 0);
    TEST_ASSERT_EQUAL(memcmp(wav.header.data,"data", 4), 0);
    TEST_ASSERT_EQUAL(wav.header.chunk_size,16);
    TEST_ASSERT_EQUAL(wav.header.format_tag,1);
    TEST_ASSERT_EQUAL(wav.header.num_chans,1);
    TEST_ASSERT_EQUAL(wav.header.srate,9);
    TEST_ASSERT_EQUAL(wav.header.bits_per_samp,16);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_sec,18);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_samp,2);
    TEST_ASSERT_EQUAL(wav.header.dlength,256);
    TEST_ASSERT_EQUAL(wav.header.flength,300);
    for (int i = 0; i < 128; i++) {
        TEST_ASSERT_EQUAL(wav.data[i], data[i]);  
    }
    TEST_ASSERT_NOT_EQUAL(wav.average,0);

    wav = process_data_to_wav(data,start_t,end_t);
    TEST_ASSERT_EQUAL(wav.average,0);
}

void test_mem_app_process_not_init_wav_data()
{
    SWavData wav;
    STime_t start_t = {0};
    STime_t end_t;
    uint32_t data[128];
    end_t.sec = 13;
    for(int i=0; i<128;i++)
    {
        data[i] = rand() % 200;
    }

    wav = process_data_to_wav(data,start_t,end_t);
    TEST_ASSERT_EQUAL(wav.header.chunk_size,0);
    TEST_ASSERT_EQUAL(wav.header.format_tag,0);
    TEST_ASSERT_EQUAL(wav.header.num_chans,0);
    TEST_ASSERT_EQUAL(wav.header.srate,0);
    TEST_ASSERT_EQUAL(wav.header.bits_per_samp,0);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_sec,0);
    TEST_ASSERT_EQUAL(wav.header.bytes_per_samp,0);
    TEST_ASSERT_EQUAL(wav.header.dlength,0);
    TEST_ASSERT_EQUAL(wav.header.flength,0);
    TEST_ASSERT_NULL(wav.data);
    TEST_ASSERT_EQUAL(wav.average,0);

}

void test_process_data_to_wav_null_pointer()
{
    SWavData wav;
    STime_t start_t = {0};
    STime_t end_t;
    uint32_t data[128];
    end_t.sec = 13;
    for(int i = 0; i < 128; i++)
    {
        data[i] = rand() % 200;
    }

    
    wav = process_data_to_wav(NULL, start_t, end_t);
    
    TEST_ASSERT_EQUAL(wav.average, 0);

    end_t.sec = 0;
    wav = process_data_to_wav(data, start_t, end_t);
    
    TEST_ASSERT_EQUAL(wav.average, 0);

}

#endif

void mem_app_test_suite()
{
    #ifndef FAKE_FUNC
    RUN_TEST(test_mem_app_check_mayor_faults);
    RUN_TEST(test_mem_app_check_minor_faults);
    RUN_TEST(test_mem_app_check_no_faults);
    RUN_TEST(test_mem_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_mem_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_mem_app_check_lower_major_fault_boundary);
    RUN_TEST(test_mem_app_check_upper_major_fault_boundary);
    RUN_TEST(test_mem_app_process_not_init_wav_data);
    RUN_TEST(test_mem_app_process_wav_data);
    RUN_TEST(test_process_data_to_wav_null_pointer);
    RUN_TEST(test_mem_app_process_same_wav_data);
    #endif
}