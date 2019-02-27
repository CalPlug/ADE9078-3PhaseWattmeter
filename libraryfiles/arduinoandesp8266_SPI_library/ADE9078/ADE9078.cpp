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
#define ADE9078_VERBOSE_DEBUG //This line turns on verbose debug via serial monitor (Normally off or //'ed).  Use sparingly and in a test program to debug operation!  Turning this on can take a lot of memory and the delay from USB printing out every statement is taxing temporally!  This is non-specific and for all functions, beware, it's a lot of output!  Reported bytes are in HEX

/*
// This might be a cleaner way of printing debug lines if it gets too messy in the future
#define DEBUG
#ifdef DEBUG
  #define DEBUG_PRINT(x) {Serial.print(x);}
#else
  #define DEBUG_PRINT(x) {}
#endif
*/

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

double decimalize(uint32_t input, double factor, double offset) //This function adds a decimal point to the input value and returns it as a double, it also provides linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE7953::calibration and double type conversion function executed ");
  #endif
return ((double)input/factor)+offset;
}

//**************** End Helper Functions *****************

//****************User Program Functions*****************

uint8_t ADE9078::getVersion(){
  return spiRead16(VERSION_16);
}

double ADE9078::getPowerFactorA(){
	int16_t value=0;
	value=spiRead16(PFA_16);
	double decimal = decimalize(value, 327.67, 0); //convert to double with calibration factors specified
return abs(decimal);
  }

// TODO: double ADE9078::getPowerFactorB(){

// TODO: double ADE9078::getPowerFactorB(){

// which APHCAL should we use? There are 4
uint32_t ADE9078::getPhaseCalibA(){
	uint32_t value=0;
	value=spiRead32(APHCAL0_32);
return value;
  }

// TODO : USER_PERIOD_32
// No period register?
// double ADE9078::getPeriod(){
// 	uint16_t value=0;
// 	value=spiRead16((functionBitVal(Period_16,1)),(functionBitVal(Period_16,0)));
// 	double decimal = decimalize(value, 1, 0); //convert to double with calibration factors specified
// return decimal;
//   }
// might need to edit to access bits for a/b/c
uint32_t ADE9078::getPHNOLOAD(){  //use signed int32_t for signed registers, and unsigned uint32_t for unsigned registers
	uint32_t value=0;  //use signed uint32_t for signed registers, and unsigned uint32_t for unsigned registers
	value=spiRead32(PHNOLOAD_32); //Call MSB and LSB from the register constant (template for how all functions should be called)
return value;
  }


uint32_t ADE9078::getInstVoltageA(){
	uint32_t value=0;
	value=spiRead32(AV_PCF_32);
return value;
  }
uint32_t ADE9078::getInstVoltageB(){
	uint32_t value=0;
	value=spiRead32(BV_PCF_32);
  return value;
}
uint32_t ADE9078::getInstVoltageC(){
	uint32_t value=0;
	value=spiRead32(CV_PCF_32);
  return value;
}

double ADE9078::getAVrms(){
	uint32_t value=0;
	value=spiRead32(AVRMS_32);
	double decimal = decimalize(value, 19090, 0); //convert to double with calibration factors specified
return decimal;
  }

double ADE9078::getBVrms(){
	uint32_t value=0;
	value=spiRead32(BVRMS_32);
	double decimal = decimalize(value, 19090, 0); //convert to double with calibration factors specified
return decimal;
  }

double ADE9078::getCVrms(){
	uint32_t value=0;
	value=spiRead32(CVRMS_32);
	double decimal = decimalize(value, 19090, 0); //convert to double with calibration factors specified
return decimal;
  }

uint32_t ADE9078::getInstCurrentA(){
	uint32_t value=0;
	value=spiRead32(AI_PCF_32);
return value;
  }

uint32_t ADE9078::getInstCurrentB(){
	uint32_t value=0;
	value=spiRead32(BI_PCF_32);
return value;
  }

uint32_t ADE9078::getInstCurrentC(){
	uint32_t value=0;
	value=spiRead32(CI_PCF_32);
return value;
  }

double ADE9078::getIrmsA(){
	uint32_t value=0;
	value=spiRead32(AIRMS_32);
	double decimal = decimalize(value, 1327, 0); //convert to double with calibration factors specified
  return decimal;
}

double ADE9078::getIrmsB(){
	uint32_t value=0;
	value=spiRead32(BIRMS_32);
	double decimal = decimalize(value, 1327, 0); //convert to double with calibration factors specified
  return decimal;
}

double ADE9078::getIrmsC(){
	uint32_t value=0;
	value=spiRead32(CIRMS_32);
	double decimal = decimalize(value, 1327, 0); //convert to double with calibration factors specified
return decimal;
  }


uint32_t ADE9078::getVpeak(){
	uint32_t value=0;
	value=spiRead32(VPEAK_32);
return value;
  }

uint32_t ADE9078::getIpeak(){
	uint32_t value=0;
	value=spiRead32(IPEAK_32);
return value;
  }

