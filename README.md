# ESP32 Wi-Fi & Bluetooth Network Scanner

A Wi-Fi and Bluetooth network scanner built with ESP32, LCD I2C display, and RGB LED.

## How It Works

1. ESP32 scans nearby Wi-Fi networks
2. Displays network name (SSID) and signal strength (RSSI) on LCD
3. RGB LED changes color based on signal strength
4. Then scans for Bluetooth devices
5. Displays BT device name and signal strength

## Libraries

- LiquidCrystal I2C by Frank de Brabander
- WiFi (ESP32 built-in)
- BLEDevice / BLEScan (ESP32 built-in)

## Components

| Component | Description |
|---|---|
| ESP32 Dev Board | Main microcontroller (Wi-Fi & BT built-in) |
| 16x2 LCD I2C | Displays scan results |
| RGB LED | Visual signal strength indicator |
| 3x 1kΩ Resistor | Current limiting for RGB LED |
| Breadboard | Circuit prototyping |
| Jumper Cables | Connections |

## Pin Connections / ## RGB LED Color System

| Component | Pin | ESP32 | / | Color | Meaning |
|---|---|---|               / |---|---|
| LCD I2C | VCC | 5V |      / | 🔵 Blue | Scanning |
| LCD I2C | GND | GND |     / | 🟢 Green | Strong signal (-50 dBm+) |
| LCD I2C | SDA | GPIO19 |  / | 🩵 Cyan | Medium signal (-50 to -70 dBm) |
| LCD I2C | SCL | GPIO18 |  / | 🔴 Red | Weak signal (-70 dBm-) |
| RGB LED | R | GPIO23 |    / | 🟣 Purple | Bluetooth device found |
| RGB LED | G | GPIO22 |    / | 🟡 Yellow | Refreshing |
| RGB LED | B | GPIO21 |
| RGB LED | COM | 3.3V |
