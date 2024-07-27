#include "mem_port.h"
#include "sd_spi_drv.h"

/* Declarations of static functions */
static int8_t ext_mem_port_init(void); // Initializes the external memory port using SD SPI driver
static int8_t ext_mem_port_txt_file_write(const char *path, char *data); // Writes text data to a file on the external memory
static int8_t ext_mem_port_bin_file_write(const char* path, void* data, size_t type_size, size_t data_size); // Writes binary data to a file on the external memory
static int8_t ext_mem_port_bin_file_update(const char* path, void* data, size_t type_size, size_t data_size, size_t offset);
static int8_t ext_mem_port_file_read(const char *path, char *data); // Reads a file from the external memory
static bool ext_mem_port_file_exists(const char *path); // Checks if a file exists in the external memory
static int8_t ext_mem_port_dir_create(const char *path); // Creates a directory in the external memory
static int8_t ext_mem_port_file_create(const char *path); // Creates a file in the external memory
static int8_t ext_mem_port_file_delete(const char *path); // Deletes a file from the external memory
static int8_t ext_mem_port_file_rename(const char *old_path, const char *new_path); // Renames a file in the external memory
static int8_t ext_mem_port_format(void); // Formats the external memory
static int8_t ext_mem_port_deinit(void); // Deinitializes the external memory port

/* Definition of the external memory port interface */
static const IMemPort ext_mem_port_interface = {
    .init = ext_mem_port_init,
    .file_txt_write = ext_mem_port_txt_file_write,
    .file_bin_write = ext_mem_port_bin_file_write,
    .file_bin_update = ext_mem_port_bin_file_update,
    .file_read = ext_mem_port_file_read,
    .file_exists = ext_mem_port_file_exists,
    .dir_create = ext_mem_port_dir_create,
    .file_create = ext_mem_port_file_create,
    .file_delete = ext_mem_port_file_delete,
    .file_rename = ext_mem_port_file_rename,
    .format = ext_mem_port_format,
    .deinit = ext_mem_port_deinit
};

// Initializes the external memory port using SD SPI driver
static int8_t ext_mem_port_init(void)
{
    return sd_spi_init();
}

// Writes text data to a file on the external memory
static int8_t ext_mem_port_txt_file_write(const char *path, char *data)
{
    return sd_spi_write_txt(path, data);
}

// Writes binary data to a file on the external memory
static int8_t ext_mem_port_bin_file_write(const char* path, void* data, size_t type_size, size_t data_size)
{
    return sd_spi_write_bin(path, data, type_size, data_size);
}

static int8_t ext_mem_port_bin_file_update(const char* path, void* data, size_t type_size, size_t data_size, size_t offset)
{
    return sd_spi_update_bin(path, data, type_size, data_size, offset);
}

// Reads a file from the external memory
static int8_t ext_mem_port_file_read(const char *path, char *data)
{
    return sd_spi_read_file(path, data);
}

// Checks if a file exists in the external memory
static bool ext_mem_port_file_exists(const char *path)
{
    return sd_spi_file_exists(path);
}

// Creates a directory in the external memory
static int8_t ext_mem_port_dir_create(const char *path)
{
    return sd_spi_create_directory(path);
}

// Creates a file in the external memory
static int8_t ext_mem_port_file_create(const char *path)
{
    return sd_spi_create_file(path);
}

// Deletes a file from the external memory
static int8_t ext_mem_port_file_delete(const char *path)
{
    return sd_spi_delete_file(path);
}

// Renames a file in the external memory
static int8_t ext_mem_port_file_rename(const char *old_path, const char *new_path)
{
    return sd_spi_rename_file(old_path, new_path);
}

// Formats the external memory
static int8_t ext_mem_port_format(void)
{
    return sd_spi_format();
}

// Deinitializes the external memory port
static int8_t ext_mem_port_deinit(void)
{
    return sd_spi_deinit();
}

/* Function to retrieve the external memory port interface */
const IMemPort *hal_ext_mem_get_port(void)
{
    const IMemPort *port = &ext_mem_port_interface;  // Pointer to the external memory port interface

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
