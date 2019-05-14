/* ADE9078
 ADE9078.h - Simple library for operating the ADE9078 Single-Phase AC Line measurement IC over SPI for Arduino Uno
  example library for operating the ADE9078 3-Phase AC Line measurement IC over SPI interfacing

ADE9078 board and library created by: David Brady, Jeff Baez, and Jacky Wan 11/2018

Code major development by David Brady

PCB design done by Esteban Granizo and Peter Nguyen (12/2018)

University of California, Irvine - California Plug Load Research Center (CalPlug)

December 2018 - Library First Release (December 2018) - Library Latest Release for ADE9078

Copyright (C) The Regents of the University of California, 2019

  Note: Please refer to the Analog Devices ADE9078 datasheet - much of this library was based directly on the statements and methods provided in it!  Their authors get paid, trust them over us!

  Released into the public domain.
*/


#ifndef ADE9078_h
#define ADE9078_h

//Architecture Control:
//Select the architecture in use, one but not both!  Do this in your main program file, here are examples for the defines:
//#define ESP32ARCH //This architecture is for the ESP32
#define AVRESP8266  //this architecture is for AVR/Arduino boards and the ESP8266

//Debug Control:
//#define ADE9078_VERBOSE_DEBUG //This line turns on verbose debug via serial monitor (Normally off or //'ed).  Use sparingly and in a test program to debug operation!  Turning this on can take a lot of memory and the delay from USB printing out every statement is taxing temporally!  This is non-specific and for all functions, beware, it's a lot of output that can challenge device memory!  Reported bytes are typically in HEX
//#define ADE9078_Calibration //Shows the output of the type cast functions to allow the raw values to be seen - very helpful in calibration
#define ADE9078_CRC_Output //Used to output debug information for the CRC check functions


#include "Arduino.h" //this includes the arduino library header. It makes all the Arduino functions available in this tab.
#include <SPI.h>
#include "ADE9078registers.h"
#include "LastReads.h"

#define AVRESP8266  //this architecture is for AVR/Arduino boards and the ESP8266


//Define Constants:
#define dummyWrite 0x00 //Used for SPI Transfer to read out a value const unsigned int READ = 0b10000000;  //This value tells the ADE9078 that data is to be read from the requested register.
const unsigned int WRITE = 0b00000000; //This value tells the ADE9078 that data is to be written to the requested register.
const unsigned int READ = 0b10000000;  //This value tells the ADE9078 that data is to be read from the requested register.


const long SPI_freq = 1000000;//Communicate with the ADE9078 at 1 MHz frequency.
// const int SPI_freq = 12,288,000 // P 6: Input flock frequency

struct InitializationSettings {
  // All gains are 2 bits. Options: 1, 2, 3, 4
  uint8_t vAGain;
  uint8_t vBGain;
  uint8_t vCGain;

  uint8_t iAGain;
  uint8_t iBGain;
  uint8_t iCGain;
  uint8_t iNGain;

  uint32_t powerAGain;
  uint32_t powerBGain;
  uint32_t powerCGain;

  uint8_t vConsel;
  uint8_t iConsel;
};


class ADE9078 {

public:
    //available from within or outside the class
    ADE9078(int SS, long SPI_freq, InitializationSettings*);
    ~ADE9078() { delete is; }
    struct LastReads lastReads;
    void initialize();

    uint8_t getVersion();
    double getPowerFactorA(); // only for A? Don't see for B/C
    // double getPeriod();    // not done. can probably implement with USER_PERIOD_32
    uint32_t getPhaseCalibA(); // B/C? - Implement for all phases

    uint32_t getInstVoltageA();
    uint32_t getInstVoltageB();
    uint32_t getInstVoltageC();
    void readVoltage();

    double getAVrms();
    double getBVrms();
    double getCVrms();
    void readVrms();

    uint32_t getInstCurrentA();
    uint32_t getInstCurrentB();
    uint32_t getInstCurrentC();
    void  readInstCurrent();

    double getIrmsA();
    double getIrmsB();
    double getIrmsC();
    void readIrms();

    void readFilterBasedCurrent();

    uint32_t getVpeak();
    uint32_t getIpeak();
    void readPeak();

    double readWattHoursA();
    double readWattHoursB();
    double readWattHoursC();
    void readWattHours();

    void readFundamentalReactivePower();
    void readPowerFactor();
    void readPeriod();

    double getInstApparentPowerA();
    double getInstApparentPowerB();
    double getInstApparentPowerC();
    void readInstApparentPower();

    double getInstActivePowerA();
    double getInstActivePowerB();
    double getInstActivePowerC();
    void readInstActivePower();

    double getInstReactivePowerA();
    double getInstReactivePowerB();
    double getInstReactivePowerC();
    void readInstReactivePower();

    uint32_t getPHNOLOAD();

    double read32BitAndScale(uint16_t address);

    void startFillingBuffer();
    void stopFillingBuffer();
    void isPageFull(int);
    void whichPageIsFull();
    void spiBurstResampledWFB(uint16_t);
    void configureWFB();
    void burstAvOnly();
    int isDoneSampling();

    uint8_t spiRead8(uint16_t address);   // Read, inbound function: address, NOTE: This is an example function, 8 Bit registers for returned values are not used in the ADE9078
    uint16_t spiRead16(uint16_t address);  // Read, inbound function: address
    uint32_t spiRead32(uint16_t address);  // Read, inbound function: address
    void spiWrite16(uint16_t address, uint16_t data); // Write, outbound function: address, data
    void spiWrite32(uint16_t address, uint32_t data); // Write, outbound function: address, data
    uint32_t spiRead32CRC(uint16_t address,bool &ValidCRC); //Function to allow CRC checking for 32 bit returns
    uint16_t spiRead16CRC(uint16_t address, bool &ValidCRC); //Function to allow CRC checking for 16 bit returns

private:
       //used within the class
      int _SS;
      int _SPI_freq;
      InitializationSettings* is;
      //Use SPI settings according to selected chipset in use
      #ifdef AVRESP8266
      SPISettings defaultSPISettings = SPISettings(_SPI_freq, MSBFIRST, SPI_MODE0);
      #endif
      #ifdef ESP32ARCH
      //#define ESP32SPIDefaultSettings VSPI,SPI_CLOCK_DIV16,SPI_MODE0,SPI_MSBFIRST //"ESP32SPIDefaultSettings" is used as macro holder for default settings
      //SPISettings defaultSPISettings = SPISettings(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST);, elected to hardcode right now
      #endif


};

#endif // ADE9078_H
