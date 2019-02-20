/*
  ADE9000API.cpp - Library for ADE9000/ADE9078 - Energy and PQ monitoring AFE
  Date: 3-16-2017
*/
/****************************************************************************************************************
 Includes
***************************************************************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include "ADE9000API.h"
#include <Wire.h>

/*EEPROM data structure*/
uint32_t ADE9000_CalibrationRegAddress[CALIBRATION_CONSTANTS_ARRAY_SIZE]={ADDR_AIGAIN, ADDR_BIGAIN, ADDR_CIGAIN, ADDR_NIGAIN,ADDR_AVGAIN, ADDR_BVGAIN, ADDR_CVGAIN,ADDR_APHCAL0, ADDR_BPHCAL0, ADDR_CPHCAL0, ADDR_APGAIN, ADDR_BPGAIN, ADDR_CPGAIN};
uint32_t ADE9000_Eeprom_CalibrationRegAddress[CALIBRATION_CONSTANTS_ARRAY_SIZE]={ADDR_AIGAIN_EEPROM, ADDR_BIGAIN_EEPROM, ADDR_CIGAIN_EEPROM, ADDR_NIGAIN_EEPROM,ADDR_AVGAIN_EEPROM, ADDR_BVGAIN_EEPROM, ADDR_CVGAIN_EEPROM,ADDR_APHCAL0_EEPROM, ADDR_BPHCAL0_EEPROM, ADDR_CPHCAL0_EEPROM, ADDR_APGAIN_EEPROM, ADDR_BPGAIN_EEPROM, ADDR_CPGAIN_EEPROM};

ADE9000Class::ADE9000Class()
{
	
}

/* 
Description: Initializes the ADE9000. The initial settings for registers are defined in ADE9000API.h header file
Input: Register settings in header files
Output: 
*/

void ADE9000Class::SetupADE9000(void)
{
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
}

/* 
Description: Initializes the arduino SPI port using SPI.h library
Input: SPI speed, chip select pin
Output:-
*/

void ADE9000Class::SPI_Init(uint32_t SPI_speed , uint8_t chipSelect_Pin)
{
	SPI.begin();		//Initiate SPI port
	SPI.beginTransaction(SPISettings(SPI_speed,MSBFIRST,SPI_MODE0));		//Setup SPI parameters
	pinMode(chipSelect_Pin, OUTPUT);		//Set Chip select pin as output	
	digitalWrite(chipSelect_Pin, HIGH);		//Set Chip select pin high 

	_chipSelect_Pin = chipSelect_Pin;
}

/* 
Description: Writes 16bit data to a 16 bit register. 
Input: Register address, data
Output:-
*/

void ADE9000Class:: SPI_Write_16(uint16_t Address , uint16_t Data )
{
	uint16_t temp_address;
	
	digitalWrite(_chipSelect_Pin, LOW);
	temp_address = ((Address << 4) & 0xFFF0);	//shift address  to align with cmd packet
	SPI.transfer16(temp_address);
	SPI.transfer16(Data);
	
	digitalWrite(_chipSelect_Pin, HIGH); 	
}

/* 
Description: Writes 32bit data to a 32 bit register. 
Input: Register address, data
Output:-
*/

void ADE9000Class:: SPI_Write_32(uint16_t Address , uint32_t Data )
{
	uint16_t temp_address;
	uint16_t temp_highpacket;
	uint16_t temp_lowpacket;

	temp_highpacket= (Data & 0xFFFF0000)>>16;
	temp_lowpacket= (Data & 0x0000FFFF);
	
	digitalWrite(_chipSelect_Pin, LOW);
	
	temp_address = ((Address << 4) & 0xFFF0);	//shift address  to align with cmd packet
	SPI.transfer16(temp_address);
	SPI.transfer16(temp_highpacket);
	SPI.transfer16(temp_lowpacket);
	
	digitalWrite(_chipSelect_Pin, HIGH); 	
	
}

/* 
Description: Reads 16bit data from register. 
Input: Register address
Output: 16 bit data
*/

uint16_t ADE9000Class:: SPI_Read_16(uint16_t Address)
{
	uint16_t temp_address;
	uint16_t returnData;
	
	digitalWrite(_chipSelect_Pin, LOW);
	
	temp_address = (((Address << 4) & 0xFFF0)+8);
	SPI.transfer16(temp_address);
	returnData = SPI.transfer16(0);
	
	digitalWrite(_chipSelect_Pin, HIGH);
	return returnData;
}

/* 
Description: Reads 32bit data from register. 
Input: Register address
Output: 32 bit data
*/

