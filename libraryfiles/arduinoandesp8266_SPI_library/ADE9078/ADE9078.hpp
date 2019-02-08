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

const long SPI_freq = 1000000;//Communicate with the ADE9078 at 1 MHz frequency.
// const int SPI_freq = 12,288,000 // P 6: Input flock frequency

class ADE9078 {
  public:
    ADE9078(int SS, int SPI_freq);
    void initialize();

	uint8_t getVersion();
	float getPowerFactorA(); // only for A? Don't see for B/C
	// float getPeriod();    // not done. can probably implement with USER_PERIOD_32
	int32_t getPhaseCalibA(); // B/C?
	unsigned long getPHNOLOAD();

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

  uint16_t spiAlgorithm16_read(uint16_t);
  uint32_t spiAlgorithm32_read(uint16_t);

	void spiAlgorithm32_write(uint16_t, uint32_t); // address, data
	void spiAlgorithm16_write(uint16_t, uint16_t);


	float decimalize(long input, float factor, float offset);

  private:
  	int _SS;
    int _SPI_freq;
};

#endif // ADE9078_HPP
