#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define BUZZER_GPIO GPIO_NUM_26

// Select buzzer type:
// 1 - Active buzzer
// 2 - Passive buzzer
#define BUZZER_TYPE 1

#define BUZZER_TIMER LEDC_TIMER_0
#define BUZZER_CHANNEL LEDC_CHANNEL_0

#define BUZZER_RESOLUTION LEDC_TIMER_10_BIT
#define BUZZER_DUTY 512

static const char *TAG = "BUZZER";

#if BUZZER_TYPE == 1

// Active buzzer

static void active_buzzer_init(void)
{
    ESP_LOGI(TAG, "Active buzzer initialization");

    gpio_reset_pin(BUZZER_GPIO);
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);
}

static void active_buzzer_run(void)
{
    while (1) {
        ESP_LOGI(TAG, "Buzzer ON");
        gpio_set_level(BUZZER_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "Buzzer OFF");
        gpio_set_level(BUZZER_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

#elif BUZZER_TYPE == 2

// Passive buzzer

typedef struct {
    uint32_t frequency;
    uint32_t duration;
} note_t;

static const note_t melody[] = {
    {262, 400},  // C4
    {294, 400},  // D4
    {330, 400},  // E4
    {349, 400},  // F4
    {392, 400},  // G4
    {440, 400},  // A4
    {494, 400},  // B4
    {523, 800},  // C5
};

static void passive_buzzer_init(void)
{
    ESP_LOGI(TAG, "Passive buzzer initialization");

    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = BUZZER_TIMER,
        .duty_resolution = BUZZER_RESOLUTION,
        .freq_hz = 2000,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    ledc_channel_config_t channel_config = {
        .gpio_num = BUZZER_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = BUZZER_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = BUZZER_TIMER,
        .duty = 0,
        .hpoint = 0,
    };

    ESP_ERROR_CHECK(ledc_channel_config(&channel_config));
}

static void play_note(uint32_t frequency, uint32_t duration)
{
    ledc_set_freq(
        LEDC_LOW_SPEED_MODE,
        BUZZER_TIMER,
        frequency
    );

    ledc_set_duty(
        LEDC_LOW_SPEED_MODE,
        BUZZER_CHANNEL,
        BUZZER_DUTY
    );

    ledc_update_duty(
        LEDC_LOW_SPEED_MODE,
        BUZZER_CHANNEL
    );

    vTaskDelay(pdMS_TO_TICKS(duration));

    ledc_set_duty(
        LEDC_LOW_SPEED_MODE,
        BUZZER_CHANNEL,
        0
    );

    ledc_update_duty(
        LEDC_LOW_SPEED_MODE,
        BUZZER_CHANNEL
    );

    vTaskDelay(pdMS_TO_TICKS(100));
}

static void passive_buzzer_run(void)
{
    while (1) {
        ESP_LOGI(TAG, "Playing melody");

        for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
            play_note(melody[i].frequency, melody[i].duration);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

#else
#error "Invalid BUZZER_TYPE. Use 1 for active or 2 for passive."
#endif

void app_main(void)
{
#if BUZZER_TYPE == 1
    active_buzzer_init();
    active_buzzer_run();
#elif BUZZER_TYPE == 2
    passive_buzzer_init();
    passive_buzzer_run();
#endif
}