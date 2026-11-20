
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#include "dht.h"

#define DHT_GPIO GPIO_NUM_4

static const char *TAG = "DHT11";

void app_main(void)
{
    ESP_LOGI(TAG, "DHT11 sensor initialization");

    while (1) {
        float temperature = 0;
        float humidity = 0;

        esp_err_t result = dht_read_float_data(
            DHT_TYPE_DHT11,
            DHT_GPIO,
            &humidity,
            &temperature
        );

        if (result == ESP_OK) {
            ESP_LOGI(TAG, "Temperature: %.1f C", temperature);
            ESP_LOGI(TAG, "Humidity: %.1f %%", humidity);
        } else {
            ESP_LOGE(TAG, "Failed to read DHT11: %s",
                     esp_err_to_name(result));
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