uint32_t ADE9000Class:: SPI_Read_32(uint16_t Address)
{
	uint16_t temp_address;
	uint16_t temp_highpacket;
	uint16_t temp_lowpacket;
	uint32_t returnData;
	
	digitalWrite(_chipSelect_Pin, LOW);
	
	temp_address = (((Address << 4) & 0xFFF0)+8);
	SPI.transfer16(temp_address);
	temp_highpacket = SPI.transfer16(0);
	temp_lowpacket = SPI.transfer16(0);	
	
	digitalWrite(_chipSelect_Pin, HIGH);
	
	returnData = temp_highpacket << 16;
	returnData = returnData + temp_lowpacket;
	
	return returnData;

}
/* 
Description: Burst reads the content of waveform buffer. This function only works with resampled data. Configure waveform buffer to have Resampled data, and burst enabled (BURST_CHAN=0000 in WFB_CFG Register).
Input: The starting address. Use the starting address of a data set. e.g 0x800, 0x804 etc to avoid data going into incorrect arrays. 
       Read_Element_Length is the number of data sets to read. If the starting address is 0x800, the maximum sets to read are 512.
Output: Resampled data returned in structure
*/

void ADE9000Class:: SPI_Burst_Read_Resampled_Wfb(uint16_t Address, uint16_t Read_Element_Length, ResampledWfbData *ResampledData)
{
	uint16_t temp;
	uint16_t i;
 

	digitalWrite(_chipSelect_Pin, LOW);
  
	SPI.transfer16(((Address << 4) & 0xFFF0)+8);  //Send the starting address
 
  //burst read the data upto Read_Length 
	for(i=0;i<Read_Element_Length;i++) 
		{
		  ResampledData->IA_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->VA_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->IB_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->VB_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->IC_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->VC_Resampled[i] =  SPI.transfer16(0);
		  ResampledData->IN_Resampled[i] =  SPI.transfer16(0);
		}
	digitalWrite(_chipSelect_Pin, HIGH);
}

/* 
Description: Reads the Active power registers AWATT,BWATT and CWATT
Input: Structure name
Output: Active power codes stored in respective structure
*/

void ADE9000Class:: ReadActivePowerRegs(ActivePowerRegs *Data)
{
	Data->ActivePowerReg_A = int32_t (SPI_Read_32(ADDR_AWATT));
	Data->ActivePowerReg_B = int32_t (SPI_Read_32(ADDR_BWATT));
	Data->ActivePowerReg_C = int32_t (SPI_Read_32(ADDR_CWATT));
}

void ADE9000Class:: ReadReactivePowerRegs(ReactivePowerRegs *Data)
{
	Data->ReactivePowerReg_A = int32_t (SPI_Read_32(ADDR_AVAR));
	Data->ReactivePowerReg_B = int32_t (SPI_Read_32(ADDR_BVAR));
	Data->ReactivePowerReg_C = int32_t (SPI_Read_32(ADDR_CVAR));	
}

void ADE9000Class:: ReadApparentPowerRegs(ApparentPowerRegs *Data)
{
	Data->ApparentPowerReg_A = int32_t (SPI_Read_32(ADDR_AVA));
	Data->ApparentPowerReg_B = int32_t (SPI_Read_32(ADDR_BVA));
	Data->ApparentPowerReg_C = int32_t (SPI_Read_32(ADDR_CVA));	
}

void ADE9000Class:: ReadVoltageRMSRegs(VoltageRMSRegs *Data)
{
	Data->VoltageRMSReg_A = int32_t (SPI_Read_32(ADDR_AVRMS));
	Data->VoltageRMSReg_B = int32_t (SPI_Read_32(ADDR_BVRMS));
	Data->VoltageRMSReg_C = int32_t (SPI_Read_32(ADDR_CVRMS));	
}

void ADE9000Class:: ReadCurrentRMSRegs(CurrentRMSRegs *Data)
{
	Data->CurrentRMSReg_A = int32_t (SPI_Read_32(ADDR_AIRMS));
	Data->CurrentRMSReg_B = int32_t (SPI_Read_32(ADDR_BIRMS));
	Data->CurrentRMSReg_C = int32_t (SPI_Read_32(ADDR_CIRMS));
	Data->CurrentRMSReg_N = int32_t (SPI_Read_32(ADDR_NIRMS));
	
}

void ADE9000Class:: ReadFundActivePowerRegs(FundActivePowerRegs *Data)
{
	Data->FundActivePowerReg_A = int32_t (SPI_Read_32(ADDR_AFWATT));
	Data->FundActivePowerReg_B = int32_t (SPI_Read_32(ADDR_BFWATT));
	Data->FundActivePowerReg_C = int32_t (SPI_Read_32(ADDR_CFWATT));	
}

