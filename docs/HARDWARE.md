# Hardware — IoTWaterTankLevelMonitor

## Parts and electrical limits
ESP32 DevKit and waterproof ultrasonic module with TTL trigger/echo; echo level shifter. Power low-voltage modules from a suitable regulated supply, tie grounds together, and verify signal levels before connection. GPIO34 is input-only and ADC1 is used because ADC2 conflicts with Wi-Fi. Never apply more than 3.3 V to an ESP32 GPIO.

| ESP32 pin | Connection | Requirement |
|---|---|---|
| ESP32 3V3 | sensor VCC | Verify module supply rating |
| ESP32 GND | sensor GND | Common low-voltage ground |
| GPIO25 | ultrasonic A TRIG | 3.3 V output |
| GPIO26 | ultrasonic A ECHO | Level shift 5 V echo to 3.3 V |

Use a pull-down on GPIO14's driver input so the load remains off during boot. Low-voltage relays must not be connected directly to GPIO, and inductive loads need flyback protection.

## Sensor specification and calibration
The firmware accepts sensor-to-water distance from 2 to 200 cm. Secondary value is level estimate (%). Level estimate assumes a 100 cm usable tank depth; use a waterproof sensor. Use a multimeter and the sensor data sheet for the exact module revision.
