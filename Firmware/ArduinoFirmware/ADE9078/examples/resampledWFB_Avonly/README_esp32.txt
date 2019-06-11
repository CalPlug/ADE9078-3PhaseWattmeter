Run this programing using single_phase_graph.pde for a bar graph visualization of the FFT.

----------------------------pinout----------------------------------------
Use VSPI pins for ESP32 SPI
MOSI	GPIO 23   Blue
MISO	GPIO 19   Grey
SCLK	GPIO 18   Yellow
CS/SS	GPIO 5    Orange
En/RESET        Green
GND             Red
3V3             Purple

Black and white wires are for ISR.

----------------------------debugging------------------------------------
If you get a core dumped error do the following:
In: ../Documents/Arduino/hardware/espressif/esp32/cores/esp32/main.cpp
Increase the stack size. In my hardware files I found that it was already 8192 so I made it 16384.

Source: https://github.com/espressif/arduino-esp32/issues/523
