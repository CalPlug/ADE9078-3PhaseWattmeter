/*
 ADE9078.cpp - Simple library for operating the ADE9078 Single-Phase AC Line measurement IC over SPI for Arduino Uno
  Created by Umar Kazmi, Crystal Lai, and Michael Klopfer, Ph.D.
  January 23, 2017 - v6.2 (pre-release)
  University of California, Irvine - California Plug Load Research Center (CalPlug)
  Released into the public domain.
*/

#ifndef ADE9078_hpp
#define ADE9078_hpp

#include "Arduino.h" //this includes the arduino library header. It makes all the Arduino functions available in this tab.
#include <SPI.h>
#include "ADE9078registers.hpp"

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
    ADE9078(int SS, long SPI_freq, InitializationSettings*);
    ~ADE9078() { delete is; }

    void initialize();

	uint8_t getVersion();
	float getPowerFactorA(); // only for A? Don't see for B/C
	// float getPeriod();    // not done. can probably implement with USER_PERIOD_32
	int32_t getPhaseCalibA(); // B/C?

  long getInstVoltageA();
  long getInstVoltageB();
  long getInstVoltageC();

	float getAVrms();
  float getBVrms();
  float getCVrms();

	long getInstCurrentA();
  long getInstCurrentB();
  long getInstCurrentC();

	float getIrmsA();
  float getIrmsB();
  float getIrmsC();

	unsigned long getVpeak();
	unsigned long getIpeak();

	long getEnergyA();

	float getInstApparentPowerA();
  float getInstApparentPowerB();
  float getInstApparentPowerC();

	float getInstActivePowerA();
  float getInstActivePowerB();
  float getInstActivePowerC();

	float getInstReactivePowerA();
  float getInstReactivePowerB();
  float getInstReactivePowerC();

  unsigned long getPHNOLOAD();

  float read32Bit(uint16_t);

  uint16_t spiAlgorithm16_read(uint16_t);
  uint32_t spiAlgorithm32_read(uint16_t);

	void spiAlgorithm32_write(uint16_t, uint32_t); // address, data
	void spiAlgorithm16_write(uint16_t, uint16_t);




  private:
  	int _SS;
    int _SPI_freq;
    InitializationSettings* is;
    SPISettings defaultSPISettings = SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3);

};

#endif // ADE9078_HPP
