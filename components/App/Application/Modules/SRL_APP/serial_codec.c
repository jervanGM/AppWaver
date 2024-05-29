#include "serial_codec.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "srl_port.h"

static const ISrlPort *srl_port;

/* Initializes the serial module */
void serial_init()
{
    srl_port = hal_srl_get_port();

    
    if (srl_port != NULL)
    {
        if(srl_port->init() != SRL_DRV_OK)
        {
            store_error_in_slot(SERIAL_ERROR_SLOT, SRL_DRV_INIT_ERROR);
            TRACE_ERROR("A serial task error has been produced during initialization");
            return;   
        } 
    }
    else
    {
        store_error_in_slot(SERIAL_ERROR_SLOT, HAL_SRL_CONFIG_ERROR);
        TRACE_ERROR("Serial HAL port has not been configured correctly on init");
    }
}

bool serial_connected()
{
    if (srl_port != NULL)
    {
        return srl_port->is_connected();
    }
    else
    {
        store_error_in_slot(SERIAL_ERROR_SLOT, SRL_DRV_ON_CONNECTED_FATAL_ERROR);
        TRACE_ERROR("Unexpected error on serial is connected due to port initialization error");
    }
    return false;
}

static void extract_between_slashes(const char *buff, size_t size) {
    const char *start_ptr = strstr(buff, "/");
    if (start_ptr != NULL) {
        // Avanzamos al siguiente caracter después de '/'
        start_ptr++;

        const char *end_ptr = strstr(start_ptr, "/");
        if (end_ptr != NULL) {
            size_t length = end_ptr - start_ptr;

            if (length < size) {
                // Creamos una copia del texto entre las barras
                char temp[length + 1]; // +1 para el carácter nulo
                strncpy(temp, start_ptr, length);
                temp[length] = '\0'; // Aseguramos que la cadena termine con el carácter nulo

                // Copiamos la cadena temporal de vuelta al buffer original solo si el tamaño es suficiente
                if (length < size) {
                    strcpy(buff, temp);
                }
            }
        }
    }
}

SSerialCmd_t serial_process_cmd() {
    SSerialCmd_t srl_cmd;
    size_t cmd_size = sizeof(srl_cmd.cmd);

    if (srl_port != NULL) {
        uint8_t data[cmd_size];
        srl_port->read_cmd(data, cmd_size);
        
        if (data[0] == '/' && data[1] == '\0') {
            strcpy(srl_cmd.cmd, "");
            srl_cmd.force = false;
        } else {

            if (cmd_size >= strlen((char *)data) + 1) {
                memcpy(srl_cmd.cmd, data, strlen((char *)data) + 1);
                extract_between_slashes(srl_cmd.cmd, cmd_size);
                
                char *force_ptr = strstr(srl_cmd.cmd, " --force");
                if (force_ptr != NULL) {
                    
                    srl_cmd.force = true;
                    *force_ptr = '\0';
                } else {
                    srl_cmd.force = false;
                }
            } else {
                
                store_error_in_slot(SERIAL_ERROR_SLOT, SRL_DRV_CMD_BUFFER_OVERFLOW);
                TRACE_ERROR("Command buffer overflow detected.");
                memset(&srl_cmd, 0, sizeof(srl_cmd));
            }
        }
    } else {

        store_error_in_slot(SERIAL_ERROR_SLOT, SRL_DRV_ON_READ_FATAL_ERROR);
        TRACE_ERROR("Unexpected error on serial process command due to port initialization error");
        memset(&srl_cmd, 0, sizeof(srl_cmd));
    }

    return srl_cmd;
}



void serial_deinit()
{
    if (srl_port != NULL)
    {
        if(srl_port->deinit() != SRL_DRV_OK)
        {
            TRACE_ERROR("A serial task error has been produced during deinitialization");
            return;   
        } 
    }
    else
    {
        TRACE_ERROR("Unexpected error on serial deinit due to port initialization error");
    }
}