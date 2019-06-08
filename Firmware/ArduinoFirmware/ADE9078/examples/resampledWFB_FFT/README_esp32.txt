Use VSPI pins for ESP32 SPI
MOSI	GPIO 23
MISO	GPIO 19
SCLK	GPIO 18
CS/SS	GPIO 5

3.3V to 3.3V
Reset to En/Reset
GND to GND

If you get a core dumped error do the following:
In: ../Documents/Arduino/hardware/espressif/esp32/cores/esp32/main.cpp
Increase the stack size. In my hardware files I found that it was already 8192 so I made it 16384.

Source: https://github.com/espressif/arduino-esp32/issues/523
