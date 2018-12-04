# ADE9078-Wattmeter

Example library for operating the ADE9078 3-Phase AC Line measurement IC over SPI interfacing 

Created by Umar Kasmi, Sid Kasat, Crystal Lai, and Michael Klopfer

Project mentors: Michael Klopfer, Ph.D. and prof. G.P. Li

ESP32 Extension Development for ESP32 by Luis Contreras as part of the CalPlug EVSE Project - https://github.com/CalPlug/EVSE_Smart_Charger

University of California, Irvine - California Plug Load Research Center (CalPlug)


February 23, 2017 - first version
May 14, 2018 - Version 1.0 for ESP32 Version for ADE7953
XXXXXX - Version 1.0 for ADE9078, polyphase AC measurement IC

Copyright (C) The Regents of the University of California, 2018

Released into the public domain. This is an example C++ library for Arduino for operating the ADE7953 Single-Phase AC Line measurement IC over SPI and tested with the Arduino Uno and C++ Arduino-style compiler for the Espressif ESP32. 

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.
When installed, this library should look like:
Arduino/lib/targets/libraries/ADE9078ESP32              (this library's folder)
Arduino/lib/targets/libraries/ADE9078ESP32/ADE9078ESP32.cpp     (the library implementation file)
Arduino/lib/targets/libraries/ADE9078ESP32/ADE9078ESP32.h       (the library description file)
Arduino/lib/targets/libraries/ADE9078ESP32/examples     (the examples)
Arduino/lib/targets/libraries/ADE9078ESP32/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you can start the Arduino application.
You may see a few warning messages as it's built.
To use this library in a sketch, go to the Sketch | Import Library menu and select Test. This will add a corresponding line to the top of your sketch: #include <ADE9078ESP32.h>
To stop using this library, delete that line from your sketch.

Background of Operation
--------------------------------------------------------------------------------

The ADE9078 uses registers for communication.  Depending on the type, this can be an 8 bit, 16 bit, 24 bit or 32 bit register.  Communication of over 8 bits uses sequential bytes using typical SPI byte-wise communication.  There are redundancies in how registers are accessed via different bit values for registers.  For addresses, the same command may be represented in multiple bit versions (eg a 24bit or 32 bit). When you call on a certain address, the corresponding value is returned with the value bit size corresponding to the 24 or 32 bit address called on. The responding value returns as the function called and of the same bit size.  Refer to the documentation!  For Debug, the Serial Monitor runs at 115200 baudrate when the reporting DEBUG functionality is activated.  Uncomment IFDEF statements in the library for library operation debug. 

Usage
--------------------------------------------------------------------------------

There are several layers of functionality in the library.  Functions are defined to permit direct communication via registers of different bit sizes.  One can use the functions in this library for direct communication using the send and receive capability of the register calls or use direct functions.  The direct functions are also included. In order to access the functions, you must write in the Arduino file myADE9078ESP32.getFunction(), Function being the function you want such as Vrms or IrmsA (the different names of functions can be found in the .h file), while myADE9078ESP32 calls on the library. 

Demo
--------------------------------------------------------------------------------
Multiphase demo to be added:


Physical Demo Board
----------
See board files for more details