void ADE9000Class:: ReadFundReactivePowerRegs(FundReactivePowerRegs *Data)
{
	Data->FundReactivePowerReg_A = int32_t (SPI_Read_32(ADDR_AFVAR));
	Data->FundReactivePowerReg_B = int32_t (SPI_Read_32(ADDR_BFVAR));
	Data->FundReactivePowerReg_C = int32_t (SPI_Read_32(ADDR_CFVAR));	
}

void ADE9000Class:: ReadFundApparentPowerRegs(FundApparentPowerRegs *Data)
{
	Data->FundApparentPowerReg_A = int32_t (SPI_Read_32(ADDR_AFVA));
	Data->FundApparentPowerReg_B = int32_t (SPI_Read_32(ADDR_BFVA));
	Data->FundApparentPowerReg_C = int32_t (SPI_Read_32(ADDR_CFVA));	
}

void ADE9000Class:: ReadFundVoltageRMSRegs(FundVoltageRMSRegs *Data)
{
	Data->FundVoltageRMSReg_A = int32_t (SPI_Read_32(ADDR_AVFRMS));
	Data->FundVoltageRMSReg_B = int32_t (SPI_Read_32(ADDR_BVFRMS));
	Data->FundVoltageRMSReg_C = int32_t (SPI_Read_32(ADDR_CVFRMS));	
}

void ADE9000Class:: ReadFundCurrentRMSRegs(FundCurrentRMSRegs *Data)
{
	Data->FundCurrentRMSReg_A = int32_t (SPI_Read_32(ADDR_AIFRMS));
	Data->FundCurrentRMSReg_B = int32_t (SPI_Read_32(ADDR_BIFRMS));
	Data->FundCurrentRMSReg_C = int32_t (SPI_Read_32(ADDR_CIFRMS));	
}

void ADE9000Class:: ReadHalfVoltageRMSRegs(HalfVoltageRMSRegs *Data)
{
	Data->HalfVoltageRMSReg_A = int32_t (SPI_Read_32(ADDR_AVRMSONE));
	Data->HalfVoltageRMSReg_B = int32_t (SPI_Read_32(ADDR_BVRMSONE));
	Data->HalfVoltageRMSReg_C = int32_t (SPI_Read_32(ADDR_CVRMSONE));	
}

void ADE9000Class:: ReadHalfCurrentRMSRegs(HalfCurrentRMSRegs *Data)
{
	Data->HalfCurrentRMSReg_A = int32_t (SPI_Read_32(ADDR_AIRMSONE));
	Data->HalfCurrentRMSReg_B = int32_t (SPI_Read_32(ADDR_BIRMSONE));
	Data->HalfCurrentRMSReg_C = int32_t (SPI_Read_32(ADDR_CIRMSONE));
	Data->HalfCurrentRMSReg_N = int32_t (SPI_Read_32(ADDR_NIRMSONE));
}

void ADE9000Class:: ReadTen12VoltageRMSRegs(Ten12VoltageRMSRegs *Data)
{
	Data->Ten12VoltageRMSReg_A = int32_t (SPI_Read_32(ADDR_AVRMS1012));
	Data->Ten12VoltageRMSReg_B = int32_t (SPI_Read_32(ADDR_BVRMS1012));
	Data->Ten12VoltageRMSReg_C = int32_t (SPI_Read_32(ADDR_CVRMS1012));	
}

void ADE9000Class:: ReadTen12CurrentRMSRegs(Ten12CurrentRMSRegs *Data)
{
	Data->Ten12CurrentRMSReg_A = int32_t (SPI_Read_32(ADDR_AIRMS1012));
	Data->Ten12CurrentRMSReg_B = int32_t (SPI_Read_32(ADDR_BIRMS1012));
	Data->Ten12CurrentRMSReg_C = int32_t (SPI_Read_32(ADDR_CIRMS1012));
	Data->Ten12CurrentRMSReg_N = int32_t (SPI_Read_32(ADDR_NIRMS1012));	
	
}

void ADE9000Class:: ReadVoltageTHDRegsnValues(VoltageTHDRegs *Data)
{
	uint32_t tempReg;
	float tempValue;
	
	tempReg=int32_t (SPI_Read_32(ADDR_AVTHD)); //Read THD register
	Data->VoltageTHDReg_A = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %
	Data->VoltageTHDValue_A=tempValue;	
	tempReg=int32_t (SPI_Read_32(ADDR_BVTHD)); //Read THD register
	Data->VoltageTHDReg_B = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %
	Data->VoltageTHDValue_B=tempValue;		
	tempReg=int32_t (SPI_Read_32(ADDR_CVTHD)); //Read THD register
	Data->VoltageTHDReg_C = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %
	Data->VoltageTHDValue_C=tempValue;			
}

