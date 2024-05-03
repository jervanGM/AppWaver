#include "ota_drv.h"
#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <esp_system.h>
#include <esp_log.h>


static const char *TAG = "OTA";
esp_ota_handle_t update_handle;
const esp_partition_t *update_partition;

void ota_update_reboot()
{
    esp_restart();
}

int8_t ota_init()
{
    assert(!update_partition);

    update_partition = esp_ota_get_next_update_partition(NULL);
    if (!update_partition) {
        ESP_LOGE(TAG,"Cannot obtain update partition");
        return -1;
    }

    if (esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN,
                      &update_handle)) {
        ESP_LOGE(TAG,"OTA begin failed");
        update_partition = NULL;
        return -1;
    }
    return 0;
}

int8_t ota_update_install()
{
    const esp_partition_t *partition = esp_ota_get_running_partition();
    esp_ota_img_states_t partition_state;
    esp_ota_get_state_partition(partition, &partition_state);

    if (partition_state == ESP_OTA_IMG_UNDEFINED
            || partition_state == ESP_OTA_IMG_PENDING_VERIFY) {
        ESP_LOGI(TAG,"First boot from partition with new firmware");
        esp_ota_mark_app_valid_cancel_rollback();
        return 0;
    }
    return -1;
}

int8_t ota_write(const void *data, size_t length)
{
    assert(update_partition);

    int result = esp_ota_write(update_handle, data, length);
    if (result) {
        ESP_LOGE(TAG,"OTA write failed");
        return -1;
    }
    return 0;
}

int8_t ota_upgrade()
{
    int result = esp_ota_set_boot_partition(update_partition);
    if (result) {
        update_partition = NULL;
        return -1;
    }
    return 0;
}

void ota_abort()
{
    if (update_partition) {
        esp_ota_abort(update_handle);
        update_partition = NULL;
    }
}

int8_t ota_end()
{
    assert(update_partition);

    int result = esp_ota_end(update_handle);
    if (result) {
        ESP_LOGE(TAG,"OTA end failed");
        update_partition = NULL;
        return -1;
    }
    return 0;
}