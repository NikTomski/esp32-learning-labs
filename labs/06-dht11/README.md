# Lab 06 — DHT11 Temperature and Humidity Sensor

## Overview

This project uses a DHT11 digital sensor to measure temperature and relative humidity.

The ESP32 communicates with the sensor through a single digital GPIO pin using the DHT communication protocol.

The sensor readings are displayed in the serial monitor.

## Components

- ESP32 DevKit
- DHT11 temperature and humidity sensor module (3-pin)
- Breadboard
- Jumper wires

## Concepts

- Digital sensors
- GPIO input
- DHT communication protocol
- Temperature measurement
- Relative humidity measurement
- ESP-IDF Component Manager
- External component dependencies

## Wiring

### DHT11 Sensor

- VCC → 3.3V
- DATA → GPIO 4
- GND → GND

Check the pin labels on your sensor module before connecting it.

## Dependencies

This project uses the [esp-idf-lib/dht](https://components.espressif.com/components/esp-idf-lib/dht) component.

The dependency is managed through the ESP-IDF Component Manager and declared in `main/idf_component.yml`.

## How It Works

1. The ESP32 initializes the DHT11 sensor.
2. The sensor is read periodically using GPIO 4.
3. The library retrieves temperature and humidity measurements.
4. The readings are printed to the serial monitor.
5. If a reading fails, an error message is displayed.

The sensor is read every 2 seconds.

## Expected Result

The serial monitor displays temperature and relative humidity readings:

```text
I (....) DHT11: Temperature: 24.0 C
I (....) DHT11: Humidity: 45.0 %
```

Actual values depend on the surrounding environment.

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