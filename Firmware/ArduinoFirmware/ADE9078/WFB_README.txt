Enoch Chau 6/12/2019

This library has implementation for both Arduino and ESP32.
To set up Arduino: https://www.arduino.cc/en/Main/Software
To set up Arduino IDE for ESP32: https://github.com/espressif/arduino-esp32

All examples using the waveform buffer are written for ESP32 Architecture.
Any examples that do not use the arduino FFT library are compatible with Arduino UNO.

It may be possible to modify WFBFFT examples for Arduino DUE or another similarly powerful microcontroller.
These examples do NOT work with Arduino UNO as there is not enough SRAM to run the WFB and calculate the FFT.

All WFB functions use resampled data. If you are referencing the datasheet, be sure to look
only at the parts regarding resampled data.
