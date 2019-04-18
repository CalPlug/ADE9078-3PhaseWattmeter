/* ADE9078
 ADE9078.cpp - Example library for operating the ADE9078 Three-Phase AC Line measurement IC over SPI for Arduino Uno/AVR/ESP8266
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

#include "Arduino.h"
#include <SPI.h>  //Arduino SPI SPI library, may not always be needed for ESP32 use
#include "ADE9078.h"
#include "ADE9078Calibrations.h"
#include "ADEutility.h"

#ifdef ESP32ARCH
	#include "esp32-hal-spi.h"
	spi_t * spy; //for ESP32, create object for SPI
#endif



//****************User Program Available Functions*****************

uint8_t ADE9078::getVersion(){
	return spiRead16(VERSION_16);
}

double ADE9078::getPowerFactorA(){
	int16_t value=0;
	value=spiRead16(PFA_16);
	double decimal = decimalize(value, 1.0, 0.0,0); //convert to double with calibration factors specified (default values in place)
	return (decimal);
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
// 	double decimal = decimalize(value, 1, 0,0); //convert to double with calibration factors specified
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

void ADE9078::readVoltage()
{
    lastReads.instVoltage.a = spiRead32(AV_PCF_32);
    lastReads.instVoltage.b = spiRead32(BV_PCF_32);
    lastReads.instVoltage.c = spiRead32(CV_PCF_32);
}

double ADE9078::getAVrms(){
	uint32_t value=0;
	value=spiRead32(AVRMS_32);
	double decimal = decimalize(value, AVrmsGain, AVrmsOffset,0); //convert to double with calibration factors specified, no abs value
	return decimal;
}

double ADE9078::getBVrms(){
	uint32_t value=0;
	value=spiRead32(BVRMS_32);
	double decimal = decimalize(value, BVrmsGain, BVrmsOffset,0); //convert to double with calibration factors specified, no abs value
	return decimal;
}

double ADE9078::getCVrms(){
	uint32_t value=0;
	value=spiRead32(CVRMS_32);
	double decimal = decimalize(value, CVrmsGain, CVrmsOffset,0); //convert to double with calibration factors specified,  no abs value
	return decimal;
}

void ADE9078::readVrms()
{
    lastReads.vrms.a = int32_t(decimalize(spiRead32(AVRMS_32), AVrmsGain, AVrmsOffset, 0));
    lastReads.vrms.b = int32_t(decimalize(spiRead32(BVRMS_32), BVrmsGain, BVrmsOffset, 0));
    lastReads.vrms.c = int32_t(decimalize(spiRead32(CVRMS_32), CVrmsGain, CVrmsOffset, 0));
}


double ADE9078::getIrmsA(){
	uint32_t value=0;
	value=spiRead32(AIRMS_32);
	double decimal = decimalize(value, AIrmsGain, AIrmsOffset,0); //convert to double with calibration factors specified
	return decimal;
}

double ADE9078::getIrmsB(){
	uint32_t value=0;
	value=spiRead32(BIRMS_32);
	double decimal = decimalize(value, BIrmsGain, BIrmsOffset,0); //convert to double with calibration factors specified
	return decimal;
}

double ADE9078::getIrmsC(){
	uint32_t value=0;
	value=spiRead32(CIRMS_32);
	double decimal = decimalize(value, CIrmsGain, CIrmsOffset, 0); //convert to double with calibration factors specified
	return decimal;
}

void ADE9078::readIrms()
{
    lastReads.irms.a = int32_t(decimalize(spiRead32(AIRMS_32), AIrmsGain, AIrmsOffset, 0));
    lastReads.irms.b = int32_t(decimalize(spiRead32(BIRMS_32), BIrmsGain, BIrmsOffset, 0));
    lastReads.irms.c = int32_t(decimalize(spiRead32(CIRMS_32), CIrmsGain, CIrmsOffset, 0));
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

void ADE9078::readInstCurrent()
{
    lastReads.instCurrent.a = spiRead32(AI_PCF_32);
    lastReads.instCurrent.b = spiRead32(BI_PCF_32);
    lastReads.instCurrent.c = spiRead32(CI_PCF_32);
}


double ADE9078::readWattHoursA(){
	uint32_t data = spiRead32(AWATTHR_HI_32);
	double decimal = decimalize(data, AWattHrGain, AWattHrOffset,0);
	return (decimal);
}

double ADE9078::readWattHoursB(){
	uint32_t data = spiRead32(BWATTHR_HI_32);
	double decimal = decimalize(data, AWattHrGain, AWattHrOffset,0);
	return (decimal);
}

double ADE9078::readWattHoursC(){
	uint32_t data = spiRead32(CWATTHR_HI_32);
	double decimal = decimalize(data, AWattHrGain, AWattHrOffset,0);
	return (decimal);
}

void ADE9078::readWattHours()
{
    lastReads.wattHours.a = decimalize(spiRead32(AWATTHR_HI_32), AWattHrGain, AWattHrOffset, 0);
    lastReads.wattHours.b = decimalize(spiRead32(BWATTHR_HI_32), BWattHrGain, BWattHrOffset, 0);
    lastReads.wattHours.c = decimalize(spiRead32(CWATTHR_HI_32), CWattHrGain, CWattHrOffset, 0);
}

void ADE9078:: readFundamentalReactivePower()
{
	lastReads.fundReactPower.a = int32_t (spiRead32(AFVAR_32));
	lastReads.fundReactPower.b = int32_t (spiRead32(AFVAR_32));
	lastReads.fundReactPower.c = int32_t (spiRead32(AFVAR_32));
}

void ADE9078::readFilterBasedCurrent()
{
	lastReads.filterBasedCurrent.a = int32_t (spiRead32(AIRMS_32));
	lastReads.filterBasedCurrent.b = int32_t (spiRead32(BIRMS_32));
	lastReads.filterBasedCurrent.c = int32_t (spiRead32(CIRMS_32));
	lastReads.filterBasedCurrent.n = int32_t (spiRead32(NIRMS_32));
}

void ADE9078::readPowerFactor()
{
    // not sure what 9000 code is doing with the values
    lastReads.powerFactor.regA = int32_t(spiRead32(APF_32));
    // lastReads.powerFactor.valA =
    lastReads.powerFactor.regB = int32_t(spiRead32(BPF_32));
    // lastReads.powerFactor.valB =
    lastReads.powerFactor.regC = int32_t(spiRead32(CPF_32));
    // lastReads.powerFactor.valC =
}

void ADE9078::readPeriod()
{
    lastReads.period.a = int32_t(spiRead32(APERIOD_32));
    lastReads.period.b = int32_t(spiRead32(APERIOD_32));
    lastReads.period.c = int32_t(spiRead32(APERIOD_32));
    // 9000 code also calculates some values here?
}

double ADE9078::getInstApparentPowerA(){
	uint32_t value=0;
	value=spiRead32(AVA_32);
	double decimal = decimalize(value, AAppPowerGain, AAppPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

double ADE9078::getInstApparentPowerB(){
	uint32_t value=0;
	value=spiRead32(BVA_32);
	double decimal = decimalize(value, BAppPowerGain, BAppPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

double ADE9078::getInstApparentPowerC(){  //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(CVA_32);
	double decimal = decimalizeSigned(value, CAppPowerGain, CAppPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

void ADE9078::readInstApparentPower()
{
    lastReads.instApparentPower.a = int32_t(decimalizeSigned(spiRead32(AVA_32), AAppPowerGain, AAppPowerOffset, 0));
    lastReads.instApparentPower.b = int32_t(decimalizeSigned(spiRead32(BVA_32), BAppPowerGain, BAppPowerOffset, 0));
    lastReads.instApparentPower.c = int32_t(decimalizeSigned(spiRead32(CVA_32), CAppPowerGain, CAppPowerOffset, 0));
}


double ADE9078::getInstActivePowerA(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(AWATT_32);
	double decimal = decimalizeSigned(value, AInstPowerGain, AInstPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

double ADE9078::getInstActivePowerB(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(BWATT_32);
	double decimal = decimalizeSigned(value, BInstPowerGain, BInstPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

double ADE9078::getInstActivePowerC(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(CWATT_32);
	double decimal = decimalizeSigned(value, CInstPowerGain, CInstPowerOffset,0); //convert to double with calibration factors specified
	return (decimal);
}

void ADE9078::readInstActivePower()
{
    lastReads.instActivePower.a = int32_t(decimalizeSigned(spiRead32(AWATT_32), AInstPowerGain, AInstPowerOffset, 0));
    lastReads.instActivePower.b = int32_t(decimalizeSigned(spiRead32(BWATT_32), BInstPowerGain, BInstPowerOffset, 0));
    lastReads.instActivePower.c = int32_t(decimalizeSigned(spiRead32(CWATT_32), CInstPowerGain, CInstPowerOffset, 0));
}

double ADE9078::getInstReactivePowerA(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(AVAR_32);
	double decimal = decimalizeSigned(value, AInstReactivePowerGain, AInstReactivePowerOffset,0); //convert to double with calibration factors specified
	return decimal;
  }

double ADE9078::getInstReactivePowerB(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(BVAR_32);
	double decimal = decimalizeSigned(value, BInstReactivePowerGain, BInstReactivePowerOffset,0); //convert to double with calibration factors specified
	return decimal;
}

double ADE9078::getInstReactivePowerC(){ //type conversion approach used for the ADE9000
	int32_t value = (int32_t)spiRead32(CVAR_32);
	double decimal = decimalizeSigned(value, CInstReactivePowerGain, CInstReactivePowerOffset,0); //convert to double with calibration factors specified
	return decimal;
}

void ADE9078::readInstReactivePower()
{
    lastReads.instReactivePower.a = int32_t(decimalizeSigned(spiRead32(AVAR_32), AInstReactivePowerGain, AInstReactivePowerOffset, 0));
    lastReads.instReactivePower.b = int32_t(decimalizeSigned(spiRead32(BVAR_32), BInstReactivePowerGain, BInstReactivePowerOffset, 0));
    lastReads.instReactivePower.c = int32_t(decimalizeSigned(spiRead32(CVAR_32), CInstReactivePowerGain, CInstReactivePowerOffset, 0));
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

void ADE9078::readPeak()
{
    lastReads.peak.Vpeak = spiRead32(VPEAK_32);
    lastReads.peak.Ipeak = spiRead32(IPEAK_32);
}


double ADE9078::read32BitAndScale(uint16_t readRegister){
	uint32_t data = spiRead32(readRegister);
	double decimal = decimalize(data, 1.0, 0.0,0);
	return (decimal);
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

//****************Hardware Initialization********************
void ADE9078::initialize(){

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078:initialize function started"); //wiring configuration defined in VCONSEL and ICONSEL registers init. in this function
  #endif

    /* //For reference, the following registers are written to on bootup for the ADE9000 (from ADE9000 Arduino Library Sample Code, note these ICs are similar but do not have identical functionality!)
   SPI_Write_16(ADDR_PGA_GAIN,ADE9000_PGA_GAIN);
 	 SPI_Write_32(ADDR_CONFIG0,ADE9000_CONFIG0);
	 SPI_Write_16(ADDR_CONFIG1,ADE9000_CONFIG1);
	 SPI_Write_16(ADDR_CONFIG2,ADE9000_CONFIG2);
	 SPI_Write_16(ADDR_CONFIG3,ADE9000_CONFIG3);
	 SPI_Write_16(ADDR_ACCMODE,ADE9000_ACCMODE);
	 SPI_Write_16(ADDR_TEMP_CFG,ADE9000_TEMP_CFG);
	 SPI_Write_16(ADDR_ZX_LP_SEL,ADE9000_ZX_LP_SEL);
	 SPI_Write_32(ADDR_MASK0,ADE9000_MASK0);
	 SPI_Write_32(ADDR_MASK1,ADE9000_MASK1);
	 SPI_Write_32(ADDR_EVENT_MASK,ADE9000_EVENT_MASK);
	 SPI_Write_16(ADDR_WFB_CFG,ADE9000_WFB_CFG);
	 SPI_Write_32(ADDR_VLEVEL,ADE9000_VLEVEL);
	 SPI_Write_32(ADDR_DICOEFF,ADE9000_DICOEFF);
	 SPI_Write_16(ADDR_EGY_TIME,ADE9000_EGY_TIME);
	 SPI_Write_16(ADDR_EP_CFG,ADE9000_EP_CFG);		//Energy accumulation ON
	 SPI_Write_16(ADDR_RUN,ADE9000_RUN_ON);		//DSP ON
	 */


  // ESP32 Architecture setup
  #ifdef ESP32ARCH  //example SPI routine for the ESP32
  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE3, SPI_MSBFIRST);
  spiAttachSCK(spy, -1);
  spiAttachMOSI(spy, -1);
  spiAttachMISO(spy, -1);
  pinMode(_SS, OUTPUT);
  spiStopBus(spy);
  digitalWrite(_SS, HIGH); //Disable data transfer by bringing SS line HIGH
  delay(50);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
  SPI.begin();
  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3 or 0 modes.
  pinMode(_SS, OUTPUT); // FYI: SS is pin 10 by Arduino's SPI library on many boards (including the UNO), set SS pin as Output
  SPI.setBitOrder(MSBFIRST);  //Define MSB as first (explicitly)
  SPI.endTransaction(); //end SPI communication
  digitalWrite(_SS, HIGH); //Initialize pin as HIGH to bring communication inactive
  delay(50);
  #endif

  // Page 56 of datasheet quick start
  // #1: Ensure power sequence completed
  delay(30);

  // Is always printing right now. Might be an issue?
  // if (!checkBit((int)read32BitAndScale(STATUS1_32), 16)) {
  //   Serial.println("WARNING, POWER UP MAY NOT BE FINISHED");
  // }
   // #2: Configure Gains
   spiWrite32(APGAIN_32, is->powerAGain);
   spiWrite32(BPGAIN_32, is->powerBGain);
   spiWrite32(CPGAIN_32, is->powerCGain);

   uint16_t pgaGain = (is->vCGain << 12) + (is->vBGain << 10) + (is->vCGain << 8) +   // first 2 reserved, next 6 are v gains, next 8 are i gains.
                      (is->iNGain << 6) + (is->iCGain << 4) + (is->iBGain << 2) + is->iAGain;
   spiWrite16(PGA_GAIN_16, pgaGain);
   uint32_t vLevelData = 0x117514;  // #5 : Write VLevel 0x117514
   spiWrite32(VLEVEL_32, vLevelData); // #5

  spiWrite16(CONFIG0_32, 0x00000000);  // #7:  If current transformers are used, INTEN and ININTEN in the CONFIG0 register must = 0
  // Table 24 to determine how to configure ICONSEL and VCONSEL in the ACCMODE register
  uint16_t settingsACCMODE = (is->iConsel << 6) + (is->vConsel << 5);

	spiWrite16(ACCMODE_16, settingsACCMODE); // chooses the wiring mode (delta/Wye, Blondel vs. Non-blondel) to push up in initial config, Need the other if statements for all configuration modes

  spiWrite16(RUN_16, 1);  // 8: Write 1 to Run register
  spiWrite16(EP_CFG_16, 1);  // 9: Write 1 to EP_CFG register

  /*
  Potentially useful registers to configure:
  The following were in the 9078:
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
   Serial.print(" APGAIN: ");
   Serial.print(is->powerAGain);
   Serial.print(" BPGAIN: ");
   Serial.print(is->powerBGain);
   Serial.print(" CPGAIN: ");
   Serial.print(is->powerCGain);
   Serial.print(" PGA_GAIN: ");
   Serial.print(pgaGain);
   Serial.print(" VLEVEL: ");
   Serial.print(vLevelData);
   Serial.print(" CONFIG0-3, ALL 0'S");
   Serial.print(" ACCMODE: ");
   Serial.print(settingsACCMODE);
   Serial.print(" RUN: ");
   Serial.print(1);
   Serial.print(" EP_CFG: ");
   Serial.print(1);
   Serial.print(" DICOEFF: ");
   Serial.println(0xFFFFE000);
  #endif
}
//**************************************************

void ADE9078::configureWFB(int begin)
{
	//  0000 0000 0000 0000
	// 15   11    7    3     shifts to get to location
		uint16_t wfb_cfg = 0; // first 3 bits are reserved
		wfb_cfg += (1 << 12); // yes, we are reading I Neutral
		// next 2 bits reserved
		// 0001 0011 0000 0000
		wfb_cfg += (B11 << 9); // use voltage/current waveform samples
		wfb_cfg += (B00 << 7); // stop when waveform buffer is full
		wfb_cfg += (0   << 5); // use resampled, not fixed
		wfb_cfg += (begin   << 4); // begin sampling or maintain?
		wfb_cfg += (0b0000);   // read all channels
		spiWrite16(WFB_CFG_16, wfb_cfg);
}

bool ADE9078::isDoneSampling()
{
		uint16_t status = spiRead32(STATUS0_32);
		// 23rd bit needs to be 1 to be true
		return checkBit(status, 23);
}

/* Burst read, resampled waveform */
void ADE9078::spiBurstResampledWFB(uint16_t startingAddress)
{
	Serial.print("Begin BurstResample | ");
  	SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
	digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

	Serial.print("StartingAddress: ");
	Serial.print(startingAddress, HEX);
	Serial.print(" | ");
	Serial.print("Transfering commandheader: ");
	uint16_t commandHeader = ((startingAddress << 4)& 0xFFF0) + 8;
	Serial.print(commandHeader, HEX);
	Serial.print(" | ");
	SPI.transfer16(commandHeader);
  	//SPI.transfer16(((startingAddress << 4) & 0xFFF0)+8);  //Send the starting address, read mode


	Serial.print("Begin forloop");
	for(int i=0; i < WFB_RESAMPLE_SEGMENTS; i++)
	{
		  lastReads.resampledData.Ia[i] = SPI.transfer16(0);
		  lastReads.resampledData.Va[i] = SPI.transfer16(0);
		  lastReads.resampledData.Ib[i] = SPI.transfer16(0);
		  lastReads.resampledData.Vb[i] = SPI.transfer16(0);
		  lastReads.resampledData.Ic[i] = SPI.transfer16(0);
		  lastReads.resampledData.Vc[i] = SPI.transfer16(0);
		  lastReads.resampledData.In[i] = SPI.transfer16(0);
      // no transfer16 here for the space? if it doesnt work, maybe add
	}
	Serial.println("End for loop");

	digitalWrite(_SS, HIGH);  //Enable data transfer by bringing SS line LOW
	SPI.endTransaction();

}

