#include "mem_drv.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "mem_port.h"
#include <string.h>

static const IMemPort *mem_port;
int wav_subfolder = 0;

void mem_drv_init()
{
    mem_port = hal_ext_mem_get_port();
    if(mem_port != NULL)
    {
        if(mem_port->init() != MEM_DRV_OK)
        {
            store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_INIT_ERROR);
            TRACE_ERROR("An external memory task error has been produced during initialization");
            return; 
        }
        else
        {
            int max_path_length = sizeof(WAV_FOLDER) + 30;
            char full_path[max_path_length];

            if(!mem_port->file_exists(WAV_FOLDER))
            {
                if(mem_port->dir_create(WAV_FOLDER)!= MEM_DRV_OK)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_DIR_ERROR);
                    TRACE_WARNING(WAV_FOLDER,"directory cannot be created");
                }
            }
            do{
                wav_subfolder++;
                sprintf(full_path, "%s/%d" , WAV_FOLDER, wav_subfolder);
            }while(mem_port->file_exists(full_path));
            
            if(mem_port->dir_create(full_path)!= MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_DIR_ERROR);
                TRACE_WARNING(full_path,"directory cannot be created");
            }

            if(mem_port->file_exists(DEV_INFO_FILE))
            {
                if(mem_port->file_delete(DEV_INFO_FILE) == 1)
                {
                    store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_DELETE_FILE_ERROR);
                    TRACE_WARNING(full_path,"directory cannot be created");  
                }
            }
            if(mem_port->file_create(DEV_INFO_FILE) != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_FILE_ERROR);
                TRACE_WARNING(DEV_INFO_FILE,"file cannot be created");  
            }
            if(mem_port->file_txt_write(DEV_INFO_FILE,"FW VERSION:1.0.0") != MEM_DRV_OK)
            {
                store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
                TRACE_WARNING(DEV_INFO_FILE,"file cannot be written");  
            }
        }
    }
    else{
        store_error_in_slot(EXT_MEM_ERROR_SLOT,HAL_MEM_CONFIG_ERROR);
        TRACE_ERROR("External memory HAL port has not been configured correctly on init");
    }

}

void save_wav_data(SWavData wav)
{
    
    if(!mem_port->file_exists(wav.file_path))
    {
        if(mem_port->file_create(wav.file_path) != MEM_DRV_OK)
        {
            store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_CREATE_FILE_ERROR);
            TRACE_WARNING(wav.file_path,"file cannot be created");  
            return;
        }
        if((mem_port->file_bin_write(wav.file_path,&wav.header,sizeof(char),sizeof(SWavHeader)) != MEM_DRV_OK) ||
            (mem_port->file_bin_write(wav.file_path,wav.data,sizeof(int16_t),DATA_BUFFER_SIZE)))
        {
            store_error_in_slot(EXT_MEM_ERROR_SLOT, MEM_DRV_WRITE_FILE_ERROR);
            TRACE_WARNING(wav.file_path,"file cannot be written correctly");  
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