void ADE9000Class:: ReadCurrentTHDRegsnValues(CurrentTHDRegs *Data)
{
	uint32_t tempReg;
	float tempValue;	
	
	tempReg=int32_t (SPI_Read_32(ADDR_AITHD)); //Read THD register
	Data->CurrentTHDReg_A = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %	
	Data->CurrentTHDValue_A=tempValue;		
	tempReg=int32_t (SPI_Read_32(ADDR_BITHD)); //Read THD register
	Data->CurrentTHDReg_B = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %	
	Data->CurrentTHDValue_B=tempValue;
	tempReg=int32_t (SPI_Read_32(ADDR_CITHD)); //Read THD register
	Data->CurrentTHDReg_C = tempReg;
	tempValue=(float)tempReg*100/(float)134217728; //Calculate THD in %		
	Data->CurrentTHDValue_C=tempValue;
}

void ADE9000Class:: ReadPowerFactorRegsnValues(PowerFactorRegs *Data)
{
	uint32_t tempReg;
	float tempValue;	
	
	tempReg=int32_t (SPI_Read_32(ADDR_APF)); //Read PF register
	Data->PowerFactorReg_A = tempReg;
	tempValue=(float)tempReg/(float)134217728; //Calculate PF	
	Data->PowerFactorValue_A=tempValue;			
	tempReg=int32_t (SPI_Read_32(ADDR_BPF)); //Read PF register
	Data->PowerFactorReg_B = tempReg;
	tempValue=(float)tempReg/(float)134217728; //Calculate PF	
	Data->PowerFactorValue_B=tempValue;	
	tempReg=int32_t (SPI_Read_32(ADDR_CPF)); //Read PF register
	Data->PowerFactorReg_C = tempReg;
	tempValue=(float)tempReg/(float)134217728; //Calculate PF	
	Data->PowerFactorValue_C=tempValue;
}

void ADE9000Class:: ReadPeriodRegsnValues(PeriodRegs *Data)
{
	uint32_t tempReg;
	float tempValue;	
	tempReg=int32_t (SPI_Read_32(ADDR_APERIOD)); //Read PERIOD register
	Data->PeriodReg_A = tempReg;
	tempValue=(float)(8000*65536)/(float)(tempReg+1); //Calculate Frequency	
	Data->FrequencyValue_A = tempValue;
	tempReg=int32_t (SPI_Read_32(ADDR_BPERIOD)); //Read PERIOD register
	Data->PeriodReg_B = tempReg;
	tempValue=(float)(8000*65536)/(float)(tempReg+1); //Calculate Frequency	
	Data->FrequencyValue_B = tempValue;
	tempReg=int32_t (SPI_Read_32(ADDR_CPERIOD)); //Read PERIOD register
	Data->PeriodReg_C = tempReg;
	tempValue=(float)(8000*65536)/(float)(tempReg+1); //Calculate Frequency	
	Data->FrequencyValue_C = tempValue;
}

void ADE9000Class:: ReadAngleRegsnValues(AngleRegs *Data)
{

	uint32_t tempReg;	
	uint16_t temp;
	float mulConstant;
	float tempValue;
	
	temp=SPI_Read_16(ADDR_ACCMODE); //Read frequency setting register
	if((temp&0x0100)>=0)
		{
			mulConstant=0.02109375;  //multiplier constant for 60Hz system
		}
	else
		{
			mulConstant=0.017578125; //multiplier constant for 50Hz system		
		}
	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VA_VB)); //Read ANGLE register
	Data->AngleReg_VA_VB=tempReg;
	tempValue=tempReg*mulConstant;	//Calculate Angle in degrees					
	Data->AngleValue_VA_VB=tempValue;
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VB_VC));
	Data->AngleReg_VB_VC=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_VB_VC=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VA_VC));
	Data->AngleReg_VA_VC=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_VA_VC=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VA_IA));
	Data->AngleReg_VA_IA=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_VA_IA=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VB_IB));
	Data->AngleReg_VB_IB=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_VB_IB=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_VC_IC));
	Data->AngleReg_VC_IC=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_VC_IC=tempValue;		
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_IA_IB));
	Data->AngleReg_IA_IB=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_IA_IB=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_IB_IC));
	Data->AngleReg_IB_IC=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_IB_IC=tempValue;	
	tempReg=int16_t (SPI_Read_32(ADDR_ANGL_IA_IC));
	Data->AngleReg_IA_IC=tempReg;
	tempValue=tempReg*mulConstant;
	Data->AngleValue_IA_IC=tempValue;						
}

