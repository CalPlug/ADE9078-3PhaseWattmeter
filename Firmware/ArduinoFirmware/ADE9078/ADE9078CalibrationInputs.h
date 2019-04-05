/*Calibration Procedure*/
/*Setup ADE9000. Set the desired configuration registers in ADE9000API.h file.*/
/*Fill the user inputs, transfer function and conversion constants*/
/*Follow directions shown on serial monitor */

/*User Inputs*/
#define NOMINAL_INPUT_VOLTAGE 110       //Nominal Calibrating RMS Voltage on all phases (Vrms)
#define NOMINAL_INPUT_CURRENT 5         //Nominal Calibrating RMS Current on all phases (Irms)
#define INPUT_FREQUENCY 60              //Nominal Calibrating frequency. Used to calculate Omega for phase calibration.Ensure ACCMODE register is set to correct frequency
#define CALIBRATION_ANGLE_DEGREES 60	//Calibration Angle in Degrees.Used for phase calibration

/*Transfer function*/
/****************************************************************************************************************
									Current Transfer Function
*****************************************************************************************************************
It is the voltage at the ADC input pins per input current(A) (Volts/Amp)
E.g: For a current output current transformer with Turns Ratio of 2500:1. Burden resistor on board = 5.1*2=10.2 Ohm.
Current transfer function= 1/2500*Total Burden = 1/2500*10.2= 0.00408
****************************************************************************************************************/
/****************************************************************************************************************
									Voltage Transfer Function
*****************************************************************************************************************
It is the voltage at the ADC input pins per input Voltage(V)(Volts/Volts)
E.g. The defaul atteunation factor on board is 801. 
Voltage transfer function = 1/801= 0.001248 ~=0.00125
****************************************************************************************************************/                      						 
#define CURRENT_TRANSFER_FUNCTION 0.00408   //The RMS voltage at the ADC input pins per input RMS current  (V/A).(2500:1-->0.00408 with default burden resistors)
#define VOLTAGE_TRANSFER_FUNCTION  0.00125 //The RMS voltage at the ADC input pins per input RMS voltage (V/V) 
/****************************************************************************************************************
									Constants: Do not change 
*****************************************************************************************************************/
#define F_DSP 8000                         //Signal update Rate
#define CALIBRATION_EGY_CFG 0xF011         //Latch after EGYRDY. Sample based accumulation. Read with reset disabled. Accumulation enabled
#define EGYACCTIME 0x1F3F                  //Accumulate for a total of 8000 (EGY_TIME+1) samples.
#define CALIBRATION_ACC_TIME 1             //if EGYACCTIME= 0x1F3F, Accumulation time is 1sec. Change this if EGYACCTIME is changed.

#define CAL_ANGLE_RADIANS(x) (x*3.14159/180)


/****************************************************************************************************************
									Conversion Constants
*****************************************************************************************************************
If calibration is done with the the calibration sketch, the following conversion constants apply:
If CURRENT_TRANSFER_FUNCTION or VOLTAGE_TRANSFER_FUNCTION are changed, update the conversion constants

CAL_IRMS_CC in uA/code 				= 10^6/(CURRENT_TRANSFER_FUNCTION*ADE9000_RMS_FULL_SCALE_CODES*SQRT(2)) 
CAL_VRMS_CC in uV/code 				= 10^6/(VOLTAGE_TRANSFER_FUNCTION*ADE9000_RMS_FULL_SCALE_CODES*SQRT(2))
CAL_POWER_CC in mW/code 			= 10^3/(CURRENT_TRANSFER_FUNCTION*VOLTAGE_TRANSFER_FUNCTION*ADE9000_WATT_FULL_SCALE_CODES*2)
CAL_ENERGY_CC in uWhr/xTHR_HI code 	= 10^6/(CURRENT_TRANSFER_FUNCTION*VOLTAGE_TRANSFER_FUNCTION*ADE9000_WATT_FULL_SCALE_CODES*2*8000*3600*2^-13)

If conversion constants are set correctly, the register codes are converted to physical parameters as:
e.g Channel A Vrms = (AVRMS(register)*CAL_VRMS_CC/10^6)
	Channel A Active Power = (AWATT(register)*CAL_POWER_CC/10^3)	
*****************************************************************************************************************/
#define CAL_IRMS_CC		3.28849					// (uA/code)
#define CAL_VRMS_CC		10.73364				// (uV/code)	
#define CAL_POWER_CC 	4.73755					// (mW/code) Applicable for Active, reactive and apparent power
#define CAL_ENERGY_CC	1.34757					// (uWhr/xTHR_HI code)Applicable for Active, reactive and apparent energy

/*Full scale Codes referred from Datasheet.Respective digital codes are produced when ADC inputs are at full scale. Donot Change. */
#define ADE9078_RMS_FULL_SCALE_CODES  52702092
#define ADE9078_WATT_FULL_SCALE_CODES 20694066
#define ADE9078_RESAMPLED_FULL_SCALE_CODES  18196
#define ADE9078_PCF_FULL_SCALE_CODES  74532013

/*Constant Definitions***/
#define ADE90xx_FDSP 4000   			//*ADE9000 FDSP: 8000sps, ADE9078 FDSP: 4000sps*/

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

