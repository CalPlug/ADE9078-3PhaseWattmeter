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
#include <EEPROM.h>


#ifdef ESP32ARCH
	#include "esp32-hal-spi.h"
	spi_t * spy; //for ESP32, create object for SPI
#endif

//****EEPROM Settings******
#define NUM_ELEMENTS 14 //Define total fields for EEPROM storage that are cleared and used
// temporary char buffers for individual EEPROM saved values, local copy for the RAM to use after EEPROM load complete
char data[250] = {}; //holder for the string pushed into the EEPROM; buffer for EEPROM string
char data2[250] = {}; //holder for the string pushed into the EEPROM; used for test read from the EEPROM

//Fields for calibration values from ADE9000 example, declare blank to begin with
char Valconfigured[5]; //Identification if previous values are OK (can be used to detect good values on boot-up, if not, load default values
char ValADDR_AIGAIN[20];
char ValADDR_BIGAIN[20];
char ValADDR_CIGAIN[20];
char ValADDR_NIGAIN[20];
char ValADDR_AVGAIN[20];
char ValADDR_BVGAIN[20];
char ValADDR_CVGAIN[20];
char ValADDR_APHCAL0[20];
char ValADDR_BPHCAL0[20];
char ValADDR_CPHCAL0[20];
char ValADDR_APGAIN[20];
char ValADDR_BPGAIN[20];
char ValADDR_CPGAIN[20];
//**********


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

