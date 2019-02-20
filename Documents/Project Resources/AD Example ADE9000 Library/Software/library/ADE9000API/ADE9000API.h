/*
  ADE9000API.h - Library for ADE9000/ADE9078 - Energy and PQ monitoring AFE
  Author:nchandra
  Date: 3-16-2017
*/
#ifndef ADE9000API_h
#define ADE9000API_h

/****************************************************************************************************************
 Includes
***************************************************************************************************************/

#include "Arduino.h"
#include  "ADE9000RegMap.h"

/****************************************************************************************************************
 Definitions
****************************************************************************************************************/
/*Configuration registers*/
#define ADE9000_PGA_GAIN 0x0000    	    /*PGA@0x0000. Gain of all channels=1*/
#define ADE9000_CONFIG0 0x00000000		/*Integrator disabled*/
#define ADE9000_CONFIG1	0x0002			/*CF3/ZX pin outputs Zero crossing */
#define ADE9000_CONFIG2	0x0C00			/*Default High pass corner frequency of 1.25Hz*/
#define ADE9000_CONFIG3	0x0000			/*Peak and overcurrent detection disabled*/
#define ADE9000_ACCMODE 0x0000			/*60Hz operation, 3P4W Wye configuration, signed accumulation*/
										/*Clear bit 8 i.e. ACCMODE=0x00xx for 50Hz operation*/
										/*ACCMODE=0x0x9x for 3Wire delta when phase B is used as reference*/	
#define ADE9000_TEMP_CFG 0x000C			/*Temperature sensor enabled*/
#define ADE9000_ZX_LP_SEL 0x001E		/*Line period and zero crossing obtained from combined signals VA,VB and VC*/	
#define ADE9000_MASK0 0x00000001		/*Enable EGYRDY interrupt*/				
#define ADE9000_MASK1 0x00000000		/*MASK1 interrupts disabled*/
#define ADE9000_EVENT_MASK 0x00000000	/*Events disabled */
#define ADE9000_VLEVEL	0x0022EA28		/*Assuming Vnom=1/2 of full scale. 
										/*Refer Technical reference manual for detailed calculations.*/
#define ADE9000_DICOEFF 0x00000000 		/* Set DICOEFF= 0xFFFFE000 when integrator is enabled*/

/*Constant Definitions***/
#define ADE90xx_FDSP 8000   			/*ADE9000 FDSP: 8000sps, ADE9078 FDSP: 4000sps*/
#define ADE9000_RUN_ON 0x0001			/*DSP ON*/
/*Energy Accumulation Settings*/
#define ADE9000_EP_CFG 0x0011			/*Enable energy accumulation, accumulate samples at 8ksps*/
										/*latch energy accumulation after EGYRDY*/
										/*If accumulation is changed to half line cycle mode, change EGY_TIME*/
#define ADE9000_EGY_TIME 0x1F3F 				/*Accumulate 8000 samples*/

/*Waveform buffer Settings*/
#define ADE9000_WFB_CFG 0x1000			/*Neutral current samples enabled, Resampled data enabled*/
										/*Burst all channels*/
#define WFB_ELEMENT_ARRAY_SIZE 512  	/*size of buffer to read. 512 Max.Each element IA,VA...IN has max 512 points 
										/*[Size of waveform buffer/number of sample sets = 2048/4 = 512]*/
										/*(Refer ADE9000 technical reference manual for more details)*/

/*Full scale Codes referred from Datasheet.Respective digital codes are produced when ADC inputs are at full scale. Donot Change. */
#define ADE9000_RMS_FULL_SCALE_CODES  52702092
#define ADE9000_WATT_FULL_SCALE_CODES 20694066
#define ADE9000_RESAMPLED_FULL_SCALE_CODES  18196
#define ADE9000_PCF_FULL_SCALE_CODES  74532013

/*Size of array reading calibration constants from EEPROM*/
#define CALIBRATION_CONSTANTS_ARRAY_SIZE 13
#define ADE9000_EEPROM_ADDRESS 0x54			//1010xxxy xxx---> 100(A2,A1,A0 defined by hardware). y (1: Read, 0:Write)
#define EEPROM_WRITTEN 0x01

/*Address of registers stored in EEPROM.Calibration data is 4 bytes*/
#define ADDR_CHECKSUM_EEPROM 0x0800		 // Simple checksum to verify data transmission errors. Add all the registers upto CPGAIN. The lower 32 bits should match data starting @ADDR_CHECKSUM_EEPROM
#define ADDR_EEPROM_WRITTEN_BYTE 0x0804  //1--> EEPROM Written, 0--> Not written. One byte only

