# Lab 02 — LED Blink

## Overview

This project demonstrates how to blink an external LED using an ESP32 GPIO output.

The LED repeatedly turns on and off with a 500 ms delay between state changes.

## Components

- ESP32 DevKit
- LED
- 220Ω resistor
- Breadboard
- Jumper wires
- USB cable

## Wiring

| LED Component | ESP32 |
|---|---|
| Anode (long leg) | GPIO25 through 220Ω resistor |
| Cathode (short leg) | GND |

## Demo

![LED blinking demonstration](images/02-led-blink.gif)

## Concepts

- GPIO output configuration
- Digital HIGH and LOW signals
- FreeRTOS task delays
- `vTaskDelay()`
- `pdMS_TO_TICKS()`
- Infinite application loops

## Build and Flash

Activate the ESP-IDF environment:

```
source ~/.espressif/tools/activate_idf_v6.1.sh
```

Navigate to the project directory:

```
cd labs/02-led-blink
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

The external LED connected to GPIO25 repeatedly turns on for 500 ms and off for 500 ms.

The blinking continues while the program is running.