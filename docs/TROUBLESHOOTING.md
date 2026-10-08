# Troubleshooting — IoTWaterTankLevelMonitor

| Symptom | Check |
|---|---|
| No sensor-to-water distance | Verify sensor power, grounds, pin table, voltage limits, and module orientation. |
| Invalid sample | Check 2–200 cm range and sensor calibration. |
| Wi-Fi disconnected | Check SSID, 2.4 GHz coverage, and local network policy. |
| MQTT disconnected | Check broker DNS, port 8883, CA PEM, device credentials, and publish ACL. |
| Unexpected alert | Inspect raw sensor-to-water distance and level estimate; calibrate the threshold in `logic.h`. |
| Build failure | Confirm PlatformIO is installed and dependency downloads are permitted. |

Level estimate assumes a 100 cm usable tank depth; use a waterproof sensor.
