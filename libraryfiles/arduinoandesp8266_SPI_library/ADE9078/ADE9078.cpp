/* ADE9078
 ADE9078.cpp - Example library for operating the ADE9078 Single-Phase AC Line measurement IC over SPI for Arduino Uno
  Created by Umar Kazmi, Crystal Lai, and Michael J. Klopfer, Ph.D.
  January 23, 2017 - 0.1 (pre-release)
  May 3, 2018 - v6.2 (current version) - by MJK
  Verified for compatibility with Arduino Uno and Espressif ESP8266, please see README about ESP32 compatibility.
  University of California, Irvine - California Plug Load Research Center (CalPlug)
  Copyright: The Regents of the University of California
  Released into the public domain with Share-alike licensing.
  Be decent: if our work helped you, then please reference/acknowledge this project and its authors in your work!

  Note: Please refer to the Analog Devices ADE9078 datasheet - much of this library was based directly on the statements and methods provided in it!  Their authors get paid, trust them over us!
*/

#include "Arduino.h"
#include <SPI.h>
#include "ADE9078.hpp"
//Debug Control:
//#define ADE9078_VERBOSE_DEBUG //This line turns on verbose debug via serial monitor (Normally off or //'ed).  Use sparingly and in a test program to debug operation!  Turning this on can take a lot of memory and the delay from USB printing out every statement is taxing temporally!  This is non-specific and for all functions, beware, it's a lot of output!  Reported bytes are in HEX


//**************** Helper Functions *****************

bool checkBit(int data, int i) // return true if i'th bit is set, false otherwise
{
    // datasheet counts bits starting at 0. so the 2nd bit would be the 1 in 00100
    /* example: assume input.. data=5, i=2
    data = 5 ----> 00101
    00101 & 00100 ---> 00100 --> 4
    4 > 0, return true, the bit is set.
    */
    return ((data) & (1 << i)) > 0;
}

float decimalize(long input, float factor, float offset) //This function adds a decimal point to the input value and returns it as a float, it also provides linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE7953::calibration and float type conversion function executed ");
  #endif
return ((float)input/factor)+offset;
}

//**************** End Helper Functions *****************

//****************User Program Functions*****************

uint8_t ADE9078::getVersion(){
  return spiAlgorithm16_read(VERSION_16);
}

