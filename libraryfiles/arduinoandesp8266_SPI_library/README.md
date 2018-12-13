# ADE9078-3-Phase Wattmeter

Version 0.1

Example library for operating the ADE9078 3-Phase AC Line measurement IC over SPI interfacing


ADE9078 board and library created by: David Brady, Jeff Baez, and Jacky Wan 11/2018

PCB design done by Esteban Granizo and Peter Nguyen (12/2018)

University of California, Irvine - California Plug Load Research Center (CalPlug)

December 2018 - Library First Release
(December 2018) - Library Latest Release for ADE9078

Copyright (C) The Regents of the University of California, 2018

Released into the public domain under creative commons share-alike license. This is an example C++ library for Arduino for operating the ADE9078 3-Phase AC Line measurement IC over SPI and tested with the Arduino Uno and C++ Arduino-style compiler for the Espressif ESP8266. This library in current form was shown to work with the Arduino Uno and the Espressif ESP8266.  See note below about Espressif ESP32 compatibility - a working forked example is provided is in the ESP32 folder in this project.  This ESP32 extension example was developed by Luis Contreras as part of the CalPlug EVSE Project - https://github.com/CalPlug/EVSE_Smart_Charger and presented in this project as functional example working with the ESP32.
.  

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.
When installed, this library should look like:
Arduino/lib/targets/libraries/ADE9078              (this library's folder)
Arduino/lib/targets/libraries/ADE9078/ADE7953.cpp     (the library implementation file)
Arduino/lib/targets/libraries/ADE9078/ADE7953.h       (the library description file)
Arduino/lib/targets/libraries/ADE9078/examples     (the examples)
Arduino/lib/targets/libraries/ADE9078/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you can start the Arduino application.
You may see a few warning messages as it's built.
To use this library in a sketch, go to the Sketch | Import Library menu and select Test. This will add a corresponding line to the top of your sketch: #include <ADE7953.h>
To stop using this library, delete that line from your sketch.

Background of Operation
--------------------------------------------------------------------------------

The ADE9078 uses registers for communication.  Depending on the type, this can be a 16 bit or 32 bit register.  Communication uses sequential bytes using typical SPI byte-wise communication.  There are redundancies in how registers are accessed via different bit values for registers.  For addresses, the same command may be represented in multiple bit versions (eg a 16bit or 32 bit). When you call on a certain address, the corresponding value is returned with the value bit size corresponding to the 16 or 32 bit address called on. The responding value returns as the function called and of the same bit size.  Refer to the documentation!  For Debug, the Serial Monitor runs at 115200 baudrate when the reporting DEBUG functionality is activated.  Uncomment IFDEF statements in the library for library operation debug.

Usage
--------------------------------------------------------------------------------

There are several layers of functionality in the library.  Functions are defined to permit direct communication via registers of different bit sizes.  One can use the functions in this library for direct communication using the send and receive capability of the register calls or use direct functions.  The direct functions are also included. In order to access the functions, you must write in the Arduino file ADE9078.getFunction(), Function being the function you want such as Vrms or IrmsA (the different names of functions can be found in the .h file), while myADE9078 calls on the library.

Demo
--------------------------------------------------------------------------------
(TO BE ADDED)

Physical Demo Board
----------
This design is provided without any warranty or assumption of liability.  This project involves the use of mains voltage.  We have no idea how well you can reporduce this design: we assume no liability for your implementation or usage mistakes! Please construct and use at your own risk.

This folder contains all the files required to construct a fully isolated ADE9078 wattmeter board that uses SPI communication. Please refer to the README inside the folder for more details on using the files.
