
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"

#define LED_GPIO        GPIO_NUM_25

#define ADC_UNIT        ADC_UNIT_1
#define ADC_CHANNEL     ADC_CHANNEL_6
#define ADC_ATTEN       ADC_ATTEN_DB_12

#define LEDC_MODE       LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_DUTY_RES   LEDC_TIMER_13_BIT
#define LEDC_FREQUENCY  5000

#define ADC_MAX_VALUE   4095
#define MAX_DUTY        8191

void app_main(void)
{
    // Configure ADC
    adc_oneshot_unit_handle_t adc_handle;

    adc_oneshot_unit_init_cfg_t adc_init_config = {
        .unit_id = ADC_UNIT
    };

    ESP_ERROR_CHECK(
        adc_oneshot_new_unit(&adc_init_config, &adc_handle)
    );

    adc_oneshot_chan_cfg_t adc_channel_config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN
    };

    ESP_ERROR_CHECK(
        adc_oneshot_config_channel(
            adc_handle,
            ADC_CHANNEL,
            &adc_channel_config
        )
    );

    // Configure LEDC timer
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    // Configure LEDC channel
    ledc_channel_config_t channel_config = {
        .gpio_num = LED_GPIO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };

    ESP_ERROR_CHECK(ledc_channel_config(&channel_config));

    // Read potentiometer and control LED brightness
    while (1) {
        int adc_value = 0;

        ESP_ERROR_CHECK(
            adc_oneshot_read(
                adc_handle,
                ADC_CHANNEL,
                &adc_value
            )
        );

        int duty = (adc_value * MAX_DUTY) / ADC_MAX_VALUE;

        ESP_ERROR_CHECK(
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty)
        );

        ESP_ERROR_CHECK(
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL)
        );

        printf("ADC: %d | PWM Duty: %d\n", adc_value, duty);

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
