#include "mem_drv.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "mem_port.h"
#include <string.h>

static const IMemPort *mem_port;
int wav_subfolder = 0;

void mem_drv_init()
{
    mem_port = hal_ext_mem_get_port(); ///< Get memory port interface.

    if (mem_port != NULL)
    {
        // Initialize the memory port
        if (mem_port->init() != MEM_DRV_OK)
        {
            store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_INIT_ERROR);
            TRACE_ERROR("An external memory task error occurred during initialization");
            return; ///< Exit function.
        }
        else
        {
            int max_path_length = sizeof(WAV_FOLDER) + 30;
            char full_path[max_path_length];

            // Create WAV folder if it doesn't exist
            if (!mem_port->file_exists(WAV_FOLDER))
            {
                if (mem_port->dir_create(WAV_FOLDER) != MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_DIR_ERROR);
                    TRACE_WARNING(WAV_FOLDER, "directory cannot be created");
                }
            }

            // Find a non-existing subfolder number for WAV files
            do {
                wav_subfolder++;
                sprintf(full_path, "%s/%d", WAV_FOLDER, wav_subfolder);
            } while (mem_port->file_exists(full_path));

            // Create subfolder for WAV files
            if (mem_port->dir_create(full_path) != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_DIR_ERROR);
                TRACE_WARNING(full_path, "directory cannot be created");
            }

            // Delete existing device info file if present
            if (mem_port->file_exists(DEV_INFO_FILE))
            {
                if (mem_port->file_delete(DEV_INFO_FILE) == 1)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_DELETE_FILE_ERROR);
                    TRACE_WARNING(full_path, "directory cannot be created");
                }
            }

            // Create device info file
            if (mem_port->file_create(DEV_INFO_FILE) != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_FILE_ERROR);
                TRACE_WARNING(DEV_INFO_FILE, "file cannot be created");
            }

            // Write firmware version to device info file
            if (mem_port->file_txt_write(DEV_INFO_FILE, "FW VERSION:2.1.0") != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                TRACE_WARNING(DEV_INFO_FILE, "file cannot be written");
            }
        }
    }
    else
    {
        store_error_in_slot(EXT_MEM_ERROR_SLOT, HAL_MEM_CONFIG_ERROR);
        TRACE_ERROR("External memory HAL port has not been configured correctly on init");
    }
}

void save_wav_data(SWavData wav)
{

        if(wav.record)
        {
            // Write WAV header and data to file
            if(wav.file_create)
            {
                // Create WAV file if it doesn't exist
                if (mem_port->file_create(wav.file_path) != MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_FILE_ERROR);
                    TRACE_WARNING(wav.file_path, "file cannot be created");
                    return; ///< Exit function.
                }
                if (mem_port->file_bin_write(wav.file_path, &wav.header, sizeof(char), sizeof(SWavHeader)) != MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                    TRACE_WARNING(wav.file_path, "file cannot be written correctly");
                }
            }
            if (mem_port->file_bin_write(wav.file_path, wav.data, sizeof(int16_t), DATA_BUFFER_SIZE) != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                TRACE_WARNING(wav.file_path, "file cannot be written correctly");
            }
        }

}

void save_csv_data(SCsvData csv)
{

        if(csv.record)
        {
            // Write WAV header and data to file
            if(csv.file_create)
            {
                // Create WAV file if it doesn't exist
                if (mem_port->file_create(csv.file_path) != MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_FILE_ERROR);
                    TRACE_WARNING(csv.file_path, "file cannot be created");
                    return; ///< Exit function.
                }
                if (mem_port->file_txt_write(csv.file_path, csv.header) != MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                    TRACE_WARNING(csv.file_path, "file cannot be written correctly");
                }
            }
            if (mem_port->file_txt_write(csv.file_path, csv.data) != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                TRACE_WARNING(csv.file_path, "file cannot be written correctly");
            }
        }

}

void mem_drv_deinit()
{
    if(mem_port->deinit() != MEM_DRV_OK)
    {
        store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_DEINIT_ERROR);
        TRACE_ERROR("An external memory task error has been produced during deinitialization");
    }  
}