/* 
Description: Starts a new acquisition cycle. Waits for constant time and returns register value and temperature in Degree Celsius
Input:	Structure name
Output: Register reading and temperature value in Degree Celsius
*/

void ADE9000Class:: ReadTempRegnValue(TemperatureRegnValue *Data)
{
	uint32_t trim;
	uint16_t gain;
	uint16_t offset;
	uint16_t tempReg; 
	float tempValue;
	
	SPI_Write_16(ADDR_TEMP_CFG,ADE9000_TEMP_CFG);//Start temperature acquisition cycle with settings in defined in ADE9000_TEMP_CFG
	delay(2); //delay of 2ms. Increase delay if TEMP_TIME is changed

	trim = SPI_Read_32(ADDR_TEMP_TRIM);
	gain= (trim & 0xFFFF);  //Extract 16 LSB
	offset= ((trim>>16)&0xFFFF); //Extract 16 MSB
	tempReg= SPI_Read_16(ADDR_TEMP_RSLT);	//Read Temperature result register
	tempValue= (float)(offset>>5)-((float)tempReg*(float)gain/(float)65536); 
	
	Data->Temperature_Reg=tempReg;
	Data->Temperature=tempValue;
}

/* 
Description: Writes one byte of data to EEPROM
Input: Data and EEPROM address
Output:-
*/

void ADE9000Class:: writeByteToEeprom(uint16_t dataAddress, uint8_t data)
{
	uint8_t temp;
	temp= (dataAddress>>8);
	Wire.beginTransmission(ADE9000_EEPROM_ADDRESS); // device address is specified in datasheet
	Wire.write(byte(temp));            // MSB Address
	temp= (dataAddress & (0xFF));
	Wire.write(byte(temp));           //LSB Address
	Wire.write(byte(data));             // 
	Wire.endTransmission();     // stop transmitting	
}

/* 
Description: REads one byte of data from EEPROM
Input: EEPROM address
Output:- 8 bit data
*/	

uint8_t ADE9000Class:: ReadByteFromEeprom(uint16_t dataAddress)
{
    uint8_t returndata;
    uint8_t temp;
    temp= (dataAddress>>8);
    Wire.beginTransmission(byte(ADE9000_EEPROM_ADDRESS)); // device address is specified in datasheet
    Wire.write(byte(temp)); // MSB
    temp= (dataAddress & (0xFF));
    Wire.write(byte(temp)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(byte(ADE9000_EEPROM_ADDRESS),1);
    if (Wire.available())  
        {
          returndata = Wire.read();
        }
    
	return returndata;	
}

/* 
Description: Writes 4 bytes into EEPROM in continuous locations
Input: Data and EEPROM address
Output:-
*/

void ADE9000Class:: writeWordToEeprom(uint16_t address, uint32_t data)
{
	uint8_t temp;
	uint32_t returnedValue;
	temp = (data &(0xFF));  //LSB
	writeByteToEeprom(address,temp);
	delay(10);
	temp = ((data>>8) &(0xFF)); 
	writeByteToEeprom(address+1,temp);
	temp = ((data>>16) &(0xFF));
	delay(10);
	writeByteToEeprom(address+2,temp);
	temp = ((data>>24) &(0xFF)); //MSB
	delay(10);
	writeByteToEeprom(address+3,temp);
	delay(10);
	returnedValue = readWordFromEeprom(address);
	if(returnedValue!=data)
    {
      Serial.println("Write Not Successful"); //Check if data write is successful
	  Serial.println("Address: ");
	  Serial.print(address);
	  Serial.println("Data: ");
	  Serial.print(data,HEX);
    }	
}

/* 
Description: Reads 4 bytes stored in EEPROM
Input: Starting EEPROM address
Output:- 4 byte wide data
*/

uint32_t ADE9000Class:: readWordFromEeprom(uint16_t address)
{
	uint32_t returndata;
	returndata=0;
	uint8_t temp;
	temp = ReadByteFromEeprom(address);
	returndata = temp;    //LSB
	delay(10);
	temp = ReadByteFromEeprom(address+1);
	returndata |= (temp<<8);
	delay(10);
	temp = ReadByteFromEeprom(address+2);
	returndata |= (temp<<16);
	delay(10);
	temp = ReadByteFromEeprom(address+3);
	returndata |= (temp<<24);  //MSB  
	return returndata;	
}



