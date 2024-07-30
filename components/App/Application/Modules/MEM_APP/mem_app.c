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

    def_header.dlength = DATA_BUFFER_SIZE * (RECORD_MULTIPLER-1) * def_header.bytes_per_samp;
    def_header.flength = def_header.dlength + sizeof(SWavHeader);
}

SWavData process_data_to_wav(uint32_t* data, int64_t start_t, bool record)
{
    SWavData wav;
    SWavHeader empty_header = {0};
    STime_t start_secs = encode_time_to_date(start_t);
    static int64_t prev_start_secs = 0;
    static bool file_create = true;

    // Check if data, time interval, or default header is empty
    if ((data == NULL) || (memcmp(&def_header, &empty_header, sizeof(SWavHeader)) == 0))
    {
        // Store error and log warning if any input data is invalid
        store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_APP_PROCESS_NULL_WAV_DATA);
        TRACE_WARNING("Any of the input data to process WAV files is not valid or declared");  
        memset(&wav, 0, sizeof(SWavData));
        return wav;
    }
    
    static char time_string[100];
    wav.file_create = file_create;
    if(record)
    {
        if (prev_start_secs != start_t)
        {
            // Generate WAV file name based on start time
            if(file_create)
            {
                sprintf(time_string, "%02d-%02d-%04d_%02d-%02d-%02d.wav", start_secs.year, start_secs.month, start_secs.day, start_secs.hour, start_secs.min, start_secs.sec);
                file_create = false;
            }
            // Create file path for WAV file
            sprintf(wav.file_path, "%s/%d/%s", WAV_FOLDER, wav_subfolder, time_string);
            wav.header = def_header;
            wav.data = (int16_t *)malloc(DATA_BUFFER_SIZE * sizeof(int16_t));

            for (size_t i = 0; i < DATA_BUFFER_SIZE; i++)
            {
                wav.data[i] = (int16_t)data[i]*10;
            }
            wav.average = 1;

        }
        else
        {
            wav.average = 0;
        }
    }
    else
    {
        file_create = true;
    }

    wav.record = record;

    prev_start_secs = start_t;

    return wav;
}

SCsvData process_analog_data_to_csv(SEnvData_t analog_env,int64_t start_t, bool record)
{
    SCsvData csv;
    STime_t start_secs = encode_time_to_date(start_t);
    static bool file_create = true;
    
    static char time_string[100];
    csv.file_create = file_create;
    if(record)
    {
        // Generate WAV file name based on start time
        if(file_create)
        {
            sprintf(time_string, "%02d-%02d-%04d_%02d-%02d-%02d_analog.csv", start_secs.year, start_secs.month, start_secs.day, start_secs.hour, start_secs.min, start_secs.sec);
            file_create = false;
        }
        // Create file path for WAV file
        sprintf(csv.file_path, "%s/%d/%s", WAV_FOLDER, wav_subfolder, time_string);
        snprintf(csv.header, CSV_HEADER_SIZE, "Time(s),Analog Data,Soil Moisture(Percentage),Direct Sunlight(Percentage),Ambient Light(Percentage)\n");
        snprintf(csv.data, CSV_ROW_SIZE, "%lld,%d,%u,%u,%u\n",(long long int)analog_env.instant_analog_time,(int)analog_env.plant_inst_data,analog_env.soil_moist,analog_env.sun,analog_env.light);

    }
    else
    {
        file_create = true;
    }

    csv.record = record;


    return csv;
}

SCsvData process_digital_data_to_csv(SEnvData_t digital_env,int64_t start_t, bool record)
{
    SCsvData csv;
    STime_t start_secs = encode_time_to_date(start_t);
    static bool file_create = true;
    
    static char time_string[100];
    csv.file_create = file_create;
    if(record)
    {
        // Generate WAV file name based on start time
        if(file_create)
        {
            sprintf(time_string, "%02d-%02d-%04d_%02d-%02d-%02d_digital.csv", start_secs.year, start_secs.month, start_secs.day, start_secs.hour, start_secs.min, start_secs.sec);
            file_create = false;
        }
        // Create file path for WAV file
        sprintf(csv.file_path, "%s/%d/%s", WAV_FOLDER, wav_subfolder, time_string);
        snprintf(csv.header, CSV_HEADER_SIZE, "Time(s),X Val(g),Y Val(g),Z Val(g),Temperature (Celsius), Air Moisture(Percentage)\n");
        snprintf(csv.data, CSV_ROW_SIZE, "%lld,%.2f,%.2f,%.2f,%.2f,%.2f\n",(long long int)digital_env.instant_digital_time,digital_env.x,digital_env.y,digital_env.z,digital_env.temp,digital_env.air_moist);

    }
    else
    {
        file_create = true;
    }

    csv.record = record;


    return csv;
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
        return MEM_MAYOR_FAULT;
    }
    else
    {
        // Return TASK_OK if no faults detected
        return MEM_TASK_OK;
    }
}