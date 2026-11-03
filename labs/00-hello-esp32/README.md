# Lab 00 — Hello ESP32

## Overview

The first ESP32 project.

The application prints a message to the serial monitor.

## Components

- ESP32 DevKit
- USB cable
- Computer with ESP-IDF installed

## Concepts

- ESP-IDF project structure
- Application entry point (`app_main`)
- Serial output using `printf`
- Building and flashing firmware
- Using the ESP-IDF monitor

## Build and Flash

Activate the ESP-IDF environment:

```source ~/.espressif/tools/activate_idf_v6.1.sh```

Navigate to the project directory:

```cd labs/00-hello-esp32```

Build the project:

```idf.py build```

Flash the firmware and open the serial monitor:

```idf.py flash monitor```

## Expected Result

The serial monitor displays:

`Hello, ESP32!`