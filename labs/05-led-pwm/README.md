# Lab 05 — Potentiometer-Controlled LED Brightness

## Overview

This project uses a potentiometer to control LED brightness.

The ESP32 reads the analog voltage from the potentiometer using its ADC peripheral and adjusts the LED brightness using PWM (Pulse Width Modulation).

## Components

- ESP32 DevKit
- Breadboard
- LED
- 220 Ω resistor
- Potentiometer
- Jumper wires

## Concepts

- Analog-to-Digital Converter (ADC)
- Pulse Width Modulation (PWM)
- LEDC peripheral
- ADC oneshot driver
- PWM duty cycle
- Analog input and digital output

## Wiring

### LED

- GPIO 25 → 220 Ω resistor → LED anode (long leg)
- LED cathode (short leg) → GND

### Potentiometer

- First outer pin → 3.3V
- Middle pin (wiper) → GPIO 34
- Second outer pin → GND

## How It Works

1. The ADC reads the potentiometer voltage.
2. The analog reading is converted into a digital value.
3. The value is mapped to the PWM duty cycle.
4. The LED brightness changes according to the potentiometer position.

The ADC uses 12-bit resolution (0–4095), while PWM uses 13-bit resolution (0–8191).

## Expected Result

- Turning the potentiometer in one direction increases LED brightness.
- Turning it in the opposite direction decreases LED brightness.
- The LED brightness changes continuously according to the potentiometer position.

Small fluctuations in ADC readings are normal due to analog signal noise.

## Build and Flash

Activate the ESP-IDF environment:

```bash
source ~/.espressif/tools/activate_idf_v6.1.sh
```

Build the project:

```bash
idf.py build
```

Flash the firmware:

```bash
idf.py -p /dev/ttyUSB0 flash
```

Open the serial monitor:

```bash
idf.py -p /dev/ttyUSB0 monitor
```