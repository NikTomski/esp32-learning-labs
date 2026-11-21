# Lab 07 — Active and Passive Buzzer

## Overview

This project demonstrates how to control active and passive buzzers using an ESP32.

Two operating modes are implemented in a single application:
- Active buzzer controlled using GPIO.
- Passive buzzer controlled using LEDC PWM.

The buzzer type can be selected by changing a single configuration value in `main.c`.

## Components

- ESP32 DevKit
- Active buzzer
- Passive buzzer
- Breadboard
- Jumper wires

## Concepts

- GPIO output control
- Active vs. passive buzzers
- PWM (Pulse Width Modulation)
- LEDC peripheral
- Frequency and duty cycle
- FreeRTOS task delays
- Conditional compilation

## Wiring

| Buzzer | ESP32 |
|---|---|
| Active buzzer (+) | GPIO 26 |
| Passive buzzer (+) | GPIO 26 |
| Buzzer (-) | GND |

Only one buzzer should be connected at a time.

## How It Works

### Active Buzzer

An active buzzer contains an internal oscillator and generates sound when powered.

The ESP32 controls it by setting GPIO 26 HIGH or LOW.

The buzzer switches between:
- 1 second ON
- 1 second OFF

### Passive Buzzer

A passive buzzer requires an external signal to generate sound.

The ESP32 uses the LEDC peripheral to generate PWM signals at different frequencies.

The application plays a simple ascending melody using musical notes from C4 to C5.

### Mode Selection

The operating mode is selected in `main.c`:

```c
#define BUZZER_TYPE 1  // Active buzzer
```
```c
#define BUZZER_TYPE 2  // Passive buzzer
```

Use only one definition at a time.

## Expected Result

**Active mode:**
- Repeating beeps with one-second intervals.

**Passive mode:**
- An ascending sequence of musical notes.
- The melody repeats every two seconds.

## Build and Flash

Activate ESP-IDF:

```bash
source ~/.espressif/tools/activate_idf_v6.1.sh
```

Build the project:

```bash
idf.py build
```

Flash the ESP32:

```bash
idf.py -p /dev/ttyUSB0 flash
```

Open the serial monitor:

```bash
idf.py -p /dev/ttyUSB0 monitor
```
