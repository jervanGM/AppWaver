#ifndef I_HAL_MEM_PORT_H_
#define I_HAL_MEM_PORT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Hardware Abstraction Layer (HAL) Interface for Memory Port operations.
 * 
 * This interface defines functions for interacting with memory and file system operations
 * in a hardware-independent manner.
 */
typedef struct {
    int8_t (*init)(void); /**< Function pointer to initialize the memory port. */
    int8_t (*file_txt_write)(const char *path, char *data); /**< Function pointer to write text data to a file. */
    int8_t (*file_bin_write)(const char* path, void* data, size_t type_size, size_t data_size); /**< Function pointer to write binary data to a file. */
    int8_t (*file_bin_update)(const char* path, void* data, size_t type_size, size_t data_size, size_t offset);
    int8_t (*file_read)(const char *path, char *data); /**< Function pointer to read data from a file. */
    bool (*file_exists)(const char *path); /**< Function pointer to check if a file exists. */
    int8_t (*dir_create)(const char *path); /**< Function pointer to create a directory. */
    int8_t (*file_create)(const char *path); /**< Function pointer to create a file. */
    int8_t (*file_delete)(const char *path); /**< Function pointer to delete a file. */
    int8_t (*file_rename)(const char *old_path, const char *new_path); /**< Function pointer to rename a file. */
    int8_t (*format)(void); /**< Function pointer to format the memory. */
    int8_t (*deinit)(void); /**< Function pointer to deinitialize the memory port. */
} IMemPort;

#endif /* I_HAL_MEM_PORT_H_ */
