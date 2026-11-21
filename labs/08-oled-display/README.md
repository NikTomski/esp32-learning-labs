# Lab 08 - OLED Display (I2C)

## Overview

This lab demonstrates how to connect and control a 0.96-inch OLED display using the ESP32 and the I2C communication protocol.

The display uses the SSD1306 controller and has a resolution of 128x64 pixels.

The ESP32 initializes the I2C bus, communicates with the display, and renders text using a custom 5x7 pixel font. An uptime counter is refreshed every second.

## Components

- ESP32 DevKit
- 0.96-inch OLED display (SSD1306, 128x64)
- Breadboard
- Jumper wires

## Concepts

- I2C communication
- I2C master bus initialization
- SSD1306 display driver
- Framebuffer
- Pixel-based graphics
- Custom bitmap fonts
- Periodic updates using FreeRTOS

## Wiring

| OLED Display | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |

I2C address: `0x3C`

## How It Works

1. The ESP32 initializes the I2C master bus.
2. The SSD1306 display interface is configured.
3. A framebuffer is allocated to store pixel data.
4. Text is rendered using a custom 5x7 bitmap font.
5. The uptime counter is updated every second.
6. The framebuffer is transferred to the OLED display.

## Expected Result

The OLED display shows:

- ESP32
- LEARNING LABS
- OLED DISPLAY
- An uptime counter that updates every second

## Build and Flash

Activate the ESP-IDF environment:

```bash
source ~/.espressif/tools/activate_idf_v6.1.sh
```

Navigate to the project directory:

```bash
cd labs/08-oled-display
```

Build the project:

```bash
idf.py build
```

Flash the firmware and open the serial monitor:

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```