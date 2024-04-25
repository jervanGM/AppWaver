#include "mem_port.h"
#include "sd_spi_drv.h"


/* Declarations of static functions */
static int8_t mem_port_init(void);
static int8_t mem_port_txt_file_write(const char *path, char *data);
static int8_t mem_port_bin_file_write(const char* path, void* data,size_t type_size, size_t data_size);
static int8_t mem_port_file_read(const char *path, char *data);
static bool mem_port_file_exists(const char *path);
static int8_t mem_port_dir_create(const char *path);
static int8_t mem_port_file_create(const char *path);
static int8_t mem_port_file_delete(const char *path);
static int8_t mem_port_file_rename(const char *old_path,const char *new_path);
static int8_t mem_port_format(void);
static int8_t mem_port_deinit(void);


/* Definition of the wireless port interface */
static const IMemPort mem_port_interface = {
    .init = mem_port_init,
    .file_txt_write = mem_port_txt_file_write,
    .file_bin_write = mem_port_bin_file_write,
    .file_read = mem_port_file_read,
    .file_exists = mem_port_file_exists,
    .dir_create = mem_port_dir_create,
    .file_create = mem_port_file_create,
    .file_delete = mem_port_file_delete,
    .file_rename = mem_port_file_rename,
    .format = mem_port_format,
    .deinit = mem_port_deinit
};

static int8_t mem_port_init(void)
{
    return sd_spi_init();
}

static int8_t mem_port_txt_file_write(const char *path, char *data)
{
    return sd_spi_write_txt(path,data);
}

static int8_t mem_port_bin_file_write(const char* path, void* data,size_t type_size, size_t data_size)
{
    return sd_spi_write_bin(path,data,type_size,data_size);
}

static int8_t mem_port_file_read(const char *path, char *data)
{
    return sd_spi_read_file(path,data);
}

static bool mem_port_file_exists(const char *path)
{
    return sd_spi_file_exists(path);
}

static int8_t mem_port_dir_create(const char *path)
{
    return sd_spi_create_directory(path);
}

static int8_t mem_port_file_create(const char *path)
{
    return sd_spi_create_file(path);
}

static int8_t mem_port_file_delete(const char *path)
{
    return sd_spi_delete_file(path);
}

static int8_t mem_port_file_rename(const char *old_path,const char *new_path)
{
    return sd_spi_rename_file(old_path,new_path);
}

static int8_t mem_port_format(void)
{
    return sd_spi_format();
}

static int8_t mem_port_deinit(void)
{
    return sd_spi_deinit();
}

/* Function to retrieve the wireless port interface */
const IMemPort *hal_ext_mem_get_port(void)
{
    const IMemPort *port = &mem_port_interface;  // Pointer to the wireless port interface

    /* Check if all members of the structure pointed by 'port' are initialized */
    if (port->init != NULL &&
        port->file_txt_write != NULL &&
        port->file_bin_write != NULL &&
        port->file_read != NULL &&
        port->file_exists != NULL &&
        port->file_create != NULL &&
        port->file_delete != NULL &&
        port->file_rename != NULL &&
        port->format != NULL &&
        port->deinit != NULL) {
        // The structure is not empty, return the pointer
        return port;
    } else {
        // The structure is empty or not all members are initialized, return NULL
        return NULL;
    }
}