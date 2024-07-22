#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "sd_spi_drv.h"

static const char *TAG = "SD SPI DRV";

#define MOUNT_POINT "/sdcard"

sdmmc_card_t *card;
const char mount_point[] = MOUNT_POINT;

static sdmmc_host_t spi_host;

// Pin assignments can be set in menuconfig, see "SD SPI Example Configuration" menu.
// You can also change the pin assignments here by changing the following 4 lines.
#ifdef BASIC
#define PIN_NUM_MISO  5
#define PIN_NUM_MOSI  6
#define PIN_NUM_CLK   4
#define PIN_NUM_CS    7
#endif

#ifdef ADVANCED
#define PIN_NUM_MISO  20
#define PIN_NUM_MOSI  22
#define PIN_NUM_CLK   19
#define PIN_NUM_CS    21
#endif

int8_t sd_spi_init(void)
{
    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = true,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    ESP_LOGI(TAG, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    ESP_LOGI(TAG, "Using SPI peripheral");

    // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
    // For setting a specific frequency, use spi_host.max_freq_khz (range 400kHz - 20MHz for SDSPI)
    // Example: for fixed frequency of 10MHz, use spi_host.max_freq_khz = 10000;
    sdmmc_host_t temp_spi_host = SDSPI_HOST_DEFAULT();
    memcpy(&spi_host, &temp_spi_host, sizeof(sdmmc_host_t));

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(spi_host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return -1;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = spi_host.slot;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &spi_host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return -1;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    return 0;

}

int8_t sd_spi_write_txt(const char *path, char *data)
{
    // Construct full file path
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Open file in append mode
    ESP_LOGI(TAG, "Opening file %s", file_path);
    FILE *f = fopen(file_path, "a");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return -1;
    }

    // Write data to file
    fprintf(f, data);

    // Close file
    fclose(f);

    return 0;
}

int8_t sd_spi_write_bin(const char* path, void* data, size_t type_size, size_t data_size)
{
    // Construct full file path
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Open file in append binary mode
    ESP_LOGI(TAG, "Opening file %s", file_path);
    FILE* f = fopen(file_path, "ab");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return -1;
    }

    // Write binary data to file
    fwrite(data, type_size, data_size, f);

    // Close file
    fclose(f);

    // Log success message
    ESP_LOGI(TAG, "Data has been appended to the file");
    return 0;
}

int8_t sd_spi_read_file(const char *path, char *data)
{
    // Construct full file path
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Open file in read mode
    ESP_LOGI(TAG, "Reading file %s", file_path);
    FILE *f = fopen(file_path, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return -1;
    }

    // Read data from file
    fgets(data, sizeof(data), f);

    // Close file
    fclose(f);

    // Strip newline character if present
    char *pos = strchr(data, '\n');
    if (pos) {
        *pos = '\0';
    }

    // Log read data
    ESP_LOGI(TAG, "Read from file: '%s'", data);

    return 0;
}

bool sd_spi_file_exists(const char *path)
{
    // Construct full file path
    struct stat st;
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Check file existence
    if (stat(file_path, &st) == 0) {
        return true;
    }
    return false;
}

int8_t sd_spi_create_directory(const char *path)
{
    // Construct full directory path
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Attempt to create directory
    if (mkdir(file_path, 0777) != 0) {
        return -1;
    }

    return 0;  
}

int8_t sd_spi_create_file(const char *path)
{
    // Construct full file path
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Create empty file
    FILE* archivo = fopen(file_path, "w");
    if (archivo == NULL) {
        return -1;
    }
    fclose(archivo);

    return 0;  
}

int8_t sd_spi_delete_file(const char *path)
{
    // Construct full file path
    struct stat st;
    char file_path[strlen(path) + strlen(MOUNT_POINT) + 1];
    snprintf(file_path, sizeof(file_path), "%s%s", MOUNT_POINT, path);

    // Check if file exists
    if (stat(file_path, &st) == 0) {
        // Delete file if it exists
        return unlink(file_path);
    }    
    return 1; // File does not exist
}

int8_t sd_spi_rename_file(const char *old_path,const char *new_path)
{
    if (rename(old_path, new_path) != 0) {
        return -1;
    }
    return 0;
}

int8_t sd_spi_format(void)
{
    if (esp_vfs_fat_sdcard_format(mount_point, card) != ESP_OK) {
        return -1;
    }
    return 0;
}

int8_t sd_spi_deinit(void)
{
    // All done, unmount partition and disable SPI peripheral
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Card unmounted");

    //deinitialize the bus after all devices are removed
    if(spi_bus_free(spi_host.slot)!=ESP_OK)
    {
        return -1;
    }
    return 0;
}