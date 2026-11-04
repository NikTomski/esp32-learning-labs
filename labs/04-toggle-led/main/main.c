#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO    GPIO_NUM_25
#define BUTTON_GPIO GPIO_NUM_27

void app_main(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY);

    int led_state = 0;
    int last_button_state = 1;

    while (1) {
        int button_state = gpio_get_level(BUTTON_GPIO);

        if (last_button_state == 1 && button_state == 0) {
            led_state = !led_state;
            gpio_set_level(LED_GPIO, led_state);
        }

        last_button_state = button_state;

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}