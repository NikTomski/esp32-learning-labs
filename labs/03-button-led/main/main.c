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

    while (1) {
        int button_pressed = (gpio_get_level(BUTTON_GPIO) == 0);

        gpio_set_level(LED_GPIO, button_pressed);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}