double decimalize(uint32_t input, double factor, double offset, bool absolutevalue) //This function converts to floating point with an optional linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
	#ifdef ADE9078_VERBOSE_DEBUG
	Serial.print(" ADE9078::calibration (decimalize) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	#ifdef ADE9078_Calibration
	Serial.print(" ADE9078::calibration (decimalize) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	//Warning, you can get overflows due to the printout of returned values in Arduino, See: http://forum.arduino.cc/index.php/topic,46931.0.html
	if(absolutevalue == 0){
	return (((double)input*factor)+offset); //standard y=mx+b calibration function applied to return
	}
	else{
		return (abs(((double)input*factor)+offset)); //standard y=mx+b calibration function applied to return
	}
}

double decimalizeSigned(int32_t input, double factor, double offset, bool absolutevalue) //This function converts to floating point with an optional linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
	#ifdef ADE9078_VERBOSE_DEBUG
	Serial.print(" ADE9078::calibration (decimalize-signed) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
    #ifdef ADE9078_Calibration
	Serial.print(" ADE9078::calibration (decimalize-signed) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	//Warning, you can get overflows due to the printout of returned values in Arduino, See: http://forum.arduino.cc/index.php/topic,46931.0.html
	if(absolutevalue == 0){
	return (((double)input*factor)+offset); //standard y=mx+b calibration function applied to return
	}
	else{
		return (abs(((double)input*factor)+offset)); //standard y=mx+b calibration function applied to return
	}
}

//The following functions are used to assist with loading calibration and mode values onto the on-board EEPROM

void save_data(char* data)  // Saves data in the passed array to the EEPROM
{
  Serial.println("Call to write data to EEPROM");
  #ifdef ESP32ARCH
  EEPROM.begin(512);
  #endif
  for (int i = 0; i < strlen(data); ++i)
  {
    EEPROM.write(i, (int)data[i]);
    delay(1);
  }
  #ifdef ESP32ARCH
  EEPROM.commit();
  #endif
  Serial.println("Write data complete");
  delay(100);
}

void load_data(char* data) //passes all read fields back by reference
{
  Serial.println("Read data from EEPROM");
  #ifdef ESP32ARCH
  EEPROM.begin(512);
  #endif
  int count = 0;
  int address = 0;
  while (count < NUM_ELEMENTS)
  {
    char read_char = (char)EEPROM.read(address);
    delay(1);
    strncat(data, &read_char, 1);
    if (read_char == '#')
      ++count;
    ++address;
	delay(100);
  }
  Serial.println("Read data complete with the following values read back: ");
  Serial.println(data);
}


void wipe_data() 
{
  Serial.println("Wipe EEPROM Values called");
  char* sep = "#";
  #ifdef ESP32ARCH
  EEPROM.begin(512);
  #endif
  for (int i = 0; i < NUM_ELEMENTS; ++i)
  {
    EEPROM.write(i, (int)sep);
    delay(1);
    EEPROM.write(i, 50); //end character
    delay(1);
  }
  #ifdef ESP32ARCH
  EEPROM.commit();
  #endif
  Serial.println("Wipe data complete");
}

void EEPROMInit() { //function called once on a virgin micro-controller to set the EEPROM with used fields
  Serial.println(" Begin EEPROM Initialization Function...");
  //Default values
  strcpy(Valconfigured, "0"); //indication that the EEPROM is configured with values, use 0, the un-configured, default state
  //Set field values with default calibration values
  strcpy(ValADDR_AIGAIN, "1");  
  strcpy(ValADDR_BIGAIN, "1");  
  strcpy(ValADDR_CIGAIN, "1");  
  strcpy(ValADDR_NIGAIN, "1");  
  strcpy(ValADDR_AVGAIN, "1");  
  strcpy(ValADDR_BVGAIN, "1");  
  strcpy(ValADDR_CVGAIN, "1");  
  strcpy(ValADDR_APHCAL0, "1");  
  strcpy(ValADDR_BPHCAL0, "1");  
  strcpy(ValADDR_CPHCAL0, "1");  
  strcpy(ValADDR_APGAIN, "1");  
  strcpy(ValADDR_BPGAIN, "1");  
  strcpy(ValADDR_CPGAIN, "1");  
  wipe_data(); //wipe current EEPROM values, without this the configured value is almost certainly not pre-set properly.
  char* sep = "#";
  strcat(data, Valconfigured);
  strcat(data, sep);
  strcat(data, ValADDR_AIGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_BIGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_CIGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_NIGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_AVGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_BVGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_CVGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_APHCAL0);
  strcat(data, sep);
  strcat(data, ValADDR_BPHCAL0);
  strcat(data, sep);
  strcat(data, ValADDR_CPHCAL0);
  strcat(data, sep);
  strcat(data, ValADDR_APGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_BPGAIN);
  strcat(data, sep);
  strcat(data, ValADDR_CPGAIN);
  strcat(data, sep);
 
  Serial.println("This is the final string to load into EEPROM:");
  Serial.println(data);
  Serial.println("The length is: ");
  Serial.println((unsigned)strlen(data));
  Serial.println();
  save_data(data);
  Serial.println("Data saved to EEPROM");
  Serial.println("Test read of saved data from EEPROM:");
  load_data(data2);
  Serial.println(data2);

  Serial.println("EEPROM Initialization Complete");
}

void load_data_allfields() //load the data field by field into the RAM holders - MUST MATCH EEPROM formatting!
{
  Serial.println("Call to read data from EEPROM");
  #ifdef ESP32ARCH
  EEPROM.begin(512);
  #endif
  int count = 0;
  int address = 0;
  while (count < NUM_ELEMENTS)
  {
    char read_char = (char)EEPROM.read(address);
    delay(1);
    if (read_char == '#')
    {
      Serial.println(data);
      switch (count)
      { 
	    //load each value field by field and parse into the RAM holders for each value, the readout must match the loaded data fields!  

	    case 0: strcpy(Valconfigured, data); break;
        case 1: strcpy(ValADDR_AIGAIN, data); break;
        case 2: strcpy(ValADDR_BIGAIN, data); break;
        case 3: strcpy(ValADDR_CIGAIN, data); break;
        case 4: strcpy(ValADDR_NIGAIN, data); break;
        case 5: strcpy(ValADDR_AVGAIN, data); break;
        case 6: strcpy(ValADDR_BVGAIN, data); break;
        case 7: strcpy(ValADDR_CVGAIN, data); break;
        case 8: strcpy(ValADDR_APHCAL0, data); break;
        case 9: strcpy(ValADDR_BPHCAL0, data); break;
        case 10: strcpy(ValADDR_CPHCAL0, data); break;  
        case 11: strcpy(ValADDR_APGAIN, data); break;
        case 12: strcpy(ValADDR_BPGAIN, data); break;
        case 13: strcpy(ValADDR_CPGAIN, data); break; 		
      }
      count++;
      strcpy(data,"");
    } 
    else
    {
      strncat(data, &read_char, 1);  //total of 1 character appended
    }
    ++address;
  }
  //when using the recalled values (ouside of this function, the following approaches can be used to make the arrays that hold values as characters into numerical values for use:
  //atoi() can be used to generate integers needed from char arrays for loading, e.g. integerFromPC = atoi(strtokIndx);     // convert this part to an integer strtokIndx = strtok(NULL, ",");floatFromPC = atof(strtokIndx);     // convert this part to a float (see: http://forum.arduino.cc/index.php?topic=396450) 
    //floatFromPC = atof(strtokIndx);     // convert this part to a float
  Serial.println("<--Read data complete, this was read");
}
//************************

uint16_t crc16(unsigned char* data_p, uint16_t length){ //example CCITT 16 CRC function that returns unsigned 16 bit return given an array of input values and a length of the array.  Used  for checksum verification, borrowed Bob Felice, 2007 from example: http://www.drdobbs.com/implementing-the-ccitt-cyclical-redundan/199904926  ALSO  https://forum.arduino.cc/index.php?topic=123467.0
   unsigned char i;
   unsigned int data;
   unsigned int crc;
   #define POLY 0x8408 //deff. of the polynomial used for the calculation

   crc = 0xffff; //initial reset calculation value
	       if (length == 0)
              return (~crc);

       do {
              for (i = 0, data = (unsigned int)0xff & *data_p++; i < 8; i++, data >>= 1) //*data_p++ is often without ++ in other versions, see links above for details on this and implementation/usage
			  {
                    if ((crc & 0x0001) ^ (data & 0x0001))
                           crc = (crc >> 1) ^ POLY;
                    else
                           crc >>= 1;
              }
       } while (--length);

       crc = ~crc;

       data = crc;
       crc = (crc << 8) | (data >> 8 & 0xFF);

       return (crc);
}

//**************** End Helper Functions *****************


//****************User Program Available Functions*****************

uint8_t ADE9078::getVersion(){
	return spiRead16(VERSION_16);
}

double ADE9078::getPowerFactorA(){
	int16_t value=0;
	value=spiRead16(PFA_16);
	double decimal = decimalize(value, 1.0, 0.0,0); //convert to double with calibration factors specified
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
    lastReads.vrms.a = decimalize(spiRead32(AVRMS_32), AVrmsGain, AVrmsOffset, 0);
    lastReads.vrms.b = decimalize(spiRead32(BVRMS_32), BVrmsGain, BVrmsOffset, 0);
    lastReads.vrms.c = decimalize(spiRead32(CVRMS_32), CVrmsGain, CVrmsOffset, 0);
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
    lastReads.irms.a = decimalize(spiRead32(AIRMS_32), AIrmsGain, AIrmsOffset, 0);
    lastReads.irms.b = decimalize(spiRead32(BIRMS_32), BIrmsGain, BIrmsOffset, 0);
    lastReads.irms.c = decimalize(spiRead32(CIRMS_32), CIrmsGain, CIrmsOffset, 0);
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
    lastReads.instApparentPower.a = decimalizeSigned(spiRead32(AVA_32), AAppPowerGain, AAppPowerOffset, 0);
    lastReads.instApparentPower.b = decimalizeSigned(spiRead32(BVA_32), BAppPowerGain, BAppPowerOffset, 0);
    lastReads.instApparentPower.c = decimalizeSigned(spiRead32(CVA_32), CAppPowerGain, CAppPowerOffset, 0);
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
    lastReads.instActivePower.a = decimalizeSigned(spiRead32(AWATT_32), AInstPowerGain, AInstPowerOffset, 0);
    lastReads.instActivePower.b = decimalizeSigned(spiRead32(BWATT_32), BInstPowerGain, BInstPowerOffset, 0);
    lastReads.instActivePower.c = decimalizeSigned(spiRead32(CWATT_32), CInstPowerGain, CInstPowerOffset, 0);
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
    lastReads.instReactivePower.a = decimalizeSigned(spiRead32(AVAR_32), AInstReactivePowerGain, AInstReactivePowerOffset, 0);
    lastReads.instReactivePower.b = decimalizeSigned(spiRead32(BVAR_32), BInstReactivePowerGain, BInstReactivePowerOffset, 0);
    lastReads.instReactivePower.c = decimalizeSigned(spiRead32(CVAR_32), CInstReactivePowerGain, CInstReactivePowerOffset, 0);
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

    /* //For reference, the following registers are written to on bootup for the ADE9000
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
  if (!checkBit((int)read32BitAndScale(STATUS1_32), 16)) {
    Serial.println("WARNING, POWER UP MAY NOT BE FINISHED");
  }
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

byte ADE9078::functionBitVal(uint16_t addr, uint8_t byteVal)
{
//Returns as integer an address of a specified byte - basically a byte controlled shift register with "byteVal" controlling the byte that is read and returned
  uint16_t x = ((addr >> (8*byteVal)) & 0xff);

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::functionBitVal function (separates high and low command bytes of provided addresses) details: ");
   Serial.print(" Address input (dec): ");
   Serial.print(addr, DEC);
   Serial.print(" Byte requested (dec): ");
   Serial.print(byteVal, DEC);
   Serial.print(" Returned Value (dec): ");
   Serial.print(x, DEC);
   Serial.print(" Returned Value (HEX): ");
   Serial.print(x, HEX);
   Serial.println(" ADE9078::functionBitVal function completed ");
  #endif

  return x;
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
   uint16_t temp_address, readval_unsigned, CRC_Value;
   uint16_t returnedCRC = 0;
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
   uint16_t temp_address, CRC_Value;
   uint16_t returnedCRC = 0;
   uint32_t returnedValue;
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

