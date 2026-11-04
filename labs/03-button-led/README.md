# Lab 03 — Button + LED

## Overview

This project demonstrates how to read a button input and control an external LED using the ESP32 GPIO pins.

The LED turns on while the button is pressed and turns off when the button is released.

## Components

- ESP32 DevKit
- LED
- 220Ω resistor
- Tactile push button
- Breadboard
- Jumper wires
- USB cable

## Wiring

| Component | ESP32 |
|---|---|
| LED anode (long leg) | GPIO25 through 220Ω resistor |
| LED cathode (short leg) | GND |
| Button terminal 1 | GPIO27 |
| Button terminal 2 | GND |

The button uses the ESP32 internal pull-up resistor.

## Demo

![LED lights up when the button is pressed](images/03-button-led.gif)

## Concepts

- GPIO input and output configuration
- Internal pull-up resistors
- Reading digital input with `gpio_get_level()`
- Button state detection
- Active-low logic
- Basic input polling
- FreeRTOS task delays
- `vTaskDelay()`
- `pdMS_TO_TICKS()`

## Build and Flash

Activate the ESP-IDF environment:

```
source ~/.espressif/tools/activate_idf_v6.1.sh
```

Navigate to the project directory:

```
cd labs/03-button-led
```

Build the project:

```
idf.py build
```

Flash the firmware and open the serial monitor:

```
idf.py flash monitor
```

## Expected Result

- Pressing the button turns the LED on.
- Releasing the button turns the LED off.
- The ESP32 continuously reads the button state while the program is running.