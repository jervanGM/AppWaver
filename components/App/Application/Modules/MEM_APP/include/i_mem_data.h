#ifndef I_MEM_DATA_H_
#define I_MEM_DATA_H_
#include <stdint.h>
#include "safe_timer.h"
#include "common_t_data.h"
#include "CONSTANTS.h"

#define EXT_MEM_ERROR_SLOT 10
#define EXT_MEM_HANDLER_ID 6


#define HAL_MEM_CONFIG_ERROR -127
#define MEM_DRV_INIT_ERROR -126
#define MEM_DRV_DEINIT_ERROR -125

#define MEM_DRV_CREATE_DIR_ERROR -19
#define MEM_DRV_CREATE_FILE_ERROR -18
#define MEM_DRV_DELETE_FILE_ERROR -17
#define MEM_DRV_WRITE_FILE_ERROR -16
#define MEM_APP_PROCESS_NULL_WAV_DATA -15

#define MEM_DRV_OK 0

#define FILE_NAME_SIZE 200
#define CSV_HEADER_SIZE 200
#define CSV_ROW_SIZE 300

#define WAV_CHUNKS 16
#define WAV_CHANNELS 1
#define WAV_FORMAT 1
#define WAV_BITS 16
#define WAV_DEF_SRATE 10

#define WAV_FOLDER "/wave_data"
#define LOG_FOLDER "/logs"
#define ENVIRONMENT_FOLER "/env_data"
#define DEV_INFO_FILE "/device_info.txt"

extern int wav_subfolder;

typedef struct {
  char riff[4];           /* "RIFF"                                  */
  int32_t flength;        /* file length in bytes                    */
  char wave[4];           /* "WAVE"                                  */
  char fmt[4];            /* "fmt "                                  */
  int32_t chunk_size;     /* size of FMT chunk in bytes (usually 16) */
  int16_t format_tag;     /* 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM */
  int16_t num_chans;      /* 1=mono, 2=stereo                        */
  int32_t srate;          /* Sampling rate in samples per second     */
  int32_t bytes_per_sec;  /* bytes per second = srate*bytes_per_samp */
  int16_t bytes_per_samp; /* 2=16-bit mono, 4=16-bit stereo          */
  int16_t bits_per_samp;  /* Number of bits per sample               */
  char data[4];           /* "data"                                  */
  int32_t dlength;        /* data length in bytes (filelength - 44)  */
} SWavHeader;

typedef struct
{
    char file_path[FILE_NAME_SIZE];
    SWavHeader header;
    int16_t* data;
    uint32_t average;
    bool record;
    bool file_create;
} SWavData;

typedef struct
{
    char file_path[FILE_NAME_SIZE];
    char header[CSV_HEADER_SIZE];
    char data[CSV_ROW_SIZE];
    bool record;
    bool file_create;
} SCsvData;


typedef enum{
    MEM_TASK_OK,
    MEM_TASK_INIT_FAIL,
    MEM_TASK_SM_INIT_FAIL,
    MEM_MINOR_FAULT,
    MEM_MAYOR_FAULT
}EMemTaskStatus_t;

//Wireless to control task interfaces
typedef struct {
    uint8_t ID;
    EMemTaskStatus_t status;
    uint32_t delay;
    uint32_t LastWakeTime;
} SMemTaskInfo_t;

typedef struct{
    SMemTaskInfo_t _task_info;
}SMemCtrlMsg_t;

//Control to wireless task interface

typedef struct{
    SErrorInfo_t _alarm;
    SSystemStatus_t _status;
    SPPlantData_t _plant_signal;
    SEnvData_t _env_data;
    SPowerData_t _power_data;
    SAxisData_t _axis_buff;
    ESysMode_t _current_mode;
    ESysMode_t _previous_mode;
    int64_t _start_time;
    int64_t _end_time;
    int64_t _system_time;
}SCtrlMemMsg_t;

#endif /* I_MEM_DATA_H_ */