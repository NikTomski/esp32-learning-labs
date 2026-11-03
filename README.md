# ESP32 Learning Labs

A collection of practical projects and experiments while learning
ESP32 development with ESP-IDF.

## Environment

- Board: ESP32 DevKit
- Framework: ESP-IDF
- Language: C
- IDE: Visual Studio Code

## Labs

| # | Project | Topics |
|---|---------|--------|
| 00 | Hello ESP32 | ESP-IDF setup, build, flash, serial monitor |
| 01 | LED On | GPIO output |
| 02 | LED Blink | GPIO output, FreeRTOS delays |
| 03 | Button + LED | GPIO input, pull-up, button state |

## Structure

Each directory in `labs/` is an independent ESP-IDF project.

##Build

Activate the ESP-IDF environment, then navigate to the desired lab:

```
source ~/.espressif/tools/activate_idf_v6.1.sh
cd labs/00-hello-esp32
idf.py build
idf.py flash monitor
```