#define ADDR_AIGAIN_EEPROM 0x0004
#define ADDR_BIGAIN_EEPROM 0x000C
#define ADDR_CIGAIN_EEPROM 0x0010
#define ADDR_NIGAIN_EEPROM 0x0014
#define ADDR_AVGAIN_EEPROM 0x0018
#define ADDR_BVGAIN_EEPROM 0x001C
#define ADDR_CVGAIN_EEPROM 0x0020
#define ADDR_APHCAL0_EEPROM 0x0024
#define ADDR_BPHCAL0_EEPROM 0x0028
#define ADDR_CPHCAL0_EEPROM 0x002C
#define ADDR_APGAIN_EEPROM 0x0030
#define ADDR_BPGAIN_EEPROM 0x0034
#define ADDR_CPGAIN_EEPROM 0x0038
/****************************************************************************************************************
 EEPROM Global Variables
****************************************************************************************************************/

extern uint32_t calibrationDatafromEEPROM[CALIBRATION_CONSTANTS_ARRAY_SIZE];
extern uint32_t ADE9000_CalibrationRegAddress[CALIBRATION_CONSTANTS_ARRAY_SIZE];
extern uint32_t ADE9000_Eeprom_CalibrationRegAddress[CALIBRATION_CONSTANTS_ARRAY_SIZE];

/****************************************************************************************************************
 Structures and Global Variables
****************************************************************************************************************/

 struct ResampledWfbData
 {
  int16_t VA_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t IA_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t VB_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t IB_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t VC_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t IC_Resampled[WFB_ELEMENT_ARRAY_SIZE];
  int16_t IN_Resampled[WFB_ELEMENT_ARRAY_SIZE];
 };

  struct ActivePowerRegs
 {
	int32_t ActivePowerReg_A;
	int32_t ActivePowerReg_B;
	int32_t ActivePowerReg_C;
 };
 
   struct ReactivePowerRegs
 {
	int32_t ReactivePowerReg_A;
	int32_t ReactivePowerReg_B;
	int32_t ReactivePowerReg_C;
 };
 
  struct ApparentPowerRegs
 {
	int32_t ApparentPowerReg_A;
	int32_t ApparentPowerReg_B;
	int32_t ApparentPowerReg_C;
 };

  struct VoltageRMSRegs
 {
	int32_t VoltageRMSReg_A;
	int32_t VoltageRMSReg_B;
	int32_t VoltageRMSReg_C;
 };

  struct CurrentRMSRegs
 {
	int32_t CurrentRMSReg_A;
	int32_t CurrentRMSReg_B;
	int32_t CurrentRMSReg_C;
	int32_t CurrentRMSReg_N;
 };

  struct FundActivePowerRegs
 {
	int32_t FundActivePowerReg_A;
	int32_t FundActivePowerReg_B;
	int32_t FundActivePowerReg_C;
 }; 
 
   struct FundReactivePowerRegs
 {
	int32_t FundReactivePowerReg_A;
	int32_t FundReactivePowerReg_B;
	int32_t FundReactivePowerReg_C;
 }; 
 
   struct FundApparentPowerRegs
 {
	int32_t FundApparentPowerReg_A;
	int32_t FundApparentPowerReg_B;
	int32_t FundApparentPowerReg_C;
 }; 
 
    struct FundVoltageRMSRegs
 {
	int32_t FundVoltageRMSReg_A;
	int32_t FundVoltageRMSReg_B;
	int32_t FundVoltageRMSReg_C;
 }; 
 
    struct FundCurrentRMSRegs
 {
	int32_t FundCurrentRMSReg_A;
	int32_t FundCurrentRMSReg_B;
	int32_t FundCurrentRMSReg_C;
	//Fundamental neutral RMS is not calculated 
 }; 
 
     struct HalfVoltageRMSRegs
 {
	int32_t HalfVoltageRMSReg_A;
	int32_t HalfVoltageRMSReg_B;
	int32_t HalfVoltageRMSReg_C;
 }; 
 
     struct HalfCurrentRMSRegs
 {
	int32_t HalfCurrentRMSReg_A;
	int32_t HalfCurrentRMSReg_B;
	int32_t HalfCurrentRMSReg_C;
	int32_t HalfCurrentRMSReg_N;	
 }; 
 
     struct Ten12VoltageRMSRegs
 {
	int32_t Ten12VoltageRMSReg_A;
	int32_t Ten12VoltageRMSReg_B;
	int32_t Ten12VoltageRMSReg_C;	
 }; 
 
     struct Ten12CurrentRMSRegs
 {
	int32_t Ten12CurrentRMSReg_A;
	int32_t Ten12CurrentRMSReg_B;
	int32_t Ten12CurrentRMSReg_C;
	int32_t Ten12CurrentRMSReg_N;	
 }; 
 
     struct VoltageTHDRegs
 {
	int32_t VoltageTHDReg_A;
	int32_t VoltageTHDReg_B;
	int32_t VoltageTHDReg_C;
	float VoltageTHDValue_A;
	float VoltageTHDValue_B;
	float VoltageTHDValue_C;	
 }; 
 
     struct CurrentTHDRegs
 {
	int32_t CurrentTHDReg_A;
	int32_t CurrentTHDReg_B;
	int32_t CurrentTHDReg_C;
	float CurrentTHDValue_A;
	float CurrentTHDValue_B;
	float CurrentTHDValue_C;	
 }; 
  
     struct PowerFactorRegs
 {
	int32_t PowerFactorReg_A;
	int32_t PowerFactorReg_B;
	int32_t PowerFactorReg_C;	
	float PowerFactorValue_A;
	float PowerFactorValue_B;
	float PowerFactorValue_C;
 };  
 
     struct PeriodRegs
 {
	int32_t PeriodReg_A;
	int32_t PeriodReg_B;
	int32_t PeriodReg_C;
	float FrequencyValue_A;
	float FrequencyValue_B;
	float FrequencyValue_C;	
 };   

      struct AngleRegs
 {
	int16_t AngleReg_VA_VB;
	int16_t AngleReg_VB_VC;
	int16_t AngleReg_VA_VC;
	int16_t AngleReg_VA_IA;
	int16_t AngleReg_VB_IB;
	int16_t AngleReg_VC_IC;
	int16_t AngleReg_IA_IB;
	int16_t AngleReg_IB_IC;
	int16_t AngleReg_IA_IC;
	float AngleValue_VA_VB;
	float AngleValue_VB_VC;
	float AngleValue_VA_VC;
	float AngleValue_VA_IA;
	float AngleValue_VB_IB;
	float AngleValue_VC_IC;
	float AngleValue_IA_IB;
	float AngleValue_IB_IC;
	float AngleValue_IA_IC;	
 };   
 
     struct TemperatureRegnValue
 {
	int16_t Temperature_Reg;
	float Temperature;	
 };   

 
