/*
 ADE9078.cpp - Simple library for operating the ADE9078 Single-Phase AC Line measurement IC over SPI for Arduino Uno
  Created by XXXXXXX   and Michael Klopfer, Ph.D.
  February 20, 2019 - v6.2 (pre-release)
  University of California, Irvine - California Plug Load Research Center (CalPlug)
  Released into the public domain.
*/

#ifndef ADE9078_h
#define ADE9078_h

#include "Arduino.h" //this includes the arduino library header. It makes all the Arduino functions available in this tab.
#include <SPI.h>
#include "ADE9078registers.h"

//Define Constants:
#define dummyWrite 0x00 //Used for SPI Transfer to read out a value const unsigned int READ = 0b10000000;  //This value tells the ADE7953 that data is to be read from the requested register.
const unsigned int WRITE = 0b00000000; //This value tells the ADE7953 that data is to be written to the requested register.
const unsigned int READ = 0b10000000;  //This value tells the ADE7953 that data is to be read from the requested register.


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

	  void initialize(int configurationselection);

	  uint8_t getVersion();
	  double getPowerFactorA(); // only for A? Don't see for B/C
	  // double getPeriod();    // not done. can probably implement with USER_PERIOD_32
	  uint32_t getPhaseCalibA(); // B/C? - Implement for all phases

	  uint32_t getInstVoltageA();
	  uint32_t getInstVoltageB();
	  uint32_t getInstVoltageC();

	  double getAVrms();
	  double getBVrms();
	  double getCVrms();

	  uint32_t getInstCurrentA();
	  uint32_t getInstCurrentB();
	  uint32_t getInstCurrentC();

	  double getIrmsA();
	  double getIrmsB();
	  double getIrmsC();

	  uint32_t getVpeak();
	  uint32_t getIpeak();

	  uint32_t getEnergyA();

	  double readWattHoursA();

	  double getInstApparentPowerA();
	  double getInstApparentPowerB();
	  double getInstApparentPowerC();

	  double getInstActivePowerA();
	  double getInstActivePowerB();
	  double getInstActivePowerC();

	  double getInstReactivePowerA();
	  double getInstReactivePowerB();
	  double getInstReactivePowerC();

	  uint32_t getPHNOLOAD();

	  double read32BitAndScale(uint16_t address);

	  byte functionBitVal(uint16_t addr, uint8_t byteVal); //function used to separate each byte of an address provided
	  uint8_t spiRead8(uint16_t address);   // Read, inbound function: address, NOTE: This is an example function, 8 Bit registers for returned values are not used in the ADE9078
	  uint16_t spiRead16(uint16_t address);  // Read, inbound function: address
	  uint32_t spiRead32(uint16_t address);  // Read, inbound function: address
	  void spiWrite16(uint16_t address, uint16_t data); // Write, outbound function: address, data
	  void spiWrite32(uint16_t address, uint32_t data); // Write, outbound function: address, data

	  unsigned short crc16(char data_p, unsigned short length); //CRC verification function

  private:
	   //used within the class
	  int _SS;
	  int _SPI_freq;
	  InitializationSettings* is;
	  //Use SPI settings according to selected chipset in use
	  #ifdef AVRESP8266
	  SPISettings defaultSPISettings = SPISettings(_SPI_freq, MSBFIRST, SPI_MODE0);
	  #endif
	  #ifdef ESP32
	  //#define ESP32SPIDefaultSettings VSPI,SPI_CLOCK_DIV16,SPI_MODE0,SPI_MSBFIRST //"ESP32SPIDefaultSettings" is used as macro holder for default settings
	  //SPISettings defaultSPISettings = SPISettings(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST);, elected to hardcode right now
	  #endif


};

#endif // ADE9078_H
