Use VSPI pins
MOSI	GPIO 23
MISO	GPIO 19
SCLK	GPIO 18
CS/SS	GPIO 5

3.3V to 3.3V
Reset to En/Rest
GND to GND

If you get a core dumped error do the following:

https://github.com/espressif/arduino-esp32/issues/523
"@mceyzar It's an out of stack problem

Just increase 4096 value to a bigger one (8192 is ok) here: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/main.cpp#L25

@zjykymt Using EspExceptionDecoder: https://github.com/me-no-dev/EspExceptionDecoder"

*just double the stack size. In my hardware files I found that it was already 8192 so I made it 16384.

