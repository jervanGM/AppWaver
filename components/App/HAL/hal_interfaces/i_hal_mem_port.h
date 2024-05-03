#ifndef I_HAL_MEM_PORT_H_
#define I_HAL_MEM_PORT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int8_t (*init)  (void);
    int8_t (*file_txt_write)  (const char *path, char *data);
    int8_t (*file_bin_write)  (const char* path, void* data,size_t type_size, size_t data_size);
    int8_t (*file_read)  (const char *path, char *data);
    bool (*file_exists)  (const char *path);
    int8_t (*dir_create)  (const char *path);
    int8_t (*file_create)  (const char *path);
    int8_t (*file_delete)  (const char *path);
    int8_t (*file_rename)  (const char *old_path,const char *new_path);
    int8_t (*format)  (void);
    int8_t (*deinit)  (void);
} IMemPort;

#endif /* I_HAL_MEM_PORT_H_ */