//NOTE: This is an example function, 8 Bit registers for returned values are not used in the ADE9078
uint8_t ADE9078::spiRead8(uint16_t address)  { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
   //Prepare the 12 bit command header from the inbound address provided to the function
   uint16_t temp_address;
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::spiAlgorithm8_read function started ");
  #endif
  uint8_t readval_unsigned = 0;  //This variable is the unsigned integer value to compile read bytes into (if needed)
  byte one, two; // the second input, byte2 is a dummy placeholder read in value: likely the ADE9078 is outputting an extra byte as a 16 bit response even for a 1 byte return
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW

  #ifdef ESP32ARCH  //example SPI routine for the ESP32
  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
  spiAttachSCK(spy, -1);
  spiAttachMOSI(spy, -1);
  spiAttachMISO(spy, -1);
  digitalWrite(_SS, LOW); //Bring SS LOW (Active)
  spiTransferByte(spy, commandHeader1); //Send MSB
  spiTransferByte(spy, commandHeader2);  //Send LSB
  one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
  two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
  spiStopBus(spy);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
  SPI.beginTransaction(defaultSPISettings);  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(commandHeader1);  //Pass in MSB of register to be read first.
  SPI.transfer(commandHeader2);  //Pass in LSB of register to be read next.
  //Read in values sequentially and bitshift for a 32 bit entry
  one = (SPI.transfer(dummyWrite));  //MSB Byte 1  (Read in data on dummy write (null MOSI signal)) - only one needed as 1 byte
  two = (SPI.transfer(dummyWrite));  //"LSB "Byte 2?"  (Read in data on dummy write (null MOSI signal)) - only one needed as 1 byte, but it seems like it responses will send a byte back in 16 bit response total, likely this LSB is useless, but for timing it will be collected.  This may always be a duplicate of the first byte,
  SPI.endTransaction(); //end SPI communication
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH (device made inactive)
  #endif

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::spiAlgorithm8_read function details: ");
   Serial.print(" Address Byte 1(MSB)[HEX]: ");
   Serial.print(commandHeader1, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(commandHeader2, HEX);
   Serial.print(" Returned bytes (1(MSB) and 2 - 2nd is for 16-bit return form): ");
   Serial.print(one, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.println(" ADE9078::spiAlgorithm8_read function completed ");
  #endif

  //Post-read packing and bitshifting operation
    readval_unsigned = one;  //Process MSB (nothing much to see here for only one 8 bit value - nothing to shift), ignore second value read.
	return readval_unsigned;  //uint8_t versus long because it is only an 8 bit value, function returns uint8_t.
 }

uint16_t ADE9078::spiRead16(uint16_t address) { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16 function started ");
    #endif
   //Prepare the 12 bit command header from the inbound address provided to the function
   uint16_t temp_address, readval_unsigned;
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

    byte one, two; //holders for the read values from the SPI Transfer

	#ifdef ESP32ARCH  //example SPI routine for the ESP32
	  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
	  spiAttachSCK(spy, -1);
      spiAttachMOSI(spy, -1);
      spiAttachMISO(spy, -1);
      digitalWrite(_SS, LOW); //Bring SS LOW (Active)
      spiTransferByte(spy, commandHeader1); //Send MSB
      spiTransferByte(spy, commandHeader2);  //Send LSB
      one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
      two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
      digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
      spiStopBus(spy);
	#endif

	#ifdef AVRESP8266 //Arduino SPI Routine
    // beginTransaction is first
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
    SPI.transfer(commandHeader1);  //Transfer first byte (MSB), command
    SPI.transfer(commandHeader2);  ;//Transfer second byte (LSB), command
    //Read in values sequentially and bitshift for a 32 bit entry
    one = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    two = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
    SPI.endTransaction();      // end SPI Transaction
	#endif

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16 function details: ");
     Serial.print(" Command Header: ");
     Serial.print(commandHeader1, BIN);
     Serial.print(commandHeader2, BIN);
     Serial.print(" Address Byte 1(MSB)[HEX]: ");
     Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
     Serial.print(one, HEX); //print MSB
     Serial.print(" ");
     Serial.print(two, HEX);  //print LSB
     Serial.println(" ADE9078::spiRead16 function completed ");
    #endif

	readval_unsigned = (one << 8);  //Process MSB  (Alternate bitshift algorithm)
    readval_unsigned = readval_unsigned + two;  //Process LSB
	return readval_unsigned;
}

uint32_t ADE9078::spiRead32(uint16_t address) { //This is the algorithm that reads from a 32 bit register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.  Caution, some register elements contain information that is only 24 bit with padding on the MSB
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::spiRead32 function started ");
  #endif

   //Prepare the 12 bit command header from the inbound address provided to the function
   uint16_t temp_address;
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

  byte one, two, three, four; //holders for the read values from the SPI Transfer

  #ifdef ESP32ARCH  //example SPI routine for the ESP32
  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
  spiAttachSCK(spy, -1);
  spiAttachMOSI(spy, -1);
  spiAttachMISO(spy, -1);
  digitalWrite(_SS, LOW); //Bring SS LOW (Active)
  spiTransferByte(spy, commandHeader1); //Send MSB
  spiTransferByte(spy, commandHeader2);  //Send LSB
  one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
  two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  three = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  four = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
  spiStopBus(spy);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.transfer(commandHeader1);  //MSB Byte 1
  SPI.transfer(commandHeader2);
  //Read in values sequentially and bitshift for a 32 bit entry
  one = SPI.transfer(dummyWrite); //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  three = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  four = SPI.transfer(dummyWrite); //LSB Byte 4  (Read in data on dummy write (null MOSI signal))
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  SPI.endTransaction();
  #endif

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" Returned bytes 1-4, 1 is MSB [HEX]: ");
   Serial.print(" ADE9078::spiRead32 function details: ");
   Serial.print(" Command Header: ");
   Serial.print(commandHeader1, BIN);
   Serial.print(commandHeader2, BIN);
   Serial.print(" Returned bytes (1(MSB) to 4)[BINARY]: ");
   Serial.print(one, BIN);
   Serial.print(" ");
   Serial.print(two, BIN);
   Serial.print(" ");
   Serial.print(three, BIN);
   Serial.print(" ");
   Serial.println(four, BIN);
  #endif

  //Post-read packing and bitshifting operations
  return (((uint32_t) one << 24) + ((uint32_t) two << 16) + ((uint32_t) three << 8) + (uint32_t) four);
}

void ADE9078::spiWrite16(uint16_t address, uint16_t data) {

   //Prepare the 12 bit command header from the inbound address provided to the function
   uint16_t temp_address;
   temp_address = ((address << 4) & 0xFFF0);	//shift address to align with cmd packet, convert the 16 bit address into the 12 bit command header
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

  //Structure inbound function data into two bytes to send out over SPI sequentially, MSB is sent first
  uint8_t byteTwo = (data >> 8);
  uint8_t byteOne = (data & 0xFF);

  #ifdef ESP32ARCH  //example SPI routine for the ESP32
  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
  spiAttachSCK(spy, -1);
  spiAttachMOSI(spy, -1);
  spiAttachMISO(spy, -1);
  digitalWrite(_SS, LOW); //Bring SS LOW (Active)
  spiTransferByte(spy, commandHeader1); //Send MSB
  spiTransferByte(spy, commandHeader2);  //Send LSB
  spiTransferByte(spy, byteTwo);  //dummy write MSB, read out MSB
  spiTransferByte(spy, byteOne);  //dummy write LSB, read out LSB
  digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
  spiStopBus(spy);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.transfer(commandHeader1);
  SPI.transfer(commandHeader2);
  SPI.transfer(byteTwo);  // Write our data, msb first
  SPI.transfer(byteOne);
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  SPI.endTransaction();
  #endif

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::spiRead32 function details: ");
   Serial.print("Command Header: ");
   Serial.print(commandHeader1);
   Serial.print(commandHeader2);
   Serial.print(" Wrote bytes (2(MSB) to 1)[BINARY]: ");
   Serial.print(byteTwo, BIN);
   Serial.print(" ");
   Serial.print(byteOne, BIN);
   Serial.println(" ADE9078::spiRead32 function completed ");
  #endif
}

  void ADE9078::spiWrite32(uint16_t address, uint32_t data) {

	//Prepare the 12 bit command header from the inbound address provided to the function
	uint16_t temp_address;
	temp_address = ((address << 4) & 0xFFF0);	//shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header
	byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
	byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

	//Structure inbound function data to send out over SPI byte by byte with MSB first - 	//Perform bitshifts to structure the values: To understand these shifts, picture this group of 1's being modified - Below is a 32 bit int. We're grabbing 1 byte out at a time. byteFour is the left most byte// 1111 1111 1111 1111 1111 1111 1111 1111
	uint8_t byteFour = (data >> 24);
    uint8_t byteThree = (data & 0xFFFFFF) >> 16;
    uint8_t byteTwo = (data & 0xFFFF) >> 8;
    uint8_t byteOne = (data & 0xFF);

    #ifdef ESP32ARCH  //example SPI routine for the ESP32
    spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
    spiAttachSCK(spy, -1);
    spiAttachMOSI(spy, -1);
    spiAttachMISO(spy, -1);
    digitalWrite(_SS, LOW); //Bring SS LOW (Active)
    spiTransferByte(spy, commandHeader1); //Send MSB
    spiTransferByte(spy, commandHeader2);  //Send LSB
    spiTransferByte(spy, byteFour);  //dummy write MSB, read out MSB
	spiTransferByte(spy, byteThree);  //dummy write LSB, read out LSB
	spiTransferByte(spy, byteTwo);  //dummy write LSB, read out LSB
    spiTransferByte(spy, byteOne);  //dummy write LSB, read out LSB
    digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
    spiStopBus(spy);
    #endif

    #ifdef AVRESP8266 //Arduino SPI Routine
    // beginTransaction before writing SS low
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
    // Tell 9078 chip what address, and whether to read or write with commandHeader
    SPI.transfer(commandHeader1);
    SPI.transfer(commandHeader2);
    SPI.transfer(byteFour);  // Write our data, msb first
    SPI.transfer(byteThree);
    SPI.transfer(byteTwo);
    SPI.transfer(byteOne);
    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
    SPI.endTransaction();      // endTransaction after writing SS high
	#endif

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead32 function details: ");
     Serial.print("Command Header: " + commandHeader1 + commandHeader2);
     Serial.print(" Wrote bytes (4(MSB) to 1)[BINARY]: ");
     Serial.print(byteFour, BIN);
     Serial.print(" ");
     Serial.print(byteThree, BIN);
     Serial.print(" ");
     Serial.print(byteTwo, BIN);
     Serial.print(" ");
     Serial.print(byteOne, BIN);
     Serial.println(" ADE9078::spiRead32 function completed ");
    #endif

  }
uint16_t ADE9078::spiRead16CRC(uint16_t address, bool &ValidCRC) { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
//This function provides CRC checking for registers that allow this functionality in non-burst mode. The validity of the return will be passed by a reference argument, Call with address and a valid response check, call as: value = object.spiRead16CRC(Address, CRCcheck);
    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16-CRC function started ");
    #endif
   //Prepare the 12 bit command header from the inbound address provided to the function
   //Initialize holders
   uint16_t temp_address = 0;
   uint16_t readval_unsigned=0;
   uint16_t CRC_Value = 0;
   uint16_t returnedCRC = 0; //Initialize and default with 0
   static unsigned char CRCCheckInput[2]; //define the holder for the input to the CRC check function, unsigned char array used for holding input and arranging bit order
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

    byte one, two; //holders for the read values from the SPI Transfer
	byte crcOne, crcTwo; //holders for returned CRC values

	#ifdef ESP32ARCH  //example SPI routine for the ESP32
	  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
	  spiAttachSCK(spy, -1);
      spiAttachMOSI(spy, -1);
      spiAttachMISO(spy, -1);
      digitalWrite(_SS, LOW); //Bring SS LOW (Active)
      spiTransferByte(spy, commandHeader1); //Send MSB
      spiTransferByte(spy, commandHeader2);  //Send LSB
      one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
      two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
	  crcOne = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC MSB
	  crcTwo = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC LSB
      digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
      spiStopBus(spy);
	#endif

	#ifdef AVRESP8266 //Arduino SPI Routine
    // beginTransaction is first
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
    SPI.transfer(commandHeader1);  //Transfer first byte (MSB), command
    SPI.transfer(commandHeader2);  ;//Transfer second byte (LSB), command
    //Read in values sequentially and bitshift for a 32 bit entry
    one = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    two = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
	crcOne = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    crcTwo = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
    SPI.endTransaction();      // end SPI Transaction
	#endif

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16-CRC function details: ");
     Serial.print(" Command Header: ");
     Serial.print(commandHeader1, BIN);
     Serial.print(commandHeader2, BIN);
     Serial.print(" Address Byte 1(MSB)[HEX]: ");
     Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
     Serial.print(one, HEX); //print MSB
     Serial.print(" ");
     Serial.print(two, HEX);  //print LSB
     Serial.println(" ADE9078::spiRead16-CRC function completed ");
    #endif

	readval_unsigned = (one << 8);  //Process MSB  (Alternate bitshift algorithm)
    readval_unsigned = readval_unsigned + two;  //Process LSB
	CRC_Value = (crcOne << 8); //Push in first CRC value into the 16bit holder
	CRC_Value = CRC_Value + crcTwo;  //Process LSB for CRC
	//Load in forward into the CRC check - double check byte order!
	CRCCheckInput[0] = one; //load first value into the array
	CRCCheckInput[1] = two; //load second value into the array
	CRCCheckInput[2] = 0; //load terminal value into the array  (previously: CRCCheckInput[2] = NULL;)

	//Check the CRC value to see if the return and the CRC match on the received side, pad into a 32 bit return as part of a 32 bit character, MSB is first fed into the CRC algorithm, per page 64 of the datasheet, assume padding to 32 bits with 0's per algorithm approach
	returnedCRC = crc16(CRCCheckInput, (short)3); // enter CRC value into the check algorithm MSB first, the length is 2 bytes (16 bit), this is specified

	if (returnedCRC == CRC_Value) //check the returned CRC value to see if it matches the input CRC value
	{
	ValidCRC = 1; //value matches, return a 1 to indicate a match has taken place and the returned data is valid
	}
	else
	{
		ValidCRC = 0; //value does not match, return a 0 to indicate a match has not taken place and the returned data is invalid
	}

   #ifdef ADE9078_CRC_Output
   Serial.print(" Read 16-bit value fed into the CRC Check function[HEX]: ");
   Serial.print(readval_unsigned, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 1[HEX]: ");
   Serial.print(crcOne, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 2[HEX]: ");
   Serial.print(crcTwo, BIN);
   Serial.print(" ADE9087 Read CRC Value Combined[HEX]: ");
   Serial.print(CRC_Value, BIN);
   Serial.print(" Value returned from the 16 BIT CCITT CRC check function[HEX]: ");
   Serial.print(returnedCRC, BIN);
   Serial.print(" Determined to be a match?: ");
   Serial.println(ValidCRC, DEC);
   #endif

	return readval_unsigned;
}

uint32_t ADE9078::spiRead32CRC(uint16_t address, bool &ValidCRC) { //This is the algorithm that reads from a 32 bit register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.  Caution, some register elements contain information that is only 24 bit with padding on the MSB
  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::spiRead32 function started ");
  #endif

   //Prepare the 12 bit command header from the inbound address provided to the function
      //Initialize holders
   uint16_t temp_address = 0;
   uint16_t readval_unsigned=0;
   uint16_t CRC_Value = 0;
   uint16_t returnedCRC = 0; //Initialize and default with 0
   uint32_t returnedValue = 0;
   static unsigned char CRCCheckInput[4]; //define the holder for the input to the CRC check function, unsigned char array used for holding input and arranging bit order
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

  byte one, two, three, four; //holders for the read values from the SPI Transfer
  byte crcOne, crcTwo; //holders for returned CRC values

  #ifdef ESP32ARCH  //example SPI routine for the ESP32
  spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
  spiAttachSCK(spy, -1);
  spiAttachMOSI(spy, -1);
  spiAttachMISO(spy, -1);
  digitalWrite(_SS, LOW); //Bring SS LOW (Active)
  spiTransferByte(spy, commandHeader1); //Send MSB
  spiTransferByte(spy, commandHeader2);  //Send LSB
  one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
  two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  three = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  four = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
  crcOne = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC MSB
  crcTwo = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC LSB
  digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
  spiStopBus(spy);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
  SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.transfer(commandHeader1);  //MSB Byte 1
  SPI.transfer(commandHeader2);
  //Read in values sequentially and bitshift for a 32 bit entry
  one = SPI.transfer(dummyWrite); //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  three = SPI.transfer(dummyWrite);   // (Read in data on dummy write (null MOSI signal))
  four = SPI.transfer(dummyWrite); //LSB Byte 4  (Read in data on dummy write (null MOSI signal))
  crcOne = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  crcTwo = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  SPI.endTransaction();
  #endif

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" Returned bytes 1-4, 1 is MSB [HEX]: ");
   Serial.print(" ADE9078::spiRead32-CRC function details: ");
   Serial.print(" Command Header: ");
   Serial.print(commandHeader1, BIN);
   Serial.print(commandHeader2, BIN);
   Serial.print(" Returned bytes (1(MSB) to 4)[BINARY]: ");
   Serial.print(one, BIN);
   Serial.print(" ");
   Serial.print(two, BIN);
   Serial.print(" ");
   Serial.print(three, BIN);
   Serial.print(" ");
   Serial.print(four, BIN);
   Serial.println(" ADE9078::spiRead32-CRC function completed ");
  #endif

    //Post-read packing and bitshifting operations for a 32 bit return
  returnedValue = (((uint32_t) one << 24) + ((uint32_t) two << 16) + ((uint32_t) three << 8) + (uint32_t) four);

  	CRC_Value = (crcOne << 8); //Push in first CRC value into the 16bit holder
	CRC_Value = CRC_Value + crcTwo;  //Process LSB for CRC
	//Load in forward into the CRC check - double check byte order!
	CRCCheckInput[0] = one; //load first value into the array
	CRCCheckInput[1] = two; //load second value into the array
    CRCCheckInput[2] = three; //load third value into the array
	CRCCheckInput[3] = four; //load fourth value into the array
	CRCCheckInput[4] = 0; //load terminal value into the array (previously: CRCCheckInput[4] = NULL;)

	//Check the CRC value to see if the return and the CRC match on the received side, pad into a 32 bit return as part of a 32 bit character, MSB is first fed into the CRC algorithm, per page 64 of the datasheet, assume padding to 32 bits with 0's per algorithm approach
	returnedCRC = crc16(CRCCheckInput, (short)4); // enter CRC value into the check algorithm MSB first, the length is 2 bytes (16 bit), this is specified

	if (returnedCRC == CRC_Value) //check the returned CRC value to see if it matches the input CRC value
	{
	ValidCRC = 1; //value matches, return a 1 to indicate a match has taken place and the returned data is valid
	}
	else
	{
		ValidCRC = 0; //value does not match, return a 0 to indicate a match has not taken place and the returned data is invalid
	}
	//Check the CRC value to see if the return and the CRC match on the received side, pad into a 32 bit return as part of a 32 bit character, MSB is first fed into the CRC algorithm, per page 64 of the datasheet, assume padding to 32 bits with 0's per algorithm approach
	returnedCRC = crc16(CRCCheckInput, (short)4); // enter CRC value into the check algorithm MSB first, the length is 4 bytes (32 bit), this is specified
	if (returnedCRC == CRC_Value) //check the returned CRC value to see if it matches the input CRC value
	{
	ValidCRC = 1; //value matches, return a 1 to indicate a match has taken place and the returned data is valid
	}
	else
	{
		ValidCRC = 0; //value does not match, return a 0 to indicate a match has not taken place and the returned data is invalid
	}

   #ifdef ADE9078_CRC_Output
   Serial.print(" Read 32 value fed into the CRC Check function[HEX]: ");
   Serial.print(returnedValue, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 1[HEX]: ");
   Serial.print(crcOne, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 2[HEX]: ");
   Serial.print(crcTwo, BIN);
   Serial.print(" ADE9087 Read CRC Value Combined[HEX]: ");
   Serial.print(CRC_Value, BIN);
   Serial.print(" Value returned from the 16 BIT CCITT CRC check function[HEX]: ");
   Serial.print(returnedCRC, BIN);
   Serial.print(" Determined to be a match?: ");
   Serial.println(ValidCRC, DEC);
   #endif

  return (returnedValue);
}
