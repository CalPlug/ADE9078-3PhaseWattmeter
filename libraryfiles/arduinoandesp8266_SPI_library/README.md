# ADE7953-Wattmeter

Example library for operating the ADE7953 Single-Phase AC Line measurement IC over SPI interfacing 

Created by Umar Kazmi, Crystal Lai, and Michael Klopfer, Ph.D.

PCB v1 and v2 Board design by Damien Putignani (11/2016, 02/2017)

Version 3 PCB update by Yuxiang (Eric) Li	and Zihan (Bronco) Chen (11/2017)

Version 4 PCB (SPI and I2C Variants) update by Andy Begley and Lifeng Liang (5/2018)

University of California, Irvine - California Plug Load Research Center (CalPlug)

February 23, 2017 - Library First Release

Copyright (C) The Regents of the University of California, 2018


Released into the public domain under creative commons share-alike license. This is an example C++ library for Arduino for operating the ADE7953 Single-Phase AC Line measurement IC over SPI and tested with the Arduino Uno and C++ Arduino-style compiler for the Espressif ESP8266. This library in current form was shown to work with the Arduino Uno and the Espressif ESP8266.  See note below about Espressif ESP32 compatability - a working example is provided isn the ESP32 folder in this project.  This ESP32 extension example was developed by Luis Contreras as part of the CalPlug EVSE Project - https://github.com/CalPlug/EVSE_Smart_Charger and presented in this project as functional example working with the ESP32.
.  

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.
When installed, this library should look like:
Arduino/lib/targets/libraries/ADE7953              (this library's folder)
Arduino/lib/targets/libraries/ADE7953/ADE7953.cpp     (the library implementation file)
Arduino/lib/targets/libraries/ADE7953/ADE7953.h       (the library description file)
Arduino/lib/targets/libraries/ADE7953/examples     (the examples)
Arduino/lib/targets/libraries/ADE7953/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you can start the Arduino application.
You may see a few warning messages as it's built.
To use this library in a sketch, go to the Sketch | Import Library menu and select Test. This will add a corresponding line to the top of your sketch: #include <ADE7953.h>
To stop using this library, delete that line from your sketch.

Background of Operation
--------------------------------------------------------------------------------

The ADE7953 uses registers for communication.  Depending on the type, this can be an 8 bit, 16 bit, 24 bit or 32 bit register.  Communication of over 8 bits uses sequential bytes using typical SPI byte-wise communication.  There are redundancies in how registers are accessed via different bit values for registers.  For addresses, the same command may be represented in multiple bit versions (eg a 24bit or 32 bit). When you call on a certain address, the corresponding value is returned with the value bit size corresponding to the 24 or 32 bit address called on. The responding value returns as the function called and of the same bit size.  Refer to the documentation!  For Debug, the Serial Monitor runs at 115200 baudrate when the reporting DEBUG functionality is activated.  Uncomment IFDEF statements in the library for library operation debug. 

Usage
--------------------------------------------------------------------------------

There are several layers of functionality in the library.  Functions are defined to permit direct communication via registers of different bit sizes.  One can use the functions in this library for direct communication using the send and receive capability of the register calls or use direct functions.  The direct functions are also included. In order to access the functions, you must write in the Arduino file myADE7953.getFunction(), Function being the function you want such as Vrms or IrmsA (the different names of functions can be found in the .h file), while myADE7953 calls on the library. 

Demo
--------------------------------------------------------------------------------

When connecting a 80-Watt Lightbulb with a 110V AC, 60HZ, source and using our demo code, the serial monitor reads out the following approximate measurements from the current sensor:

Vrms (V): 110

IrmsA (mA): 718

Apparent Power A (mW): 80000

Active Power A (mW): 80000

Reactive Power A (mW): 4100

Power Factor (div 100): 99.90

A varient of this project's code was shown to work on the Espressif ESP32, please see this project for more details:  https://github.com/CalPlug/EVSE_Smart_Charger

Active Energy A (hex): 5132 


Physical Demo Board
----------
This design is provided without any warranty or assumption of liability.  This project involves the use of mains voltage.  We have no idea how well you can reporduce this design: we assume no liability for your implementation or usage mistakes! Please construct and use at your own risk.

This folder contains all the files required to construct a fully isolated ADE7953 wattmeter board that uses SPI or UART communication (see IC Datasheet). Please refer to the README inside the folder for more details on using the files.  The Version 3 supercedes the Version 2 board.  Version 1 of this PCB was an internally produced breadboard evaualtion version of this design.  It was created only to be proceeded by Version 2.  In the Version 2 (preliminary release) revision, there is no tri-state on the MISO line on the external side of the isolation chipset. Because of this, the board works properly when it is the only device on the SPI bus. If more devices are used on the same SPI bus, the CS line (inverted) must be used to drive a tristate to isolate the MISO line from this board.  The RESET and IRQ lines can be left unconnected for general operation of the board - the ADE7953 reset line is held HIGH by a pullup by default.  The minimum connections required are the data and power lines.  Be cognizent that flipped L and N in this design can result in safety concerns - the neutral volatage should be very close to ground.  This issue is mediated in the following design revisions.  The Version 2 board has the neutral connected to the isolated ground.  In bench testing, this design worked well, but in general usage, several catostrophic board failures resulted (not that crazy on our part: look at how the Analog Devices datasheet and AD demo boards are wired :) ).  

Accordingly, a safer design was developed (Version 3).  As previously stated, the Version 2 of the board does not allow for multiple devices to be used on the SPI as the MISO line is held low when communication has ended (the isolator is always enabled, causing this).  In the updated Version 3, a tri-state buffer allows proper SPI usage with multiple devices and resistor chains are used to isolate the neutral from the ground in case of the neutral having the voltage become raised substantially above the ground (or flipped with the line).

The Version 4 of this board allows use of a multiplexer for line and neutral inputs along with two current measurement coils to allow GFI detection.  The isolator configuration allows for fullly independant ground isolation.  The a jumper on this board (position 1-2, or position 2-3) allows the static setting of the line, or a pin (SELECT) can be used to toggle the voltage input being read (used with ground fault detection - full GFI implementation requires an interruptter!).  This can be used to set a single input pin for the line to measure against ground without needing a dedicated microcontroller pin or external connection.  Mind the phasing between the two coils if two CTs are used for GFI detection.  Implementation of the GFI detection and interruption with this design was demonstrated in this project using the Espressif ESP32: https://github.com/CalPlug/EVSE_Smart_Charger   The default version of this board (Version 4) is also UART compatable (see included documentation) in addition to SPI.  But the bidirectional nature of I2C prevents this working with the current isolation scheme.  An alternative design (Version 4 I2C) is also provided which permits I2C interfacing using the same board format.