class ADE9000Class
{
	public:
		ADE9000Class();
		void SetupADE9000(void); 
		
		/*SPI Functions*/
		void SPI_Init(uint32_t SPI_speed , uint8_t chipSelect_Pin);  		
		void SPI_Write_16(uint16_t Address , uint16_t Data );
		void SPI_Write_32(uint16_t Address , uint32_t Data );		
		uint16_t SPI_Read_16(uint16_t Address);
		uint32_t SPI_Read_32(uint16_t Address);
		void SPI_Burst_Read_Resampled_Wfb(uint16_t Address, uint16_t Read_Element_Length, ResampledWfbData *ResampledData);    
		
		/*ADE9000 Calculated Parameter Read Functions*/
		void ReadActivePowerRegs(ActivePowerRegs *Data);
		void ReadReactivePowerRegs(ReactivePowerRegs *Data);
		void ReadApparentPowerRegs(ApparentPowerRegs *Data);
		void ReadVoltageRMSRegs(VoltageRMSRegs *Data);
		void ReadCurrentRMSRegs(CurrentRMSRegs *Data);
		void ReadFundActivePowerRegs(FundActivePowerRegs *Data);
		void ReadFundReactivePowerRegs(FundReactivePowerRegs *Data);
		void ReadFundApparentPowerRegs(FundApparentPowerRegs *Data);
		void ReadFundVoltageRMSRegs(FundVoltageRMSRegs *Data);
		void ReadFundCurrentRMSRegs(FundCurrentRMSRegs *Data);
		void ReadHalfVoltageRMSRegs(HalfVoltageRMSRegs *Data);
		void ReadHalfCurrentRMSRegs(HalfCurrentRMSRegs *Data);
		void ReadTen12VoltageRMSRegs(Ten12VoltageRMSRegs *Data);
		void ReadTen12CurrentRMSRegs(Ten12CurrentRMSRegs *Data);
		void ReadVoltageTHDRegsnValues(VoltageTHDRegs *Data);
		void ReadCurrentTHDRegsnValues(CurrentTHDRegs *Data);
		void ReadPowerFactorRegsnValues(PowerFactorRegs *Data);
		void ReadPeriodRegsnValues(PeriodRegs *Data);
		void ReadAngleRegsnValues(AngleRegs *Data);		
		void ReadTempRegnValue(TemperatureRegnValue *Data);
		
		/*EEPROM Functions*/
		void writeByteToEeprom(uint16_t dataAddress, uint8_t data);	
		uint8_t ReadByteFromEeprom(uint16_t dataAddress);
		void writeWordToEeprom(uint16_t address, uint32_t data);
		uint32_t readWordFromEeprom(uint16_t address);
		
	private:
		uint8_t  _chipSelect_Pin;
};


	

#endif

