# SimpleBleAdvertiser
  Simple BLE advertiser that updates the advertising name when a button is pressed.

  Based on SimpleBLEDevice example from Espressif Systems
  pressing the button restarts BLE with new a advertising name using the elapsed seconds.
  The LED toggles every 1000mS.
  Compiled for Lolin32 Lite, but should work on nearly any ESP32 device.
  Note: not all ESP32 device libraries define "BUILDIN_LED" (GPIO22)

## Arduino info
Board manager:  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Library:        

### Arduino IDE settings
Arduino board:  Wemos Lolin32 Lite
Flash mode:     QIO
Flash size:     4MB (32Mb)
Arduino runs on Core 1
Events run on Core 1
PSRAM:          disabled

CPU:            ESP32-DOWQ6

### Board info
BN:   Unknown board
VID:  1A86
PID:  7523
SN:   Upload any sketch to obtain it