uint32_t ADE9078::getEnergyA(){
	uint32_t value=0;
	value=spiRead16(ACCMODE_16);
return value;
  }

double ADE9078::readWattHoursA()
{
  uint32_t data = spiRead32(AWATTHR_HI_32);
  double dec = decimalize(data, 1.502, 0);
  return abs(dec);
}


double ADE9078::getInstApparentPowerA(){
	uint32_t value=0;
	value=spiRead32(AVA_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
  }

double ADE9078::getInstApparentPowerB(){
	uint32_t value=0;
	value=spiRead32(BVA_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
  }

double ADE9078::getInstApparentPowerC(){
	uint32_t value=0;
	value=spiRead32(CVA_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
  }


double ADE9078::getInstActivePowerA(){
	uint32_t value=0;
	value=spiRead32(AWATT_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
  }

double ADE9078::getInstActivePowerB(){
	uint32_t value=0;
	value=spiRead32(BWATT_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
  }

double ADE9078::getInstActivePowerC(){
	uint32_t value=0;
	value=spiRead32(CWATT_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return abs(decimal);
}

double ADE9078::getInstReactivePowerA(){
	uint32_t value=0;
	value=spiRead32(AVAR_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return decimal;
  }

double ADE9078::getInstReactivePowerB(){
	uint32_t value=0;
	value=spiRead32(BVAR_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return decimal;
  }

double ADE9078::getInstReactivePowerC(){
	uint32_t value=0;
	value=spiRead32(CVAR_32);
	double decimal = decimalize(value, 1.502, 0); //convert to double with calibration factors specified
return decimal;
}


double ADE9078::read32BitAndScale(uint16_t readRegister)
{
  uint32_t data = spiRead32(readRegister);
  double decimal = decimalize(data, 1.502, 0);
  return abs(decimal);
}


//*******************************************************


//****************ADE 9078 Library Control Functions**************************************

//****************Object Definition*****************
ADE9078::ADE9078(int SS, long SPI_freq, InitializationSettings* is)
{
  _SS=SS;
  _SPI_freq=SPI_freq;
  this->is = is;
  }
//**************************************************

//****************Initialization********************
void ADE9078::initialize(){

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078:initialize function started ");
  #endif

  // Arduino setup
  SPI.begin();
  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.

  pinMode(_SS, OUTPUT); // FYI: SS is pin 10 by Arduino's SPI library on many boards (including the UNO), set SS pin as Output
  SPI.setBitOrder(MSBFIRST);  //Define MSB as first (explicitly)
  digitalWrite(_SS, HIGH); //Initialize pin as HIGH to bring communication inactive
  delay(50);

  // Page 56 of datasheet quick start
  // #1: Ensure power sequence completed
  delay(30);
  int status1Data = read32BitAndScale(STATUS1_32);
  if (!checkBit(status1Data, 16)) {
    Serial.print("WARNING, POWER UP MAY NOT BE FINISHED");
  }

    // #2: Configure Gains
    spiWrite32(APGAIN_32, is->powerAGain);
    spiWrite32(BPGAIN_32, is->powerBGain);
    spiWrite32(CPGAIN_32, is->powerCGain);

    // first 2 reserved, next 6 are v gains, next 8 are i gains.
    uint16_t pgaGain = (is->vCGain << 12) + (is->vBGain << 10) + (is->vCGain << 8) +
                      (is->iNGain << 6) + (is->iCGain << 4) + (is->iBGain << 2) + is->iAGain;

    spiWrite16(PGA_GAIN_16, pgaGain);

    // #5 : Write VLevel 0x117514
    uint32_t vLevelData = 0x117514;
    spiWrite32(VLEVEL_32, vLevelData); // #5

    // #7:  If current transformers are used, INTEN and ININTEN in the CONFIG0 register must = 0
  spiWrite16(CONFIG0_32, 0x00000000);
  // Table 24 to determine how to configure ICONSEL and VCONSEL in the ACCMODE register
  uint16_t settingsACCMODE = (is->iConsel << 6) + (is->vConsel << 5);
  spiWrite16(ACCMODE_16, settingsACCMODE); // chooses 4 wire WYE Blondel

  // 8: Write 1 to Run register
  spiWrite16(RUN_16, 1);

  // 9: Write 1 to EP_CFG register
  spiWrite16(EP_CFG_16, 1);

  /*
  Potentially useful registers to configure:
  The following were in the 7953:
    0x49A ZX_LP_SEL : to configure "zero crossing signal"
    0x41F PHNOLOAD : To say if something is "no load".
    Phase calibrations, such as APHCAL1_32
  */

  spiWrite16(CONFIG1_16, 0x0000);
  spiWrite16(CONFIG2_16, 0x0000);
  spiWrite16(CONFIG3_16, 0x0000);
  spiWrite32(DICOEFF_32, 0xFFFFE000); // Recommended by datasheet
  /* Registers configured in ADE9000 code */
  // zx_lp_sel
  // mask0, mask1, event_mask,
  // wfb_cfg,
  spiWrite16(EGY_TIME_16, 0x0001);
  spiWrite16(EP_CFG_16, 0x0021); // RD_EST_EN=1, EGY_LD_ACCUM=0, EGY_TMR_MODE=0, EGY_PWR_EN=1

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078:initialize function completed. Showing values and registers written ");
   Serial.print("APGAIN: ");
   Serial.print(is->powerAGain);
   Serial.print("BPGAIN: ");
   Serial.print(is->powerBGain);
   Serial.print("CPGAIN: ");
   Serial.print(is->powerCGain);
   Serial.print("PGA_GAIN: ");
   Serial.print(pgaGain);
   Serial.print("VLEVEL: ");
   Serial.print(vLevelData);
   Serial.print("CONFIG0-3, ALL 0'S");
   Serial.print("ACCMODE: ");
   Serial.print(settingsACCMODE);
   Serial.print("RUN: ");
   Serial.print(1);
   Serial.print("EP_CFG: ");
   Serial.print(1);
   Serial.print("DICOEFF: ");
   Serial.print(0xFFFFE000);
  #endif
}
//**************************************************

uint16_t ADE9078::spiRead16(uint16_t address) { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print("ADE9078::spiRead16 function started ");
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
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.

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
     Serial.print("ADE9078::spiRead16 function details: ");
     Serial.print("Command Header: ");
     Serial.print(commandHeader1);
     Serial.print(commandHeader2);
     Serial.print("Address Byte 1(MSB)[HEX]: ");
     Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
     Serial.print(one, HEX);
     Serial.print(" ");
     Serial.print(two, HEX);
     Serial.print(" ADE9078::spiRead16 function completed ");
    #endif

    return (((uint32_t) one << 8) + ((uint32_t) two));  //Alternate Bitshift algorithm)
}


uint32_t ADE9078::spiRead32(uint16_t address) { //This is the algorithm that reads from a 32 bit register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.  Caution, some register elements contain information that is only 24 bit with padding on the MSB
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078::spiRead32 function started ");
  #endif

  uint8_t isRead = 1;

  // contains upper 8 bits of address
  uint8_t commandHeader1 = (address >> 4);

  // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
  uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

  byte one, two, three, four;
  byte dummyWrite = 0x00;

  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.

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

  Serial.print(" Returned bytes 1-4, 1 is MSB [HEX]: ");

   Serial.print("ADE9078::spiRead32 function details: ");
   Serial.print("Command Header: ");
   Serial.print(commandHeader1);
   Serial.print(commandHeader2);

   Serial.print("Returned bytes (1(MSB) to 4)[BINARY]: ");
   Serial.print(one, BIN);
   Serial.print(" ");
   Serial.print(two, BIN);
   Serial.print(" ");
   Serial.print(three, BIN);
   Serial.print(" ");
   Serial.print(four, BIN);
  #endif

  //Post-read packing and bitshifting operations
  return ((uint32_t) one << 24) + ((uint32_t) two << 16) + ((uint32_t) three << 8) + (uint32_t) four;

}

void ADE9078::spiWrite16(uint16_t address, uint16_t data) {

  // Same warnings as in 32 bit write.

  uint8_t isRead = 0;

  // contains upper 8 bits of address
  uint8_t commandHeader1 = (address >> 4);

  // contains lower 4 bits of address, followed by a isRead bit, followed by 3 don't cares
  uint8_t commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

  uint8_t MSB_data = (data >> 8);
  uint8_t LSB_data = (data & 0xFF);

  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.

  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

  SPI.transfer(commandHeader1);
  SPI.transfer(commandHeader2);

  SPI.transfer(MSB_data);
  SPI.transfer(LSB_data);

  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

  SPI.endTransaction();

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print("ADE9078::spiRead32 function details: ");
   Serial.print("Command Header: ");
   Serial.print(commandHeader1);
   Serial.print(commandHeader2);
   Serial.print(" Wrote bytes (2(MSB) to 1)[BINARY]: ");
   Serial.print(MSB_data, BIN);
   Serial.print(" ");
   Serial.print(LSB_data, BIN);
   Serial.print(" ADE9078::spiRead32 function completed ");
  #endif
}

  void ADE9078::spiWrite32(uint16_t address, uint32_t data) {

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
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.

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

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print("ADE9078::spiRead32 function details: ");
     Serial.print("Command Header: " + commandHeader1 + commandHeader2);
     Serial.print(" Wrote bytes (4(MSB) to 1)[BINARY]: ");
     Serial.print(byteFour, BIN);
     Serial.print(" ");
     Serial.print(byteThree, BIN);
     Serial.print(" ");
     Serial.print(byteTwo, BIN);
     Serial.print(" ");
     Serial.print(byteOne, BIN);
     Serial.print(" ADE9078::spiRead32 function completed ");
    #endif

  }
