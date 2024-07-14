#include "mem_app.h"
#include "safe_memory.h"
#include "safe_timer.h"
#include <string.h>

static SWavHeader def_header;

void mem_app_init()
{
    // Initialize default WAV header values
    memcpy(def_header.riff, "RIFF", 4);
    memcpy(def_header.wave, "WAVE", 4);
    memcpy(def_header.fmt, "fmt ", 4);
    memcpy(def_header.data, "data", 4);

    def_header.chunk_size = WAV_CHUNKS;
    def_header.format_tag = WAV_FORMAT;
    def_header.num_chans = WAV_CHANNELS;
    def_header.srate = WAV_DEF_SRATE;
    def_header.bits_per_samp = WAV_BITS;
    def_header.bytes_per_sec = def_header.srate * def_header.bits_per_samp / 8 * def_header.num_chans;
    def_header.bytes_per_samp = (def_header.bits_per_samp / 8) * def_header.num_chans;

    def_header.dlength = DATA_BUFFER_SIZE * def_header.bytes_per_samp;
    def_header.flength = def_header.dlength + sizeof(SWavHeader);
}

SWavData process_data_to_wav(uint32_t* data, int64_t start_t, int64_t end_t)
{
    SWavData wav;
    SWavHeader empty_header = {0};
    STime_t start_secs = encode_time_to_date(start_t);
    static int64_t prev_start_secs = 0;
    static int64_t prev_end_secs = 0;

    // Check if data, time interval, or default header is empty
    if ((data == NULL) || ((end_t - start_t) == 0) || 
        (memcmp(&def_header, &empty_header, sizeof(SWavHeader)) == 0))
    {
        // Store error and log warning if any input data is invalid
        store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_APP_PROCESS_NULL_WAV_DATA);
        TRACE_WARNING("Any of the input data to process WAV files is not valid or declared");  
        memset(&wav, 0, sizeof(SWavData));
        return wav;
    }
    
    uint32_t average = 0;
    
    char time_string[100];
    if ((prev_start_secs != start_t) && (prev_end_secs != end_t))
    {
        // Generate WAV file name based on start time
        sprintf(time_string, "%02d-%02d-%04d_%02d-%02d-%02d.wav", start_secs.year, start_secs.month, start_secs.day, start_secs.hour, start_secs.min, start_secs.sec);
 
        // Create file path for WAV file
        sprintf(wav.file_path, "%s/%d/%s", WAV_FOLDER, wav_subfolder, time_string);

        wav.header = def_header;
        wav.header.srate = DATA_BUFFER_SIZE / (end_t - start_t);
        wav.header.bytes_per_sec = wav.header.srate * wav.header.bits_per_samp / 8 * wav.header.num_chans;
        wav.data = (int16_t *)malloc(DATA_BUFFER_SIZE * sizeof(int16_t));

        // Copy data and calculate average
        for (size_t i = 0; i < DATA_BUFFER_SIZE; i++)
        {
            average += data[i] / DATA_BUFFER_SIZE;
        }

        for (size_t i = 0; i < DATA_BUFFER_SIZE; i++)
        {
            wav.data[i] = (int16_t)data[i];
        }

        wav.average = average;
    }
    else
    {
        wav.average = 0;
    }
    prev_start_secs = start_t;
    prev_end_secs = end_t;

    return wav;
}

EMemTaskStatus_t mem_app_check_faults()
{
    int8_t error = 0;

    // Read error from specified slot
    error = read_error_from_slot(EXT_MEM_ERROR_SLOT);

    // Determine task status based on error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return MINOR_FAULT if error is within defined range
        return MEM_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return MAYOR_FAULT if error is less than MAYOR_FAULT_THRESHOLD
        return MEM_MAJOR_FAULT;
    }
    else
    {
        // Return TASK_OK if no faults detected
        return MEM_TASK_OK;
    }
}