#ifndef SD_SPI_DRV_H_
#define SD_SPI_DRV_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "SERIES_ID.h"

/**
 * @brief Initialize the SD card over SPI bus.
 *
 * This function initializes the SPI bus and mounts the FAT filesystem on the SD card.
 *
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_init(void);

/**
 * @brief Write text data to a file on the SD card.
 *
 * @param path Path to the file to write.
 * @param data Null-terminated string to write to the file.
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_write_txt(const char *path, char *data);

/**
 * @brief Write binary data to a file on the SD card.
 *
 * @param path Path to the file to write.
 * @param data Pointer to the data buffer.
 * @param type_size Size of each element in bytes.
 * @param data_size Number of elements to write.
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_write_bin(const char* path, void* data, size_t type_size, size_t data_size);

/**
 * @brief Read text data from a file on the SD card.
 *
 * @param path Path to the file to read.
 * @param data Buffer to store the read data (null-terminated string).
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_read_file(const char *path, char *data);

/**
 * @brief Check if a file exists on the SD card.
 *
 * @param path Path to the file to check.
 * @return true if the file exists, false otherwise.
 */
bool sd_spi_file_exists(const char *path);

/**
 * @brief Create a directory on the SD card.
 *
 * @param path Path to the directory to create.
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_create_directory(const char *path);

/**
 * @brief Create an empty file on the SD card.
 *
 * @param path Path to the file to create.
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_create_file(const char *path);

/**
 * @brief Delete a file from the SD card.
 *
 * @param path Path to the file to delete.
 * @return 0 on success, 1 if file does not exist, -1 on failure.
 */
int8_t sd_spi_delete_file(const char *path);

/**
 * @brief Rename a file on the SD card.
 *
 * @param old_path Current path of the file.
 * @param new_path New path to rename the file to.
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_rename_file(const char *old_path, const char *new_path);

/**
 * @brief Format the SD card.
 *
 * This function formats the entire SD card, erasing all data.
 *
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_format(void);

/**
 * @brief Deinitialize the SD card and SPI bus.
 *
 * This function unmounts the SD card filesystem and frees the SPI bus resources.
 *
 * @return 0 on success, -1 on failure.
 */
int8_t sd_spi_deinit(void);

#endif /* SD_SPI_DRV_H_ */