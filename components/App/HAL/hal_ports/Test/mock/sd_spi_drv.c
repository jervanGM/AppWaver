#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "sd_spi_drv.h"

#define MOUNT_POINT ".\\sdcard" // Directory test root

static int _init_error = 0;
static int _write_bin_error = 0;
static int _write_txt_error = 0;
static int _read_error = 0;
static int _create_dir_error = 0;
static int _create_file_error = 0;
static int _delete_file_error = 1;
static int _rename_file_error = 0;
static int _format_error = 0;
static int _deinit_error = 0;

void mock_drv_errors(
int init_error,int write_bin_error,int write_txt_error,
int read_error,int create_dir_error,int create_file_error,
int delete_file_error,int rename_file_error,int format_error,
int deinit_error)
{
    _init_error = init_error;
    _write_bin_error = write_bin_error;
    _write_txt_error = write_txt_error;
    _read_error = read_error;
    _create_dir_error = create_dir_error;
    _create_file_error = create_file_error;
    _delete_file_error = delete_file_error;
    _rename_file_error = rename_file_error;
    _format_error = format_error;
    _deinit_error = deinit_error;
}

int8_t sd_spi_init(void)
{
    return _init_error;
}

int8_t sd_spi_write_txt(const char *path, char *data)
{
    if(!_write_txt_error)
    {
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);
        printf("Opening file %s\n", file_path);
        FILE *f = fopen(file_path, "a");
        if (f == NULL) {
            printf("Failed to open file for writing\n");
            return -1;
        }
        fprintf(f, data);
        fclose(f);
    }
    return _write_txt_error;
}

int8_t sd_spi_write_bin(const char* path, void* data, size_t type_size, size_t data_size)
{
    if(!_write_bin_error)
    {
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);
        printf("Opening file %s\n", file_path);
        FILE* f = fopen(file_path, "ab");
        if (f == NULL) {
            printf("Failed to open file for writing\n");
            return -1;
        }

        fwrite(data, type_size, data_size, f);

        fclose(f);

        printf("Data has been appended to the file\n");
    }

    return _write_bin_error;
}

int8_t sd_spi_read_file(const char *path, char *data)
{
    if(!_read_error)
    {
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);
        printf("Reading file %s\n", file_path);
        FILE *f = fopen(file_path, "r");
        if (f == NULL) {
            printf("Failed to open file for reading\n");
            return -1;
        }

        fgets(data, sizeof(data), f);
        fclose(f);

        // strip newline
        char *pos = strchr(data, '\n');
        if (pos) {
            *pos = '\0';
        }
        printf("Read from file: '%s'\n", data);
    }
    return _read_error;
}

bool sd_spi_file_exists(const char *path)
{
    struct stat st;
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);
    if (stat(file_path, &st) == 0) {
        return true;
    }
    return false;
}

int8_t sd_spi_create_directory(const char *path)
{
    if(!_create_dir_error)
    {
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

        if (mkdir(file_path, 0777) != 0) 
        {
            return -1;
        }
    }

    return _create_dir_error;  
}

int8_t sd_spi_create_file(const char *path)
{
    if(!_create_file_error)
    {
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

        FILE* archivo = fopen(file_path, "w");
        if (archivo == NULL) {
            return -1;
        }
        fclose(archivo);
    }

    return _create_file_error;  
}

int8_t sd_spi_delete_file(const char *path)
{
    if(_delete_file_error)
    {
        struct stat st;
        char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
        snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);
        if (stat(file_path, &st) == 0) {
            // Delete it if it exists
            return unlink(file_path);
        }           
    }
 
    return _delete_file_error;
}

int8_t sd_spi_rename_file(const char *old_path,const char *new_path)
{
    if(!_rename_file_error)
    {
        if (rename(old_path, new_path) != 0) {
            return -1;
        }
    }

    return _rename_file_error;
}

int8_t sd_spi_format(void)
{
    return _format_error;
}

int8_t sd_spi_deinit(void)
{
    return _deinit_error;
}
