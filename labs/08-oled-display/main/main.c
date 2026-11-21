#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_timer.h"

#define I2C_SDA_GPIO GPIO_NUM_21
#define I2C_SCL_GPIO GPIO_NUM_22
#define OLED_I2C_ADDRESS 0x3C

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

static const char *TAG = "OLED";

// Simple 5x7 font
static const uint8_t font[][5] = {
    {0x00,0x00,0x00,0x00,0x00}, // Space
    {0x00,0x00,0x5F,0x00,0x00}, // !
    {0x7E,0x11,0x11,0x11,0x7E}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
    {0x3E,0x41,0x41,0x41,0x22}, // C
    {0x7F,0x41,0x41,0x22,0x1C}, // D
    {0x7F,0x49,0x49,0x49,0x41}, // E
    {0x7F,0x09,0x09,0x09,0x01}, // F
    {0x3E,0x41,0x49,0x49,0x7A}, // G
    {0x7F,0x08,0x08,0x08,0x7F}, // H
    {0x00,0x41,0x7F,0x41,0x00}, // I
    {0x20,0x40,0x41,0x3F,0x01}, // J
    {0x7F,0x08,0x14,0x22,0x41}, // K
    {0x7F,0x40,0x40,0x40,0x40}, // L
    {0x7F,0x02,0x0C,0x02,0x7F}, // M
    {0x7F,0x04,0x08,0x10,0x7F}, // N
    {0x3E,0x41,0x41,0x41,0x3E}, // O
    {0x7F,0x09,0x09,0x09,0x06}, // P
    {0x3E,0x41,0x51,0x21,0x5E}, // Q
    {0x7F,0x09,0x19,0x29,0x46}, // R
    {0x46,0x49,0x49,0x49,0x31}, // S
    {0x01,0x01,0x7F,0x01,0x01}, // T
    {0x3F,0x40,0x40,0x40,0x3F}, // U
    {0x1F,0x20,0x40,0x20,0x1F}, // V
    {0x3F,0x40,0x38,0x40,0x3F}, // W
    {0x63,0x14,0x08,0x14,0x63}, // X
    {0x07,0x08,0x70,0x08,0x07}, // Y
    {0x61,0x51,0x49,0x45,0x43}, // Z
};

static uint8_t framebuffer[OLED_WIDTH * OLED_HEIGHT / 8];

static const uint8_t extra_font[][5] = {
    {0x3E,0x51,0x49,0x45,0x3E}, // 0
    {0x00,0x42,0x7F,0x40,0x00}, // 1
    {0x42,0x61,0x51,0x49,0x46}, // 2
    {0x21,0x41,0x45,0x4B,0x31}, // 3
    {0x18,0x14,0x12,0x7F,0x10}, // 4
    {0x27,0x45,0x45,0x45,0x39}, // 5
    {0x3C,0x4A,0x49,0x49,0x30}, // 6
    {0x01,0x71,0x09,0x05,0x03}, // 7
    {0x36,0x49,0x49,0x49,0x36}, // 8
    {0x06,0x49,0x49,0x29,0x1E}, // 9
    {0x00,0x36,0x36,0x00,0x00}, // :
};

static void draw_char(int x, int y, char c)
{
    const uint8_t *glyph = NULL;

    if (c == ' ') {
        return;
    } else if (c >= 'A' && c <= 'Z') {
        glyph = font[c - 'A' + 2];
    } else if (c >= '0' && c <= '9') {
        glyph = extra_font[c - '0'];
    } else if (c == ':') {
        glyph = extra_font[10];
    } else if (c == '!') {
        glyph = font[1];
    } else {
        return;
    }

    for (int col = 0; col < 5; col++) {
        uint8_t bits = glyph[col];

        for (int bit = 0; bit < 7; bit++) {
            if (bits & (1 << bit)) {
                int px = x + col;
                int py = y + bit;

                if (px >= 0 && px < OLED_WIDTH &&
                    py >= 0 && py < OLED_HEIGHT) {
                    framebuffer[px + (py / 8) * OLED_WIDTH] |=
                        1 << (py % 8);
                }
            }
        }
    }
}

void app_main(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = -1,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 4,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle = NULL;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    esp_lcd_panel_io_handle_t io_handle = NULL;

    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = OLED_I2C_ADDRESS,
        .scl_speed_hz = 100000,
        .control_phase_bytes = 1,
        .dc_bit_offset = 6,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_io_i2c(bus_handle, &io_config, &io_handle)
    );

    esp_lcd_panel_dev_config_t panel_config = {
        .bits_per_pixel = 1,
        .reset_gpio_num = GPIO_NUM_NC,
    };

    esp_lcd_panel_handle_t panel_handle = NULL;

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle)
    );

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "OLED initialized");
    while (1) {
        memset(framebuffer, 0, sizeof(framebuffer));

        // Draw text using the 5x7 font
        const char *lines[] = {
            "ESP32",
            "LEARNING LABS",
            "OLED DISPLAY"
        };

        for (int row = 0; row < 3; row++) {
            int x = 0;
            int y = row * 16;

            for (int i = 0; lines[row][i] != '\0'; i++) {
                draw_char(x, y, lines[row][i]);
                x += 7;
            }
        }
        // Draw uptime counter
        int seconds = esp_timer_get_time() / 1000000;
        char uptime[32];

        snprintf(uptime, sizeof(uptime), "UPTIME: %d SEC", seconds);

        int x = 0;
        int y = 52;

        for (int i = 0; uptime[i] != '\0' && x < OLED_WIDTH - 6; i++) {
            draw_char(x, y, uptime[i]);
            x += 7;
        }

        ESP_ERROR_CHECK(
            esp_lcd_panel_draw_bitmap(
                panel_handle,
                0, 0,
                OLED_WIDTH, OLED_HEIGHT,
                framebuffer
            )
        );

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}