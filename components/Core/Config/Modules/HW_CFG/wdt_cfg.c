#include <esp_task_wdt.h>

esp_task_wdt_config_t wdt_config;

void set_wdt_disable()
{
    wdt_config.timeout_ms = 30000;
    wdt_config.trigger_panic = false;
    esp_task_wdt_init(&wdt_config);
}

void set_wdt_enable()
{
    wdt_config.trigger_panic = true;
    esp_task_wdt_init(&wdt_config);
}