float ADE9078::getPowerFactorA(){
	int16_t value=0;
	value=spiAlgorithm16_read(PFA_16);
	float decimal = decimalize(value, 327.67, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

// TODO: float ADE9078::getPowerFactorB(){

// TODO: float ADE9078::getPowerFactorB(){

// which APHCAL should we use? There are 4
int32_t ADE9078::getPhaseCalibA(){
	int32_t value=0;
	value=spiAlgorithm32_read(APHCAL0_32);
return value;
  }

// TODO : USER_PERIOD_32
// No period register?
// float ADE9078::getPeriod(){
// 	uint16_t value=0;
// 	value=spiAlgorithm16_read((functionBitVal(Period_16,1)),(functionBitVal(Period_16,0)));
// 	float decimal = decimalize(value, 1, 0); //convert to float with calibration factors specified
// return decimal;
//   }
// might need to edit to access bits for a/b/c
unsigned long ADE9078::getPHNOLOAD(){  //use signed long for signed registers, and unsigned long for unsigned registers
	unsigned long value=0;  //use signed long for signed registers, and unsigned long for unsigned registers
	value=spiAlgorithm32_read(PHNOLOAD_32); //Call MSB and LSB from the register constant (template for how all functions should be called)
return value;
  }


long ADE9078::getInstVoltageA(){
	long value=0;
	value=spiAlgorithm32_read(AV_PCF_32);
return value;
  }
long ADE9078::getInstVoltageB(){
	long value=0;
	value=spiAlgorithm32_read(BV_PCF_32);
  return value;
}
long ADE9078::getInstVoltageC(){
	long value=0;
	value=spiAlgorithm32_read(CV_PCF_32);
  return value;
}

float ADE9078::getAVrms(){
	unsigned long value=0;
	value=spiAlgorithm32_read(AVRMS_32);
	float decimal = decimalize(value, 19090, 0); //convert to float with calibration factors specified
return decimal;
  }

float ADE9078::getBVrms(){
	unsigned long value=0;
	value=spiAlgorithm32_read(BVRMS_32);
	float decimal = decimalize(value, 19090, 0); //convert to float with calibration factors specified
return decimal;
  }

float ADE9078::getCVrms(){
	unsigned long value=0;
	value=spiAlgorithm32_read(CVRMS_32);
	float decimal = decimalize(value, 19090, 0); //convert to float with calibration factors specified
return decimal;
  }

long ADE9078::getInstCurrentA(){
	long value=0;
	value=spiAlgorithm32_read(AI_PCF_32);
return value;
  }

long ADE9078::getInstCurrentB(){
	long value=0;
	value=spiAlgorithm32_read(BI_PCF_32);
return value;
  }

long ADE9078::getInstCurrentC(){
	long value=0;
	value=spiAlgorithm32_read(CI_PCF_32);
return value;
  }

float ADE9078::getIrmsA(){
	unsigned long value=0;
	value=spiAlgorithm32_read(AIRMS_32);
	float decimal = decimalize(value, 1327, 0); //convert to float with calibration factors specified
  return decimal;
}

float ADE9078::getIrmsB(){
	unsigned long value=0;
	value=spiAlgorithm32_read(BIRMS_32);
	float decimal = decimalize(value, 1327, 0); //convert to float with calibration factors specified
  return decimal;
}

float ADE9078::getIrmsC(){
	unsigned long value=0;
	value=spiAlgorithm32_read(CIRMS_32);
	float decimal = decimalize(value, 1327, 0); //convert to float with calibration factors specified
return decimal;
  }


unsigned long ADE9078::getVpeak(){
	unsigned long value=0;
	value=spiAlgorithm32_read(VPEAK_32);
return value;
  }

unsigned long ADE9078::getIpeak(){
	unsigned long value=0;
	value=spiAlgorithm32_read(IPEAK_32);
return value;
  }

long ADE9078::getEnergyA(){
	long value=0;
	value=spiAlgorithm16_read(ACCMODE_16);
return value;
  }

float ADE9078::getInstApparentPowerA(){
	long value=0;
	value=spiAlgorithm32_read(AVA_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE9078::getInstApparentPowerB(){
	long value=0;
	value=spiAlgorithm32_read(BVA_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE9078::getInstApparentPowerC(){
	long value=0;
	value=spiAlgorithm32_read(CVA_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }


float ADE9078::getInstActivePowerA(){
	long value=0;
	value=spiAlgorithm32_read(AWATT_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE9078::getInstActivePowerB(){
	long value=0;
	value=spiAlgorithm32_read(BWATT_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE9078::getInstActivePowerC(){
	long value=0;
	value=spiAlgorithm32_read(CWATT_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
}

float ADE9078::getInstReactivePowerA(){
	long value=0;
	value=spiAlgorithm32_read(AVAR_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return decimal;
  }

float ADE9078::getInstReactivePowerB(){
	long value=0;
	value=spiAlgorithm32_read(BVAR_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return decimal;
  }

float ADE9078::getInstReactivePowerC(){
	long value=0;
	value=spiAlgorithm32_read(CVAR_32);
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return decimal;
  }


float ADE9078::read32Bit(uint16_t readRegister)
{
  uint32_t data = spiAlgorithm32_read(readRegister);
  float decimal = decimalize(data, 1.502, 0);
  return abs(decimal);
}


//*******************************************************


//****************ADE 9078 Library Control Functions**************************************

//****************Object Definition*****************
ADE9078::ADE9078(int SS, long SPI_freq)
{
  _SS=SS;
  _SPI_freq=SPI_freq;
  }
//**************************************************

//****************Initialization********************
void ADE9078::initialize(struct InitializationSettings is){

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078:initialize function started ");
  #endif

  // Arduino setup
  SPI.begin();
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  // Clock is high when inactive. Read at rising edge: SPIMODE3.

  pinMode(_SS, OUTPUT); // FYI: SS is pin 10 by Arduino's SPI library on many boards (including the UNO), set SS pin as Output
  SPI.setBitOrder(MSBFIRST);  //Define MSB as first (explicitly)
  digitalWrite(_SS, HIGH); //Initialize pin as HIGH to bring communication inactive
  delay(50);

  // Page 56 of datasheet quick start
  // #1: Ensure power sequence completed
  delay(30);
  int status1Data = read32Bit(STATUS1_32);
  if (!checkBit(read32Bit(STATUS1_32), 16)) {
    Serial.print("WARNING, POWER UP MAY NOT BE FINISHED");
  }

    // #2: Configure Gains
    spiAlgorithm32_write(APGAIN_32, is.powerAGain);
    spiAlgorithm32_write(BPGAIN_32, is.powerBGain);
    spiAlgorithm32_write(CPGAIN_32, is.powerCGain);

    // first 2 reserved, next 6 are v gains, next 8 are i gains.
    uint16_t pgaGain = (is.vCGain << 12) + (is.vBGain << 10) + (is.vCGain << 8) +
                      (is.iNGain << 6) + (is.iCGain << 4) + (is.iBGain << 2) + is.iAGain;
    spiAlgorithm16_write(PGA_GAIN_16, pgaGain);

    // #5 : Write VLevel 0x117514
    spiAlgorithm32_write(VLEVEL_32, 0x117514); // #5

    // #7:  If current transformers are used, INTEN and ININTEN in the CONFIG0 register must = 0
  spiAlgorithm16_write(CONFIG0_32, 0x00000000);
  // Table 24 to determine how to configure ICONSEL and VCONSEL in the ACCMODE register
  uint16_t settingsACCMODE = (is.iConsel << 6) + (is.vConsel << 5);
  spiAlgorithm16_write(ACCMODE_16, settingsACCMODE); // chooses 4 wire WYE Blondel

  // 8: Write 1 to Run register
  spiAlgorithm16_write(RUN_16, 1);

  // 9: Write 1 to EP_CFG register
  spiAlgorithm16_write(EP_CFG_16, 1);

  /*
  Potentially useful registers to configure:
  The following were in the 7953:
    0x49A ZX_LP_SEL : to configure "zero crossing signal"
    0x41F PHNOLOAD : To say if something is "no load".
    Phase calibrations, such as APHCAL1_32
  */

  spiAlgorithm16_write(CONFIG1_16, 0x0000);
  spiAlgorithm16_write(CONFIG2_16, 0x0000);
  spiAlgorithm16_write(CONFIG3_16, 0x0000);
  spiAlgorithm32_write(DICOEFF_32, 0xFFFFE000); // Recommended by datasheet
  /* Registers configured in ADE9000 code */
  // zx_lp_sel
  // mask0, mask1, event_mask,
  // wfb_cfg,
  // EGY_TIME
  // EP_CFG

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078:initialize function completed ");
  #endif

}
//**************************************************

uint16_t ADE9078::spiAlgorithm16_read(uint16_t address) { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print("ADE9078::spiAlgorithm16_read function started ");
    #endif

    // See SPI protocol in datasheet to understand this.
    // Around p 62ish

    uint8_t isRead = 1;

    // contains upper 8 bits of address
    uint8_t commandHeader1 = (address >> 4);

    // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
    uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

    byte one, two;
	byte dummyWrite = 0x00;

    // beginTransaction is first
    SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  // Clock is high when inactive. Read at rising edge: SPIMODE3.

    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

    SPI.transfer(commandHeader1);
    SPI.transfer(commandHeader2);

    //Read in values sequentially and bitshift for a 32 bit entry
    one = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    two = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

    // endTransaction is last
    SPI.endTransaction();

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print("ADE9078::spiAlgorithm16_read function details: ");
     Serial.print("Address Byte 1(MSB)[HEX]: ");
     Serial.print(MSB, HEX);
     Serial.print(" Address Byte 2(LSB)[HEX]: ");
     Serial.print(LSB, HEX);
     Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
     Serial.print(one, HEX);
     Serial.print(" ");
     Serial.print(two, HEX);
     Serial.print(" ADE9078::spiAlgorithm16_read function completed ");
    #endif

    return (((uint32_t) one << 8) + ((uint32_t) two));  //Alternate Bitshift algorithm)
}


uint32_t ADE9078::spiAlgorithm32_read(uint16_t address) { //This is the algorithm that reads from a 32 bit register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.  Caution, some register elements contain information that is only 24 bit with padding on the MSB
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078::spiAlgorithm32_read function started ");
  #endif

  uint8_t isRead = 1;

  // contains upper 8 bits of address
  uint8_t commandHeader1 = (address >> 4);

  // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
  uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

  byte one, two, three, four;
  byte dummyWrite = 0x00;

  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  // Clock is high when inactive. Read at rising edge: SPIMODE3.

  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.transfer(commandHeader1);
  SPI.transfer(commandHeader2);

  //Read in values sequentially and bitshift for a 32 bit entry
  one = SPI.transfer(dummyWrite); //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  three = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  four = SPI.transfer(dummyWrite); //LSB Byte 4  (Read in data on dummy write (null MOSI signal))

  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

  SPI.endTransaction();

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078::spiAlgorithm32_read function details: ");
   //Serial.print("Address Byte 1(MSB)[HEX]: ");
   //Serial.print(MSB, BIN);
   //Serial.print(" Address Byte 2(LSB)[HEX]: ");
   //Serial.print(LSB, BIN);
   Serial.print(" Returned bytes (1(MSB) to 4)[HEX]: ");
   Serial.print(one, BIN);
   Serial.print(" ");
   Serial.print(two, BIN);
   Serial.print(" ");
   Serial.print(three, BIN);
   Serial.print(" ");
   Serial.print(four, BIN);
   Serial.print(" ADE9078::spiAlgorithm32_read function completed ");
  #endif

  //Post-read packing and bitshifting operations
  return ((uint32_t) one << 24) + ((uint32_t) two << 16) + ((uint32_t) three << 8) + (uint32_t) four;

}


  void ADE9078::spiAlgorithm32_write(uint16_t address, uint32_t data) {

    // IF address IS GREATER THAN 2^12, ERROR. (use only 12 bits)
    // Avoid bit fields so that compiler doesn't pad. If protection is desired,
    // raise errors inside if statements.

    uint8_t isRead = 0;

    // contains upper 8 bits of address
    uint8_t commandHeader1 = (address >> 4);

    // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
    uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

    // To understand these shifts, picture this group of 1's being modified
    // Below is a 32 bit int. We're grabbing 1 byte out at a time. byteFour is the left most byte
    // 1111 1111 1111 1111 1111 1111 1111 1111
    uint8_t byteFour = (data >> 24);
    uint8_t byteThree = (data & 0xFFFFFF) >> 16;
    uint8_t byteTwo = (data & 0xFFFF) >> 8;
    uint8_t byteOne = (data & 0xFF);

    // beginTransaction before writing SS low
    SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  // Clock is high when inactive. Read at rising edge: SPIMODE3.

    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

    // Tell 9078 chip what address, and whether to read or write with commandHeader
    SPI.transfer(commandHeader1);
    SPI.transfer(commandHeader2);

    // Write our data, msb first
    SPI.transfer(byteFour);
    SPI.transfer(byteThree);
    SPI.transfer(byteTwo);
    SPI.transfer(byteOne);

    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

    // endTransaction after writing SS high
    SPI.endTransaction();
  }

  void ADE9078::spiAlgorithm16_write(uint16_t address, uint16_t data) {

    // Same warnings as in 32 bit write.

    uint8_t isRead = 0;

    // contains upper 8 bits of address
    uint8_t commandHeader1 = (address >> 4);

    // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
    uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

    uint8_t MSB_data = (data >> 8);
    uint8_t LSB_data = (data & 0xFF);

    SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  // Clock is high when inactive. Read at rising edge: SPIMODE3.

    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

    SPI.transfer(commandHeader1);
    SPI.transfer(commandHeader2);

    SPI.transfer(MSB_data);
    SPI.transfer(LSB_data);

    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

    SPI.endTransaction();
}
