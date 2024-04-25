#ifndef SD_SPI_DRV_H_
#define SD_SPI_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"

int8_t sd_spi_init(void);

int8_t sd_spi_write_txt(const char *path, char *data);

int8_t sd_spi_write_bin(const char* path, void* data,size_t type_size, size_t data_size);

int8_t sd_spi_read_file(const char *path, char *data);

bool sd_spi_file_exists(const char *path);

int8_t sd_spi_create_directory(const char *path);

int8_t sd_spi_create_file(const char *path);

int8_t sd_spi_delete_file(const char *path);

int8_t sd_spi_rename_file(const char *old_path,const char *new_path);

int8_t sd_spi_format(void);

int8_t sd_spi_deinit(void);

#endif /* SD_SPI_DRV_H_ */