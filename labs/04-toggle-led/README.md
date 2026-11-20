# Lab 04 — Toggle LED

## Overview

This project toggles an LED between ON and OFF states using a push button.

Each button press changes the current LED state. The LED remains in that state after the button is released.

## Components

- ESP32 DevKit
- Breadboard
- LED
- 220 Ω resistor
- Push button
- Jumper wires

## Concepts

- GPIO output configuration
- GPIO input configuration
- Internal pull-up resistor
- Button state detection
- Edge detection
- LED state management
- FreeRTOS task delays

## Wiring

### LED

- GPIO 25 → 220 Ω resistor → LED anode (long leg)
- LED cathode (short leg) → GND

### Push Button

- One side → GPIO 27
- Opposite side → GND

The internal pull-up resistor is enabled in software using `GPIO_PULLUP_ONLY`.

## Expected Result

- LED is initially OFF.
- First button press turns the LED ON.
- Releasing the button does not change the LED state.
- Second button press turns the LED OFF.
- Each subsequent press toggles the LED state.

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
