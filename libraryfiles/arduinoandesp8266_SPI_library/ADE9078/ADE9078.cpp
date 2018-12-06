/*
 ADE7953.cpp - Example library for operating the ADE7953 Single-Phase AC Line measurement IC over SPI for Arduino Uno
  Created by Umar Kazmi, Crystal Lai, and Michael J. Klopfer, Ph.D.
  January 23, 2017 - 0.1 (pre-release)
  May 3, 2018 - v6.2 (current version) - by MJK
  Verified for compatibility with Arduino Uno and Espressif ESP8266, please see README about ESP32 compatibility.
  University of California, Irvine - California Plug Load Research Center (CalPlug)
  Copyright: The Regents of the University of California
  Released into the public domain with Share-alike licensing.
  Be decent: if our work helped you, then please reference/acknowledge this project and its authors in your work!

  Note: Please refer to the Analog Devices ADE7953 datasheet - much of this library was based directly on the statements and methods provided in it!  Their authors get paid, trust them over us!
*/

#include "Arduino.h"
#include <SPI.h>
#include "ADE7953.h"
//Debug Control:
//#define ADE7953_VERBOSE_DEBUG //This line turns on verbose debug via serial monitor (Normally off or //'ed).  Use sparingly and in a test program to debug operation!  Turning this on can take a lot of memory and the delay from USB printing out every statement is taxing temporally!  This is non-specific and for all functions, beware, it's a lot of output!  Reported bytes are in HEX




//*******************************************************************************************

//****************ADE 9078 REGISTERS *****************************************************
#define 0X000 AIGAIN_32 // Phase A current gain adjust

// The following registers: // Phase A multipoint gain correction factor
#define 0x001 AIGAIN0_32 /* Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define 0x002 AIGAIN1_32 /* Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define 0x003 AIGAIN2_32 /* Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define 0x004 AIGAIN3_32 /* Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define 0x005 AIGAIN4_32 /* Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */

#define 0x006 APHCAL0_32 /* Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x007 APHCAL1_32 /* Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x008 APHCAL2_32 /* Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x009 APHCAL3_32 /* Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x00A APHCAL4_32 /* Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

#define 0x00B AVGAIN_32 // Phase A voltage gain adjust
#define 0X00C AIRMSOS_32 // Phase A voltage rms offset for filter based AIRMS calculation
#define 0X00D AVRMSOS_32 // Phase A current RMS offset for filter based AIRMS calucation
#define 0X00E APGAIN_32 // Phase A power gain adjust for AWATT, AVA, avar, and AFVAR calculation
#define 0X00F AWATTOS_32 // Phase A total active power offset correction for AWATT calculation.
#define 0X010 AVAROS_32 // Phase A total active power offset correction for AVAR calculation.
#define 0x012 AFVAROS_32 // Phase A fundamental reactive power offset correction for AFVAR calculation

#define 0x020 BIGAIN_32 // Phrase B current gain adjust
#define 0x021 BIGAIN0_32 /* Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x022 BIGAIN1_32 /* Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x023 BIGAIN2_32 /* Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x024 BIGAIN3_32 /* Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x025 BIGAIN4_32 /* Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

// Phase B multipoint phase correction factor
#define 0x026 BPHCAL0_32 /* Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x027 BPHCAL1_32 /* Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x028 BPHCAL2_32 /* Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x029 BPHCAL3_32 /* Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define 0x02A BPHCAL4_32 /* Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

#define 0x02B BVGAIN_32 // Phase B voltage gai nadjust
#define 0x02C BIRMSOS_32 // Phase B current RMS offset for BIRMS calculation
#define 0x02D BVRMSOS_32 // Phase B voltage RMS offset for BVRMS calculation
#define 0X02E BPGAIN_32 // Phase B power gain adjust for BWATT, BVA, BVAR, and BFVAR calculations
#define 0X02F BWATTOS_32 // Phase B total active power offset correction for BWATT calculation
#define 0x030 BVAROS_32 // Phase B total active offset correction for BVAR calculation
#define 0x032 BFVAROS_32 // Phase B fundamental reactive power offset correction for BFVAR calculation

#define 0x040 CIGAIN_32 // Phase C current gain nadjust

// Phase C multipoint gain correction factor
#define 0x041 CIGAIN0_32 /* Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define 0x042 CIGAIN1_32 /* Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define 0x043 CIGAIN2_32 /* Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define 0x044 CIGAIN3_32 /* Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define 0x045 CIGAIN4_32 /* Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */

#define 0X046 CPHCAL0_32 /* Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define 0X047 CPHCAL1_32 /* Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define 0X048 CPHCAL2_32 /* Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define 0X049 CPHCAL3_32 /* Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define 0X04A CPHCAL4_32 /* Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */

#define 0x04B CVGAIN_32 // Phase C voltage gain adjust
#define 0x04C CIRMSOS_32 // Phase C current RMS offset for CIRMS calculation
#define 0x04D CVRMSOS_32 // Phase C voltage RMS offset for CVRMS calcuation
#define 0x04E CPGAIN_32 // Phase C power gain adjust for CWATT, CVA, CVAR, and CFVAR calculations
#define 0x04F CWATTOS_32 // Phase C total active power offset correction for CWATT calculations
#define 0x050 CVAROS_32 // Phase C total reactive power offset correction for CVAR calculation
#define 0x052 CFVAROS_32 // Phase C total reactive power offset correction for CVAR calculations

#define 0x060 CONFIG0_32
// Bits: [31:14] BitName: RESERVED Description: Reserved
// Bits: 13 BitName: DISRPLPF Description: Set this bit to disable the low-pass filter in the total reactive power datapath.
// Bits: 12 BitName: DISAPLPF Description: Set this bit to disable the low-pass filter in the total active power datapath.
// Bits: 11 BitName: ININTEN Description: Set this bit to enable the digital integrator in the Neutral Current channel.
// Bits: 10 BitName: VNOMC_EN Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase C total apparent power, CVA.
// Bits: 9 BitName: VNOMB_EN Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase B total apparent power, BVA.
// Bits: 8 BitName: VNOMA_EN Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase A total apparent power, AVA.
// Bits: 7 BitName: RESERVED Description: Reserved
// Bits: 6 BitName: ZX_SRC_SEL Description: This bit selects whether data going into the zero-crossing detection circuit comes before the highpass filter, integrator, and phase compensation or afterwards. Setting: 0 for After the high-pass filter, integrator, and phase compensation. Setting: 1 for Before the high-pass filter, integrator, and phase compensation.
// Bits: 5 BitName: INTEN Description: Set this bit to enable the integrators in the phase current channels. The neutral current channel integrator is managed byb the ININTEN bit in the CONFIG0 register.
// Bits: 4 BitName: MTEN Description: Set this bit to enable multipoint phase and gain compensation. If enabled, an additional gain factor, xIGAIN0 through xIGAIN4, is applied to the current channel based on the xIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.
// Bits: 3 BitName: HPFDIS Description: Set this bit to disable high-pass filters in all the voltage and current channels.
// Bits: 2 BitName: RESERVED Description: Reserved
// Bits: [1:0] BitName: ISUM_CFG Description: ISUM Calculation configuration. Setting: 00 for ISUM = AI_PCF + BI_PCF + CI_PCF (for approximated neutral current rms calculation) Setting: 01 for ISUM = AI_PCF + BI_PCF + CI_PCF+ NI_PCF(to determine mismatch between neutral and phase currents). Setting: 10 for ISUM = AI_PCF + BI_PCF + CI_PCF - NI_PCF(to determine mismatch between neutral and phase currents). Setting: 11 for ISUM = AI_PCF + BI_PCF + CI_PCF (for approximated neutral current rms calculation).

// Multipoint phase/gain threshold.
#define 0x061 MTTHR_L0_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x062 MTTHR_L1_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x063 MTTHR_L2_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x064 MTTHR_L3_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x065 MTTHR_L4_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/

#define 0x066 MTTHR_H0_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x067 MTTHR_H1_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x068 MTTHR_H2_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x069 MTTHR_H3_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define 0x06A MTTHR_H4_32 /* Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/

#define 0x06B NIRMSOS_32 // Neutral current RMS offset for NIRMS calculations
#define 0x06C ISUMRMSOS_32 // Offset correction for ISUMRMS calculation based on the sume of IA + IB + IC +- IN.
#define 0X06D NIGAIN_32 // Neutral current again adjust
#define 0x06E NPHCAL_32 // Neutral current-phase compensation
#define 0x071 VNOM_32 // Nominal phase voltage RMS used in the computation of apparent power, xVA, when VNOMx_EN bit is set in the CONFIG0 register
#define 0x072 DICOEFF_32 // Value used in the digital integrator algorithm
#define 0x073 ISUMLVL_32 // Threshold to compare ISUMRMS against

#define 0x20A AI_PCF_32 // Instantaneous Phase A current channel waveform processed by the DSP, at 4 kSPS.
#define 0x20B AV_PCF_32 // Instantaneous Phase A voltage channel waveform processed by the DSP, at 4 kSPS.
#define 0x20C AIRMS_32 // Phase A filter based current RMS value, updates at 4kSPS
#define 0x20D AVRMS_32 // Phase A filter based voltage RMS value, updates at 4kSPS

#define 0x210 AWATT_32 // Phase A low-pass filtere total active power, updated at 4 4kSPS
#define 0x211 AVAR_32 // Phase A low pass filtered total reactive power, updated at 4kSPS
#define 0x212 AVA_32 // Phase A total apparent power, updated at 4kSPS
#define 0x214 AFVAR_32 // Phase A fundamental reactive power, updated at 4kSPS
#define 0x216 APF_32 // Phase A power factor, updated at 1.024 second

#define 0x21D AMTREGION_32 // If multipoint gain and phase compensaion is enabled, with MTEN = 1 in the CONFIG0 register,these bits indicate which AIGAINXx and APHCALx is currently being used
/*
[31:4] : RESERVED
[3:0] : AREGION
If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which AIGAINx and APHCALx currently being used.
0000 AIGAIN0, APHCAL0.
0001 AIGAIN1, APHCAL1.
0010 AIGAIN2, APHCAL2.
0011 AIGAIN3, APHCAL3.
0100 AIGAIN4, APHCAL4.
1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.
*/


#define 0x22A BI_PCF_32 // Instantaneous Phase B current channel waveform processed by the DSP, 4kSPS
#define 0x22B BV_PCF_32 // Instantaneous Phase B votage channel waveform processed by the DSP, 4kSPS
#define 0x22C BIRMS_32 // Phase B filter based current RMS value, updates at 4kSPS
#define 0x22D BVRMS_32 // Phase B filter based voltage RMS value, updates at 4kSPS
#define 0x230 BWATT_32 // Phase B low-pass filtered total active power, updated at 4kSPS
#define 0x231 BVAR_32 // Phase B low pass filtered total reactive power, updated at 4kSPS.
#define 0x232 BVA_32 // Phase B total apparent power, updated at 4kSPS
#define 0x234 BFVAR_32 // Phase B fundamental reactive power, updated at 4kSPS
#define 0x236 BPF_32 // Phase B power factor, updated at 1.024 sec.

#define 0x23D BMTREGION_32 // If multipoint gain and phase.....
/*
[31:4] : RESERVED
[3:0] : BREGION
If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which BIGAINx and BPHCALx currently being used.
0000 BIGAIN0, BPHCAL0.
0001 BIGAIN1, BPHCAL1.
0010 BIGAIN2, BPHCAL2.
0011 BIGAIN3, BPHCAL3.
0100 BIGAIN4, BPHCAL4.
1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.
*/


#define 0x24A CI_PCF_32 // Instantaneous Phase C current channel waveform proccessed by the DSP, at 4kSPS
#define 0x24B CV_PCF_32 // Instantaneous Phase C voltage channel waveform proccessed by the DSP, at 4kSPS
#define 0X24C CIRMS_32 // Phase C filter based current RMS value, updates at 4kSPS
#define 0x24D CVRMS_32 // Phase C filter based voltage RMS value, updates at 4kSPS
#define 0x250 CWATT_32 // Phase C low-pass filtered total active power, updated at 4kSPS
#define 0x251 CVAR_32  // Phase C low pass filtered total reactive power, updated at 4kSPS.
#define 0x252 CVA_32 // Phase C total apparent power, updated at 4kSPS
#define 0x254 CFVAR_32 // Phase C fundamental reactive power, udpated at 4kSPS
#define 0x256 CPF_32 // Phase C power factor, updated at 1.024 seconds

#define 0X25D CMTREGION_32 // If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which CIGAINx and CPHCALx is currently being used.
/*
[31:4] : RESERVED
[3:0] : CREGION
If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which CIGAINx and CPHCALx currently being used.
0000 CIGAIN0, CPHCAL0.
0001 CIGAIN1, CPHCAL1.
0010 CIGAIN2, CPHCAL2.
0011 CIGAIN3, CPHCAL3.
0100 CIGAIN4, CPHCAL4.
1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.
*/

#define 0x265 NI_PCF_32 // Instantaneous neutral current channel waveform processed by the DSP, at 4kSPS.
#define 0x266 NIRMS_32 // Neutral current filter based RMS value
#define 0x269 ISUMRMS_32 // Filter based RMS based on the sum of IA + IB + IC += IN.
#define 0x26A VERSION2_32 // Indicates the version of the metrology algorithms after the user writes run = 1 to start the measuremnets.

#define 0x2E5 AWATT_ACC_32 // Phase A accumulated total active power, updated after PWR_TIME 4 ksps samples
#define 0x2E6 AWATTHR_LO_32 // Phase A accumulated total active energy, LSB's. Updated according to settings in EP_CFG and EGY_TIME Registers
#define 0x2E7 AWATTHR_HI_32 // Phase A accumulated total active energy, MSB's....
#define 0x2EF AVAR_ACC_32  // Phase A accumulated total reactive power, updated after PWR_TIME 4 kSPS samples.
#define 0X2F0 AVARHR_LO_32 // Phase A accumulated total reactive energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME Registers
#define 0x2F1 AVARHR_HI_32 // Phase A accumulated total reactive energy, MSB's...
#define 0x2F9 AVA_ACC_32 // Phase A accumulated total apparent power, updated after PWR_TIME 4 kSPS samples
#define 0x2FA AVAHR_LO_32 // Phase A accumulated total apparent energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x2FB AVAHR_HI_32 // Phase A accumulated total apparent energy, MSB's.

#define 0x30D AFVAR_ACC_32 // Phase A accumulated fundamental reactive power, updated after PWR_TIME 4kSPS samples
#define 0x30E AFVARHR_LO_32 // Phase A accumulated total apparent energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME Registers
#define 0x30F AFVARHR_HI_32 // Phase A accumulated total apparent energy, MSB's...
#define 0x321 BWATT_ACC_32 // Phase B accumulated total active power, updated after PWR_TIME 4 kSPS samples
#define 0x322 BWATTHR_LO_32 // Phase B accumulated total active energy, LSB's, updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x323 BWATTHR_HI_32 // Phase B accumulated total active energy, MSB's...
#define 0x32B BVAR_ACC_32  // Phase B accumulated total reactive power, updated after PWR_TIME 4 ksSPS samples.

#define 0x32C BVARHR_LO_32 //Phase B accumulate total ractive energy,LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x32D BVARHR_HI_32 // Phase B accumulate total ractive energy,MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x335 BVA_ACC_32 //Phase B accumulated total apparent power, updated after PWR_TIME 4kSPS samples.
#define 0x336 BVAHR_LO_32 //Phase B accumulatecd total apparent energy, LSbs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x337 BVAHR_HI_32 //Phase B accumulate total ractive energy,MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x349 BFVAR_ACC_32 //Phase B accumulated fundamental ractive power, updated after PWR_TIME 4 kSPS samples.
#define 0x34A BFVARHR_LO_32 //Phase B accumulated fundamental reactive energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x34B BFVARHR_HI_32 //Phase B accumulated fundamental reactive energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x35D CWATT_ACC_32 // Phase C accumulated total active power, updated after PWR_TIME 4 kSPS samples
#define 0x35E CWARRHR_LO_32 //Phase C accumulated total active energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x35F CWATTHR_HI_32 //Phase C accumulated total active energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x367 CVAR_ACC_32 //Phase C accumulated total reactive power, updated after PWR_TIME 4kSPS samples.
#define 0x368 CVARHR_LO_32 //Phase C accumulated total ractive energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x369 CVARHR_HI_32 //Phase C accumulated total ractive energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x371 CVA_ACC_32 //Phase C accumulated total apparent powerm updated after PWR_TIME 4 kSPS samples.
#define 0x372 CVAHR_LO_32 //Phase C  accumulated total apparent energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x373 CVAHR_HI_32 //Phase C accumulated total apparent energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x385 CFVAR_ACC_32 //Phase C accumulated fundamental reactive power, updated after PWR_TIME 4 kSPS samples.
#define 0x386 CFVARHR_LO_32 //Phase C accumulated fundamental reactive energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x387 CFVVARHR_HI_32 //Phase C accumulated fundamental reactive energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define 0x397 PWATT_ACC_32 //Accumulated Positive Total Active Power, MSBs, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 4 kSPS samples.
#define 0x39B NWATT_ACC_32 //Accumulated Negative Total Active Power, MSBs, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 4 kSPS samples.
#define 0x39F PVAR_ACC_32 //Accumulated Positive Total Reactive Power, MSBs, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 4 kSPS samples.
#define 0x3A3 NVAR_ACC_32 //Accumulated Negative Total Reactive Power, MSBs, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 4 kSPS samples
#define 0x400 IPEAK_32 //Current peak register.
/*
[31:27] RESERVED
[26:24]: IPPHASE- These bits indicate which phases generate IPEAKVAL value. Note that the PEAKSEL[2:0] bits the CONFIG3 register determine which current channel to monitor the peak value on. When IPPHASE, Bit 0 is set to 1, Phase A current generated IPEAKVAL, Bits[23:0] value. Similarly, IPPHASE, Bit 1 indicates Phase B and IPPHASE, Bit 2 indicates Phase C current generated the peak value.
[23:0]: IPEAKVAL- The IPEAK register stores the absolute value of the peak current. IPEAK is equal to xI_PCF/25
*/

#define 0x401 VPEAK_32 //Voltage peak register
// [31:27] Reserved
// [26:24] VPPHASE- These bits indicate which phases generate VPEAKVAL value. Note that the PEAKSEL[2:0] bits in the CONFIG3 register determine which voltage channels to monitor the peak value on. When VPPHASE[0] is 1, Phase A voltage generated VPEAKVAL[23:0] value. Similarly, VPPHASE[1] indicates Phase B and VPPHASE[2] indicates Phase C voltage generated the peak value.
// [23:0] VPEAKVAL- The VPEAK register stores the absolute value of the peak voltage. VPEAK is equal to xV_PCF/25.

#define 0x402 STATUS0_32 //Status Register 0
// [31:25] RESERVED
// 24 MISMTCH - This bit is set to indicate a change in the relationship between ISUMRMS and ISUMLVL
// 23 COH_WFB_FULL - This bitis set when the waveform buffer is full with resampled data, which is selected when WF_CAP_SEL = 0 in the WFB_CFG register.
// 22 WFB_TRIG - This bit is set when one of the events configured in WFB_TRIG_CFG occurs
// 21 PF_RDY - This bit goes high to indicate when the power factor measurements have been updated, every 1.024 seconds.
// [20:19] RESERVED
// 18 - PWRRDY - This bit is set when the power values in the xWATT_ACC, xVA_ACC, xVAR_ACC, xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// 17 - PAGE_FULL - This bit is set when a page enabled in the WFB_PG_IRQEN register has been filled with fixed data rate samples, when WF_CAP_SEL bit in the WFB_CFG register = 0.
// 16 - WFB_TRIG_IRQ - This bit is set when the waveform buffer has stopped filling after an event configured in WFB_TRIG_CFG occurs. This happens with fixed data rate samples only, when WF_CAP_SEL bit in the WFB_CFG register = 0.
// 15 - DREAY - This bit is set when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// 14 - CF4 - This bit is set when a CF4 pulse is issued, when the CF4 pin goes from a high to low state.
// 13 - CF3 - This bit is set when a CF3 pulse is issued, when the CF3 pin goes from a high to low state.
// 12 - CF2 - This bit is set when a CF2 pulse is issued, when the CF2 pin goes from a high to low state.
// 11 - CF1 - This bit is set when a CF1 pulse is issued, when the CF1 pin goes from a high to low state.
// 10 - REVPSUM4 - This bit is set to indicate if the CF4 polarity changed sign. For example, if the last CF4 pulse was positive reactive energy and the next CF4 pulse is negative reactive energy, the REVPSUM4 bit is set. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low
// 9 - REVPSUM3 - This bit is set to indicate if the CF3 polarity changed sign. See REVPSUM4.
// 8 - REVPSUM2 - This bit is set to indicate if the CF2 polarity changed sign. See REVPSUM4.
// 7 - REVPSUM1 - This bit is set to indicate if the CF1 polarity changed sign. See REVPSUM4.
// 6 - REVRPC - This bit indicates if the Phase C total or fundamental reactive power has changed sign. The PWR_SIGN_SEL bit in the EP_CFG register selects whether total or fundamental reactive power is monitored. This bit is updated when the power values in the xVAR_ACC and xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// 5 - REVRPB - This bit indicates if the Phase B total or fundamental reactive power has changed sign. See REVRPC.
// 5 - REVRPA - This bit indicates if the Phase A total or fundamental reactive power has changed sign. See REVRPC.
// 4 - REVRPA - This bit indicates if the Phase A total or fundamental reactive power has changed sign. See REVRPC.
// 3 - REVAPC - This bit indicates if the Phase C total active power has changed sign. This bit is updated when the power values in the xWATT_ACC and xWATT_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// 2 - REVAPB - This bit indicates if the Phase B total active power has changed sign. See REVAPC.
// 1 - REVAPA - This bit indicates if the Phase A total active power has changed sign. See REVAPC.
// 0 - EGYRDY - This bit is set when the power values in the xWATTHR, xVAHR, xVARHR, xFVARHR registers have been updated, after EGY_TIME 4 kSPS samples or line cycles, depending on the EGY_TMR_MODE bit in the EP_CFG register.

#define 0x403 STATUS1_32 //Status Register 1.
/*
31- ERROR3 - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
30 - ERROR2 - This bit indicates that an error was detected and corrected. No action is required.
29 - ERROR1 - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
28 - ERROR0 - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
27 - CRC_DONE - This bit is set to indicate when the configuration register CRC calculation is done, after initiated by writing the FORCE_CRC_UPDATE bit in the CRC_FORCE register.
26 - CRC_CHG - This bit is set if any of the registers monitored by the configuration register CRC change value. The CRC_RSLT register holds the new configuration register CRC value.
[25:19] - RESERVED - Reserved.
18 - SEQERR - This bit is set to indicate a phase sequence error on the Phase Voltage zero crossings.
17 - RESERVED - Reserved.
16 - RSTDONE - This bit is set to indicate that the IC has finished its power-up sequence after a reset or after changing between PSM2 or PSM3 operating mode to PSM0 or PSM1. This indicates that the user can configure the IC via the SPI port.
15 - ZXIC - When this bit is set to 1, it indicates a zero crossing has been detected on Phase C current.
14 - ZXIB - When this bit is set to 1, it indicates a zero crossing has been detected on Phase B current.
13 - ZXIA - When this bit is set to 1, it indicates a zero crossing has been detected on Phase A current.
12 - ZXCOMB - When this bit is set, it indicates a zero crossing has been detected on the combined signal from VA, VB, and VC.
11 - ZXVC - When this bit is set, it indicates a zero crossing has been detected on the Phase C voltage channel.
10 - ZXVB - When this bit is set, it indicates a zero crossing has been detected on the Phase B voltage channel.
9 - ZXVA - When this bit is set, it indicates a zero crossing has been detected on the Phase A voltage channel.
8 - ZXTOVC - This bit is set to indicate a zero crossing timeout on Phase C. This means that a zero crossing on the Phase C voltage is missing.
7- ZXTOVB - This bit is set to indicate a zero crossing timeout on Phase B. This means that a zero crossing on the Phase B voltage is missing.
6 ZXTOVA - This bit is set to indicate a zero crossing timeout on Phase A. This means that a zero crossing on the Phase A voltage is missing.
5 RESERVED - Reserved.
4 RFNOLOAD - This bit is set when one or more phase fundamental reactive energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
3 RESERVED - Reserved.
2 VANLOAD - This bit is set when one or more phase total apparent energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
1 RNLOAD - This bit is set when one or more phase total reactive energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
0 - ANLOAD - This bit is set when one or more phase total active energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
*/

#define 0x404 EVENT_STATUS32 //Event Status Register.
// [31:17] - RESERVED - Reserved
// 16 - DREADY - This bit changes from a one to a zero when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// 15 - RESERED - Reserved
// 14 RFNOLOAD - This bit is set when the fundamental reactive energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of fundamental reactive energy accumulation goes into no load.
// 13-  RESERVED - Reserved.
// 12 - VANLOAD - This bit is set when the total apparent energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total apparent energy accumulation goes into no load.
// 11 - RNLOAD - This bit is set when the total reactive energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total reactive energy accumulation goes into no load.
// 10 - ANLOAD - This bit is set when the total active energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total active energy accumulation goes into no load.
// 9 - REVPSUM4 - This bit indicates the sign of the last CF4 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low.
// 8 - REVPSUM3 - This bit indicates the sign of the last CF3 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF3 pulse is output, when the CF3 pin goes from high to low.
// 7 - REVPSUM2 - This bit indicates the sign of the last CF2 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF2 pulse is output, when the CF2 pin goes from high to low.
// 6 - REVPSUM1 - This bit indicates the sign of the last CF1 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF1 pulse is output, when the CF1 pin goes from high to low.
// 5[:0] - Reserved - Reserved


#define 0x405 MASK0_32 //Interrupt Enable Register 0.
// [31:25] - Reserved
// 24 MISMTCH - Set this bit to enable an interrupt when there is a change in the relationship between ISUMRMS and ISUMLVL.
// 23 - COH_WFB_FULL - Set this bit to enable an interrupt when the waveform buffer is full with resampled data, which is selected when WF_CAP_SEL = 0 in the WFB_CFG register.
// 22 - WFB_TRIG - Set this bit to enable an interrupt when one of the events configured in WFB_TRIG_CFG occurs.
// 21 - PF_RDY - Set this bit to enable an interrupt when the power factor measurements have been updated, every 1.024 seconds
// [20:19] - RESERVED - Reserved.
// 18 - PWRRDY - Set this bit to enable an interrupt when the power values in the xWATT_ACC, xVA_ACC, xVAR_ACC, xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// 17 - PAGE_FULL - Set this bit to enable an interrupt when a page enabled in the WFB_PG_IRQEN register has been filled.
// 16 - WFB_TRIG_IRQ - Set this bit to enable an interrupt when This bit is set when the waveform buffer has stopped filling after an event configured in WFB_TRIG_CFG occurs.
// 15 - DREADY - Set this bit to enable an interrupt when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// 14 - CF4 - Set this bit to enable an interrupt when the CF4 pulse is issued, when the CF4 pin goes from a high to low state.
// 13 - CF3 - Set this bit to enable an interrupt when the CF3 pulse is issued, when the CF3 pin goes from a high to low state.
// 12 - CF2 - Set this bit to enable an interrupt when the CF2 pulse is issued, when the CF2 pin goes from a high to low state.
// 11 - CF1 - Set this bit to enable an interrupt when the CF1 pulse is issued, when the CF1 pin goes from a high to low state.
// 10 - REVPSUM4 - Set this bit to enable an interrupt when the CF4 polarity changed sign.
// 9 - REVPSUM3 - Set this bit to enable an interrupt when the CF3 polarity changed sign.
// 8 - REVPSUM2 - Set this bit to enable an interrupt when the CF2 polarity changed sign.
// 7 - REVPSUM1 - Set this bit to enable an interrupt when the CF1 polarity changed sign.
// 6 - REVRPC - Set this bit to enable an interrupt when the Phase C total or fundamental reactive power has changed sign.
// 5 - REVRPB - Set this bit to enable an interrupt when the Phase C total or fundamental reactive power has changed sign.
// 4- REVRPA - Set this bit to enable an interrupt when the Phase A total or fundamental reactive power has changed sign.
// 3 - REVAPC - Set this bit to enable an interrupt when the Phase C total active power has changed sign.
// 2 - REVAPB - Set this bit to enable an interrupt when the Phase B total active power has changed sign.
// 1 - REVAPA - Set this bit to enable an interrupt when the Phase A total active power has changed sign.
// 0 - EGYRDY - Set this bit to enable an interrupt when the power values in the xWATTHR, xVAHR, xVARHR, and xFVARHR registers have been updated, after EGY_TIME 4 kSPS samples or line cycles, depending on the EGY_TMR_MODE bit in the EP_CFG register.

#define 0x406 MASK1_32 //Interrupt Enable Register 1.
// 31 - ERROR3 - Set this bit to enable an interrupt if ERROR3 occurs. Issue a software reset or hardware reset to clear this error.
// 30 - ERROR2 - Set this bit to enable an interrupt if ERROR2 occurs.
// 29 - ERROR1 - This interrupt is not maskable. Issue a software reset or hardware reset to clear this error.
// 28 - ERROR0 - This interrupt is not maskable. Issue a software reset or hardware reset to clear this error.
// 27 - CRC_DONE - Set this bit to enable an interrupt when the configuration register CRC calculation is done, after initiated by writing the FORCE_CRC_UPDATE bit in the CRC_FORCE register.
// 26 - CRC_CHG - Set this bit to enable an interrupt if any of the registers monitored by the configuration register CRC change value. The CRC_RSLT register holds the new configuration register CRC value.
// [25:19] - RESERVED - Reserved.
// 18 - SEQERR - Set this bit to set an interrupt when on a phase sequence error on the phase voltage zero crossings.
// [17:16] - RESERVED - Reserved.
// 15 - ZXIC - Set this bit to set an interrupt when a zero crossing has been detected on the Phase C current channel.
// 14 - ZXIB - Set this bit to set an interrupt when a zero crossing has been detected on the Phase B current channel.
// 13 - ZXIA - Set this bit to set an interrupt when a zero crossing has been detected on the Phase A current channel.
// 12 - ZXCOMB - Set this bit to set an interrupt when a zero crossing has been detected on the combined signal from VA, VB, and VC.
// 11 - ZXVC - Set this bit to set an interrupt when a zero crossing has been detected on the Phase C voltage channel.
// 10 - ZXVB - Set this bit to set an interrupt when a zero crossing has been detected on the Phase B voltage channel.
// 9 - ZXVA - Set this bit to set an interrupt when a zero crossing has been detected on the Phase A voltage channel.
// 8 - ZXTOVC - Set this bit to set an interrupt when there is a zero crossing timeout on Phase C. This means that a zero crossing on the Phase C voltage is missing.
// 7 - ZXTOVB - Set this bit to set an interrupt when there is a zero crossing timeout on Phase B. This means that a zero crossing on the Phase B voltage is missing
// 6 - ZXTOVA - Set this bit to set an interrupt when there is a zero crossing timeout on Phase A. This means that a zero crossing on the Phase A voltage is missing.
// 5 - RESERVED - Reserved.
// 4 - RFNOLOAD - Set this bit to set an interrupt when one or more phase total reactive energy enters or exits the no load condition.
// 3 - RESERVED - Reserved.
// 2 - VANLOAD - Set this bit to set an interrupt when one or more phase total apparent energy enters or exits the no load condition.
// 1 - RNLOAD - Set this bit to set an interrupt when one or more phase total reactive energy enters or exits the no load condition.
// 0 - ANLOAD - Set this bit to set an interrupt when one or more phase total active energy enters or exits the no load condition.

#define 0x407 EVENT_MASK_32 //Event enable register.
// [31:17] - RESERVED - Reserved.
// 16 - DREADY - Set this bit to enable the EVENT pin to go low when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// 15 - RESERVED - Reserved.
// 14 - RFNOLOAD - Set this bit to enable the EVENT pin to go low when one or more phases of fundamental reactive energy accumulation goes into no load.
// 13 - RESERVED - Reserved.
// 12 - VANLOAD - Set this bit to enable the EVENT pin to go low when one or more phases of total apparent energy accumulation goes into no load.
// 11 - RNLOAD - Set this bit to enable the EVENT pin to go low when one or more phases of total reactive energy accumulation goes into no load.
// 10 - ANLOAD - Set this bit to enable the EVENT pin to go low when one or more phases of total active energy accumulation goes into no load.
// 9 - REVPSUM4 - Set this bit to enable the EVENT pin to go low to indicate if the last CF4 pulse was from negative energy. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low.
// 8 - REVPSUM3 - Set this bit to enable the EVENT pin to go low to indicate if the last CF3 pulse was from negative energy. This bit is updated when a CF3 pulse is output, when the CF3 pin goes from high to low.
// 7 - REVPSUM2 - Set this bit to enable the EVENT pin to go low to indicate if the last CF2 pulse was from negative energy. This bit is updated when a CF2 pulse is output, when the CF2 pin goes from high to low.
// 6 - REVPSUM1 - Set this bit to enable the EVENT pin to go low to indicate if the last CF1 pulse was from negative energy. This bit is updated when a CF1 pulse is output, when the CF1 pin goes from high to low.
// [5:0] - RESERVED - Reserved.

#define 0x40E USER_PERIOD_32 //User configured line period value used for resampling when the UPERIOD_SEL bit in the CONFIG2 register is set.

#define 0x40F VLEVEL_32 //Register used in the algorithm that computes the fundamental reactive power
// Bits: [31:24] BitName: RESERVED Description: Reserved
// Bits: [23:0] BitName: VLEVEL_VAL Description: Register used in the algorithm that computes the fundamental reactive power.

#define 0x418 APERIOD_32 //Line period on Phase A voltage
#define 0x419 BPERIOD_32 //Line period on Phase B voltage
#define 0x41A CPERIOD_32 //Line period on Phase C voltage
#define 0x41B COM_PERIOD_32 //Line period measurement on combined signal from Phase A, Phase B, and Phase C voltages
#define 0x41C ACT_NL_LVL_32 //No load threshold in the total active power datapath
#define 0x41D REACT_NL_LVL_32 //No load threshold in the total and fundamental reactive power datapath.
#define 0x41E APP_NL_LVL_32 //No load threshold in the total apparent power datapath.

#define 0x41F PHNOLOAD_32 //Phase no load register.
// Bits: [31:17] BitName: RESERVED Description: Reserved
// Bits: 16 BitName: CFVARNL Description: This bit is set if the Phase C fundamental reactive energy is in no load.
// Bits: 15 BitName: RESERVED Description: Reserved
// Bits: 14 BitName: CVANL Description: This bit is set if the Phase C total apparent energy is in no load.
// Bits: 13 BitName: CVARNL Description: This bit is set if the Phase C total reactive energy is in no load.
// Bits: 12 BitName: CWATTNL Description: This bit is set if the Phase C total active energy is in no load.
// Bits: 11 BitName: RESERVED Description: Reserved
// Bits: 10 BitName: BFVARNL Description: This bit is set if the Phase B fundamental reactive energy is in no load.
// Bits: 9 BitName: RESERVED Description: Reserved
// Bits: 8 BitName: BVANL Description: This bit is set if the Phase B apparent energy is in no load.
// Bits: 7 BitName: BVARNL Description: This bit is set if the Phase B total reactive energy is in no load.
// Bits: 6 BitName: BWATTNL Description: This bit is set if the Phase B total active energy is in no load.
// Bits: 5 BitName: RESERVED Description: Reserved
// Bits: 4 BitName: AFVARNL Description: This bit is set if the Phase A fundamental reactive energy is in no load.
// Bits: 3 BitName: RESERVED Description: Reserved
// Bits: 2 BitName: AVANL Description: This bit is set if the Phase A total apparent energy is in no load.
// Bits: 1 BitName: AVARNL Description: This bit is set if the Phase A total reactive energy is in no load.
// Bits: 0 BitName: AWATTNL Description: This bit is set if the Phase A total active energy is in no load.

#define 0x420 WTHR_32 //Sets the maximum output rate from the digital to frequency converter for the total active power for the CF calibration pulse output. It is recommended to write WTHR = 0x0010 0000.
#define 0x421 VARTHR_32 //Sets the maximum output rate from the digital to frequency converter for the total and fundamental reactive power for the CF calibration pulse output. It is recommended to write VARTHR = 0x0010 0000.
#define 0x422 VATHR_32 //Sets the maximum output rate from the digital to frequency converter for the total apparent power for the CF calibration pulse output. It is recommended to write VATHR = 0x0010 0000.
#define 0x423 LAST_DATA_32_32 //This register holds the data read or written during the last 32-bittransaction on the SPI port.

#define 0x424 ADC_REDIRECT_32 //This register allows any ADC output to be redirected to any digital datapath.
// Bits: [31:21] BitName: RESERVED Description: Reserved
// Bits: [20:18] BitName: VC_DIN Description: Voltage C channel data can be selected from: Setting: 000 for IA ADC data. Setting: 001 for IB ADC data. Setting: 010 for IC ADC data. Setting: 011 for IN ADC data. Setting: 100 for VA ADC data. Setting: 101 for VB ADC data. Setting: 110 for VC ADC data. Setting: 111 for VC ADC data.
// Bits: [17:15] BitName: VB_DIN Description: VB channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for VB ADC data.
// Bits: [14:12] BitName: VA_DIN Description: VA channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for VA ADC data.
// Bits: [11:9] BitName: IN_DIN Description: IN channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IN ADC data.
// Bits: [8:6] BitName: IC_DIN Description: IC channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IC ADC data.
// Bits: [5:3] BitName: IB_DIN Description: IB channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IB ADC data.
// Bits: [2:0] BitName: IA_DIN Description: IA channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IA ADC data.

#define 0x425 CF_LCFG_32 //CF calibration pulse width configuration register.
// Bits: [31:23] BitName: RESERVED Description: Reserved
// Bits: 22 BitName: CF4_LT Description: If this bit is set, the CF4 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 21 BitName: CF3_LT Description: If this bit is set, the CF3 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 20 BitName: CF2_LT Description: If this bit is set, the CF2 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 19 BitName: CF1_LT Description: If this bit is set, the CF1 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: [18:0] BitName: CF_LTMR Description: If the CFx_LT bit in CF_LCFG register is set, this value determines the active low pulse width of the CFx pulse.

#define 0x472 PART_ID_32 //This register identifies the IC. If the ADE9000_ID bit is 0, the IC is an ADE9078
// Bits: [31:22] BitName: RESERVED Description: Reserved
// Bits: 21 BitName: Description: This bit is set to identify an ADE73370 IC.
// Bits: 20 BitName: Description: This bit is set to identify an ADE9000 IC.
// Bits: [19:17]  BitName: RESERVED Description: Reserved
// Bits: 16 BitName: Description: This bit is set to identify an ADE9004 IC.
// Bits: [15:0] BitName: RESERVED Description: Reserved

//16-Bit Registers
#define 0x480 RUN_16 //Write this register to 1 to start the measurements

#define 0x481 CONFIG1_16 //Configuration Register 1.
// Bits: 15 BitName: EXT_REF Description:
// Bits: [14:13] BitName: RESERVED Description: Reserved
// Bits: 12 BitName: IRQ0_ON_IRQ1 Description:
// Bits: 11 BitName: BURST_EN Description:
// Bits: 10 BitName: RESERVED Description: Reserved
// Bits: [9:8] BitName: PWR_SETTLE Description:
// Bits: [7:6] BitName: RESERVED Description: Reserved
// Bits: 5 BitName: CF_ACC_CLR Description: Set this bit to clear the acculumation in the digital to frequency converter and CFDEN counter. Note that this bit automatically clears itself.
// Bits: 4 BitName: RESERVED Description: Reserved
// Bits: [3:2] BitName: Description: These bits select which function to output on the CF4 pin. Setting: 00 for CF4, from digital to frequency converter. Setting: 01 for CF4, from digital to frequency converter. Setting: 10 for EVENT. Setting: 11 for DREADY.
// Bits: 1 BitName: CF3_CFG Description: This bit selects which function to output on the CF3 pin. Setting: 0 for CF3, from digital to freqency converter. Setting: 1 for Zero Crossing output selected by the ZX_SEL bits in the ZX_LP_SEL register.
// Bits: 0 BitName: SWRST Description: Set this bit to initiate a software reset. Note that this bit is self clearing.

#define 0x482 ANGL_VA_VB_16 //Time between positive to negative zero crossings on Phase A and Phase B voltages.
#define 0x483 ANGL_VB_VC_16 //Time between positive to negative zero crossings on Phase B and Phase C voltages.
#define 0x484 ANGL_VA_VC_16 //Time between positive to negative zero crossings on Phase A and Phase C voltages.
#define 0x485 ANGL_VA_IA_16 //Time between positive to negative zero crossings on Phase A voltage and current.
#define 0x486 ANGL_VB_IB_16 //Time between positive to negative zero crossings on Phase B voltage and current.
#define 0x487 ANGL_VC_IC_16 //Time between positive to negative zero crossings on Phase C voltage and current.
#define 0x488 ANGL_IA_IB_16 //Time between positive to negative zero crossings on Phase A and Phase B current.
#define 0x489 ANGL_IB_IC_16 //Time between positive to negative zero crossings on Phase B and Phase C current.
#define 0x48A ANGL_IA_IC_16 //Time between positive to negative zero crossings on Phase A and Phase C current

#define 0x490 CFMODE_16 //CFx configureation register
// Bits: 15 BitName: CF4DIS Description: CF4 output disable. Set this bit to disable the CF4 output and bring the pin high. Note that when this bit is set, the CFx bit in STATUS0 is not set when a CF pulse is accumulated in the digital to frequency converter.
// Bits: 14 BitName: CF3DIS Description: CF1 output disable -- see CF4DIS
// Bits: 13 BitName: CF2DIS Description: CF1 output disable -- see CF4DIS
// Bits: 12 BitName: CF1DIS Description: CF1 output disable -- see CF4DIS
// Bits: [11:9] BitName: CF4SEL Description: Type of energy output on the CF4 pin. Configure TERMSEL4 in the COMPMODE register to select which phases are included. Setting: 000 for Total Active Power. Setting: 001 for Total Reactive Power. Setting: 010 for Total Apparent Power. Setting: 100 for Fundamental reactive power. Setting: 110 for Total Active Power. Setting: 111 for Total Active Power.
// Bits: [8:6] BitName: CF3SEL Description: Selects type of energy output on CF3 pin --see CF4SEL
// Bits: [5:3] BitName: CF2SEL Description: Selects type of energy output on CF2 pin --see CF4SEL
// Bits: [2:0] BitName: CF1SEL Description: Selects type of energy output on CF1 pin --see CF4SEL

#define 0x491 COMPMODE_16 //Computation mode register
// Bits: [15:12] BitName: RESERVED Description: Reserved
// Bits: [11:9] BitName: TERMSEL4 Description: Phases to include in CF4 pulse output. Set the TERMSEL4[2] bit to one to include Phase C in the CF4 pulse output. Similarly, set TERMSEL4[1] to include Phase B and TERMSEL4[0] for Phase A.
// Bits: [8:6] BitName: TERMSEL3 Description: Phases to include in CF3 pulse output --see TERMSEL4
// Bits: [5:3] BitName: TERMSEL2 Description: Phases to include in CF2 pulse output --see TERMSEL4
// Bits: [2:0] BitName: TERMSEL1 Description: Phases to include in CF1 pulse output --see TERMSEL4

#define 0x492 ACCMODE_16 //Accumulation mode register
// Bits: [15:9] BitName: RESERVED Description: Reserved
// Bits: 8 BitName: Description:This bit is used to configure the IC for a 50 Hz or 60 Hz system. This setting is used in the fundamental reactive power measurement and to set the default line period used for resampling calculations if a zero crossing is not present. Setting: 0 for 50 Hz. Setting: 1 for 60 Hz.
// Bits: 7 BitName: ICONSEL Description: Set this bit to calculate the current flowing through IB from the IA and IC measurements. if this bit is set, IB = -IA - IC.
// Bits: [6:4] BitName: VCONSEL Description: Three-wire and four-wire hardware configuration selection. Setting: 000 for 4-wire wye. Setting: 001 for 3-wire delta. VB' = VA-VC. Setting: 010 for 4-wire delta, non-Blondel compliant. VB' = -VA - VC. Setting: 011 for 4-wire delta non-Blondel compliant. VB' = -VA. Setting: 100 for 3-wire delta. VA'=VA-VB; VB' = VA-VC; VC'=VC-VB.
// Bits: [3:2] BitName: VARACC Description: Total and fundamental reactive power accumulation mode for energy registers and CFx pulses. Setting: 00 for Signed accumulation mode. Setting: 01 for Absolute Value accumulation mode. Setting: 10 for Positve accumulation mode. Setting: 11 for Negative accumulation mode.
// Bits: [1:0] BitName: WATTACC Description: Total and fundamental active power accumulation mode for energy registers and CFx pulses--see VARACC.

#define 0x493 CONFIG3_16 //Configuraiton Register 3
// Bits: [15:5] BitName: RESERVED Description: Reserved
// Bits: [4:2] BitName: PEAKSEL Description: Set this bit to select which phase(s) to monitor peak voltages and currents on. Write PEAKSEL[0] to one to enable Phase A peak detection. Similarly, PEAKSEL[1] enables Phase B peak detection and PEAKSEL[2] enables Phase C peak detection.
// Bits: [1:0] BitName: RESERVED Description: Reserved

#define 0x494 CF1DEN_16 //CF1 denominator register
#define 0x495 CF2DEN_16 //CF2 denominator register
#define 0x496 CF3DEN_16 //CF3 denominator register
#define 0x497 CF4DEN_16 //CF4 denomoinator register
#define 0x498 ZXTOUT_16 //Zero-crossing timeout configuration register.
#define 0x499 ZXTHRSH_16 //Voltage channel zero-crossing threshold register.

#define 0x49A ZX_LP_SEL_16 //This register selects which zero crossing and which line period measurement are used for other calculations.
// Bits: [15:5] BitName: RESERVED Description: Reserved
// Bits: [4:3] BitName: LP_SEL Description: Selects line period measurement used for resampling. Setting: 00 APERIOD, line period measurement from Phase A voltage. Setting: 01 for BPERIOD, line period measurement from Phase B voltage. Setting: 10 for CPERIOD, line period measurement from Phase C voltage. Setting: 11 for COM_PERIOD, line period measurement on combined signal from VA, VB, and VC.
// Bits: [2:1] BitName: ZX_SEL Description: Selects the zero-crossing signal, which can be routed to CF3/ZX output pin and which is used for line cycle energy accumulation. Setting: 00 for ZXVA, Phase A voltage zero-crossing signal. Setting: 01 ZXVB, Phase B voltage zero-crossing signal.  Setting: 10 for ZXVC, Phase C voltage zero-crossing signal. Setting: 11 for ZXCOMB, zero crossing on combined signal from VA,VB and VC.
// Bits: 0 BitName: RESERVED Description: Reserved

#define 0x49C SEQ_CYC_16 //Number of line cycles used for phase sequence detection. It is recommended to set this register to 1.
#define 0x49D PHSIGN_16 //Power sign register
// Bits: [15:10] Bitname: RESERVED Description: Reserved
// Bits: 9 BitName: SUM4SIGN Description: Sign of the sum of the powers included in the CF4 datapath. The CF4 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 8 BitName: SUM3SIGN Description: Sign of the sum of the powers included in the CF3 datapath. The CF3 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 7 BitName: SUM2SIGN Description: Sign of the sum of the powers included in the CF2 datapath. The CF2 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 6 BitName: SUM1SIGN Description: Sign of the sum of the powers included in the CF1 datapath. The CF1 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 5 BitName: CVARSIGN Description: Phase C reactive power sign bit. The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 4 BitName: CWSIGN Description: Phase C active power sign bit
// Bits: 3 BitName: BVARSIGN Description: Phase B reactive power sign bit. The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 2 BitName: BWSIGN Description: Phase B active power sign bit.
// Bits: 1 BitName: AVARSIGN Description: Phase A reactive power sign bit.  The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 0 BitName: AWSIGN Description: Phase A active power sign bit
#define 0x4A0 WFB_CFG_16 //Waveform buffer configuration register
// Bits: [15:13] Bitname: RESERVED Description: Reserved
// Bits: 12 BitName: WF_IN_EN Description: This setting determines whether the IN waveform samples are read out of the waveform buffer through SPI. 0: IN waveform samples are not read out of waveform buffer through SPI. 1: IN waveform samples are read out of waveform buffer through SPI
// Bits: [11:10] BitName: RESERVED Description: Sign of the sum of the powers included in the CF3 datapath. The CF3 energy is positive if this bit is clear and negative if this bit is set.
// Bits: [9:8] BitName: WF_SRC Description: Waveform buffer souce and DREADY, data ready update rate, selection. 00: Sinc4 output, at 16kSPS. 01: Reserved. 10: Sinc4 + IIR LPF output, at 4 kSPS. 11: Current and voltage channel waveform samples, processed by the DSP (xl_PCF, xV_PCF) at 4 kSPS.
// Bits: [7:6] BitName: WF_MODE Description: fixed data rate waveforms filling and trigger based modes. 00: stop when waveform buffer is full. 01: continuous fill-stop only on enabled trigger events. 10: Continuous filling-center capture around enabled trigger events. 11: continuous fill-save event address of enabled trigger events
// Bits: 5 BitName: WF_CAP_SEL Description: This bit selects whether the waveform buffer is filled with resampled data or fixed data rate data, selected in the WF_CAP_SEL bits. 0: resampled data. 1: fixed data rate data
// Bits: 4 BitName: WF_CAP_EN Description: When this bit is set, waveform capture is started. 0: the waveform capture is disabled. the waveform buffer contents are maintained. 1: the waveform capture is started, according to the type of capture in WF_CAP_SEL and the WF_SRC bits when this bit goes from a 0 to a 1.
// Bits: [3:0] BitName: BURST_CHAN Description: selects which data to read out of the waveform buffer through SPI. 0000: all channels. 0001: IA and VA. 0010: IB and VB. 0011: IC and VC. 1000: IA. 1001: VA. 1010: IB. 1011:VB 1100:IC. 1101:VC. 1110:In if WF_IN_EN =1 in the WFB_CFG registers. 1111: single address read (SPI burst read mode is disabled)
#define 0x4A1 WFB_PG_IRQEN_16 //This register enables interrupts to occur after specific pages of the waveform buffer have been filled.
#define 0x4A2 WFB_TRG_CFG_16 //This register enables events to trigger a capture in the waveform buffer
// Bits: [15:11] Bitname: RESERVED Description: Reserved
// Bits: 10 Bitname: TRIG_FORCE Description: Set this bit to trigger an even to stop the waveform buffer filling
// Bits: 9 Bitname: ZXCOMB Description: Zero crossing on combined signal from VA, VB, and VC
// Bits: 8 Bitname: ZXVC Description: Phase C voltage zero crossing.
// Bits: 7 Bitname: ZXVB Description: Phase B voltage zero crossing.
// Bits: 6 Bitname: ZXVA Description: Phase A voltage zero crossing.
// Bits: 5 Bitname: ZXIC Description: Phase C current zero crossing.
// Bits: 4 Bitname: ZXIB Description: Phase B current zero crossing.
// Bits: 3 Bitname: ZXIA Description: Phase A current zero crossing.
// Bits: [2:0] Bitname: RESERVED Description: Reserved
#define 0x4A3 WFB_TRG_STAT_16 //This register indicates the last page that was filled in the waveform buffer and the location of trigger events.
// Bits: [15:12] Bitname: WFB_LAST_PAGE Description: These bits indicate which page of the waveform buffer was filled last, when filling with fixed rate data samples
// Bits: 11 Bitname: RESERVED Description: Reserved
// Bits: [10:0]  Bitname: UPERIOD_SEL Description: This hilds the address of the last sample put into the waveform buffer after a trigger event occured, which is within a sample or two of when the actual trigger event occurred.
#define 0x4A4 CONFIG5_16 //Configuration Register 5
#define 0x4A8 CRC_RSLT_16 //This register holds the CRC of configuration registers.
#define 0x4A9 CRC_SPI_16 //This register holds the 16-bit CRC of the data sent out on the MOSI pin during the last SPI register read.
#define 0x4AC LAST_DATA_16 //This register holds the data read or written during the last 16-bit transaction on the SPI port.
#define 0x4AE LAST_CMD_16 //This register holds the address and read/write operation request (CMD_HDR) for the last transaction on the SPI port.
#define 0x4AF CONFIG2_16 //Configuration Register 2
// Bits [15:13] Bitname: RESERVED Description: Reserved
// Bits 12 Bitname: UPERIOD_SEL Description: Set this bit to use a user configured line period, in USER_PERIOD, for the resampling calculation. If this bit is clear, the phase voltage line period selected by the LP_SEL[1:0] bits in the ZX_LP_SEL register is used.
// Bits [11:9] Bitname: HPF_CRN Description: High-Pass filter corner (f3dB) enabled when the HPFDIS is bit in the CONFIGO register=0
//000 38.695 Hz.
//001 19.6375 Hz.
//010 9.895 Hz.
//011 4.9675 Hz.
//100 2.49 Hz.
//101 1.2475 Hz.
//110 0.625 Hz.
//111 0.3125 Hz.
// Bits [8:0] Bitname: RESERVED Description: Reserved.
#define 0x4B0 EP_CFG_16 //Energy and power accumulation configuration
// Bits [15:13] Bitname: NOLOAD_TMR Description: This register configures how many 4 kSPS samples to evaluate the no load condition convert
//000 64.
//001 128.
//010 256.
//011 512.
//100 1024.
//101 2048.
//110 4096.
//111 Disable no load threshold.

// Bits [12:8] Bitname: RESERVED Description: Reserved
// Bits 7 Bitname: PWR_SIGN_SEL Description: Selects whether the REVRPx bit follows the sign of the total or fundamental reactive power. 0: Total reactive power. 1: Fundamental reactive power
// Bits 6 Bitname: RESERVED  Description: Reserved
// Bits 5 Bitname: RD_RST_EN Description: Set this bit to enable the energy register read with reset feature. If this bit is set, when one of the xWATTHR, xVAHR, xVARHR and xFVARHR register is read, it is reset and begins accumulating energy from zero.
// Bits 4 Bitname: EGY_LD_ACCUM Description: If this bit = 0, the internal energy register is added to the user accessible energy register. If the bit is set, the internal energy register overwrites the user accessible energy register when the EGYRDY event occurs.
// Bits [3:2] Bitname: RESERVED Description: Reserved
// Bits 1 Bitname: EGY_TMR_MODE Description: This bit determines whether energy is accumulated based on the number of 4 kSPS samples or zero crossing events configured in the EGY_TIME register
        // 0 Accumulate energy based on 4 kSPS samples.
        // 1 Accumulate energy based on the zero crossing selected by the ZX_SEL bits in the ZX_LP_SEL register.
// Bits 0 Bitname: EGY_PWR_EN Description: Set this bit to enable the energy and power accumulator, when the run bit is also set.

#define 0x4B1 PWR_TIME_16 //POwer and time configuration
#define 0x4B2 EGY_TIME_16 //Energy accumulation update time configuration
#define 0x4B4 CRC_FORCE_16 //This register forces an update of the CRC of configuration registers.
// Bits [15:1] Bitname: RESERVED Description: RESERVED
// Bits 0 Bitname: FORCE_CRC_UPDATE Description: Write this bit to force the configuration register CRC calculation to start. When the calculation is complete, the CRC_DONE bit is set in the STATUS1 register

#define 0x4B5 CRC_OPTEN_16 //This register selects which registers are optionally included in the configuration register CRC feature
// 15 CRC_WFB_TRG_CFG_EN - Set this bit to include the WFB_TRG_CFG register in the configuration register CRC calculation.
// 14 CRC_WFB_PG_IRQEN - Set this bit to include the WFB_PG_IRQEN register in the configuration register CRC calculation.
// 13 CRC_WFB_CFG_EN - Set this bit to include the WFB_CFG register in the configuration register CRC calculation.
// 12 CRC_SEQ_CYC_EN - Set this bit to include the SEQ_CYC register in the configuration register CRC calculation.
// 11 CRC_ZXLPSEL_EN - Set this bit to include the ZX_LP_SEL register in the configuration register CRC calculation.
// 10 CRC_ZXTOUT_EN - Set this bit to include the CRC_ZXTOUT_EN register in the configuration register CRC calculation.
// 9 CRC_APP_NL_LVL_EN - Set this bit to include the APP_NL_LVL register in the configuration register CRC calculation.
// 8 CRC_REACT_NL_LVL_EN - Set this bit to include the REACT_NL_LVL register in the configuration register CRC calculation.
// 7 CRC_ACT_NL_LVL_EN - Set this bit to include the ACT_NL_LVL register in the configuration register CRC calculation.
// [6:3] RESERVED - Reserved.
// 2 CRC_EVENT_MASK_EN -Set this bit to include the EVENT_MASK register in the configuration register CRC calculation.
// 1 CRC_MASK1_EN - Set this bit to include the MASK1 register in the configuration register CRC calculation.
// 0 CRC_MASK0_EN - Set this bit to include the MASK0 register in the configuration register CRC calculation.


#define 0x4B8 PSM2_CFG_16 /* This register configures settings for the low power PSM2 operating mode. This register value is retained in PSM2 and PSM3 but is rewritten to its default value when entering PSM0 and PSM1. */
// [15:9] - Reservedd
// [8:5] - PKDET_LVL //These bits configure the PSM2 low power comparator peak current detection Level, listed as the input signal level with respect to full scale. The register value is retained in PSM2 and PSM3. It returns to its default value if PSM0 is entered.
    // 0000 100:1
    // 0001 200:1
    // 0010 300:1
    // 0011 400:1
    // 0100 500:1
    // 0101 600:1
    // 0110 700:1
    // 0111 800:1
    // 1000 900:1
    // 1001 1000:1
    // 1010 1100:1
    // 1011 1200:1
    // 1100 1300:1
    // 1101 1400:1
    // 1110 1500:1
    // 1111 1600:1
// [4:0] LPLINE - This register determines the time used to detect 0x1F R/W peak currents in the low power comparator in
//  PSM2 operating mode. Note that this register
//  retains its value in PSM2 and PSM3 operating
//  modes but is reset to its default value upon entering PSM0 or PSM1.

#define 0x4B9 PGA_GAIN_16 /*This register configures the PGA gain for each ADC */
// [15:14] RESERVED - Reserved.
// [13:12] VC_GAIN - PGA gain for Voltage Channel C ADC. 0x0 R/W
    //  00 Gain = 1.
    //  01 Gain = 2.
    //  10 Gain = 4.
    //  11 Gain = 4.
// [11:10] VB_GAIN - PGA gain for Voltage Channel B ADC. See 0x0 R/W VC_GAIN.
// [9:8] VA_GAIN - PGA gain for Voltage Channel A ADC. See 0x0 R/W VC_GAIN.
// [7:6] IN_GAIN - PGA gain for neutral current channel ADC. See 0x0 R/W VC_GAIN.
// [5:4] IC_GAIN - PGA gain for Current Channel C ADC. See 0x0 R/W VC_GAIN.
// [3:2] IB_GAIN - PGA gain for Voltage Channel B ADC. See 0x0 R/W VC_GAIN.
// [1:0] IA_GAIN - PGA gain for Current Channel A ADC. See 0x0 R/W VC_GAIN.

#define 0x4BA CHNL_DIS_16 /* This register can be disables the ADCs individually */
// [15:7] RESERVED - Reserved.
// 6 VC_DISAD - Set this bit to one to disable the ADC.
// 5 VB_DISADC - Set this bit to one to disable the ADC.
// 4 VA_DISADC - Set this bit to one to disable the ADC.
// 3 IN_DISADC  - Set this bit to one to disable the ADC.
// 2 IC_DISADC  - Set this bit to one to disable the ADC.
// 1 IB_DISADC  - Set this bit to one to disable the ADC.
// 0 IA_DISADC - Set this bit to one to disable the ADC.


#define 0x4BF WR_LOCK_16 /* This register enables the configuration lock feature */
#define 0x4E0 VAR_DIS_16 /* Enable/disable total reactive power calculation */
// [15:1] - Reserved - Reserved.
// 0 - VARDIS - Set this bit to disable the total VAR calculation. This 0x0 R/W bit must be set before writing the run bit for proper operation.

#define 0x4F0 RESERVED1_16 /* This register is reserved */
#define 0x4FE VERSION_16 /* Version of the ADE9078 IC */
#define 0x500 AI_SINC_DAT_32 /* Current Channel A ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x501 AV_SINC_DAT_32 /* Voltage Channel A ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x502 BI_SINC_DAT_32 /* Current Channel B ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x503 BV_SINC_DAT_32 /* Voltage Channel B ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x504 CI_SINC_DAT_32 /* Current Channel C ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x505 CV_SINC_DAT_32 /* Voltage Channel C ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x506 NI_SINC_DAT_32 /* Neutral current channel ADC waveforms from sinc4 output, at 16 kSPS */
#define 0x510 AI_LPF_DAT_32 /* Current Channel A ADC waveforms from sinc4 + IIR LPF and decimator output, at 4 kSPS */
#define 0x511 AV_LPF_DAT_32 /* Voltage Channel A ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define 0x512 BI_LPF_DAT_32 /* Current Channel B ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define 0x513 BV_LPF_DAT_32 /* Voltage Channel B ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define 0x514 CI_LPF_DAT_32 /* Current Channel C ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define 0x515 CV_LPF_DAT_32 /* Voltage Channel C ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define 0x516 NI_LPF_DAT_32 /* Neutral current channel ADC waveforms from since4 + IIR LPF output, at 4 kSPS*/
#define 0x600 AV_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See AV_PCF in Table 31*/
#define 0x601 BV_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See BV_PCF in Table 31*/
#define 0x602 CV_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See CV_PCF in Table 31*/
#define 0x603 NI_PCF-1_32 /* SPI burst read accessible. Registers organized functionally. See NI_PCF in Table 31*/
#define 0x604 AI_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See AI_PCF in Table 31*/
#define 0x605 BI_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See BI_PCF in Table 31*/
#define 0x606 CI_PCF_1_32 /* SPI burst read accessible. Registers organized functionally. See CI_PCF in Table 31*/
#define 0x607 AIRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See AIRMS in Table 31*/
#define 0x608 BIRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See BIRMS in Table 31*/
#define 0x609 CIRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See CIRMS in Table 31*/
#define 0x60A AVRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See AVRMS in Table 31*/
#define 0x60B BVRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See BVRMS in Table 31*/
#define 0x60C CVRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See CVRMS in Table 31*/
#define 0x60D NIRMS_1_32 /* SPI burst read accessible. Registers organized functionally. See NIRMS in Table 31*/
#define 0x60E AWATT_1_32 /* SPI burst read accessible. Registers organized functionally. See AWATT in Table 31*/
#define 0x60F BWATT_1_32 /* SPI burst read accessible. Registers organized functionally. See BWATT in Table 31*/
#define 0x610 CWATT_1_32 /* SPI burst read accessible. Registers organized functionally. See CWATT in Table 31*/
#define 0x611 AVA_1_32 /* SPI burst read accessible. Registers organized functionally. See AVA in Table 31*/
#define 0x612 BVA_1_32 /* SPI burst read accessible. Registers organized functionally. See BVA in Table 31*/
#define 0x613 CVA_1_32 /* SPI burst read accessible. Registers organized functionally. See CVA in Table 31*/
#define 0x614 AVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See AVAR in Table 31*/
#define 0x615 BVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See BVAR in Table 31*/
#define 0x616 CVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See CVAR in Table 31*/
#define 0x617 AFVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See AFVAR in Table 31*/
#define 0x618 BFVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See BFVAR in Table 31*/
#define 0x619 CFVAR_1_32 /* SPI burst read accessible. Registers organized functionally. See CFVAR in Table 31*/
#define 0x61A APF_1_32 /* SPI burst read accessible. Registers organized functionally. See APF in Table 31*/
#define 0x61B BPF_1_32 /* SPI burst read accessible. Registers organized functionally. See BPF in Table 31*/
#define 0x61C CPF_1_32 /* SPI burst read accessible. Registers organized functionally. See CPF in Table 31*/
#define 0x680 AV_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See AV_PCF in Table 31*/
#define 0x681 AI_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See AI_PCF in Table 31*/
#define 0x682 AIRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See AIRMS in Table 31*/
#define 0x683 AVRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See AVRMS in Table 31*/
#define 0x684 AWATT_2_32 /* SPI burst read accessible. Registers organized functionally. See AWATT in Table 31*/
#define 0x685 AVA_2_32 /* SPI burst read accessible. Registers organized functionally. See AVA in Table 31*/
#define 0x686 AVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See AVAR in Table 31*/
#define 0x687 AFVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See AFVAR in Table 31*/
#define 0x688 APF_2_32 /* SPI burst read accessible. Registers organized functionally. See APF in Table 31*/
#define 0x693 BV_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See BV_PCF in Table 31*/
#define 0x694 BI_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See BI_PCF in Table 31*/
#define 0x695 BIRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See BIRMS in Table 31*/
#define 0x696 BVRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See BVRMS in Table 31*/
#define 0x697 BWATT_2_32 /* SPI burst read accessible. Registers organized functionally. See BWATT in Table 31*/
#define 0x698 BVA_2_32 /* SPI burst read accessible. Registers organized functionally. See BVA in Table 31*/
#define 0x699 BVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See BVAR in Table 31*/
#define 0x69A BFVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See BFVAR in Table 31*/
#define 0x69B BPF_2_32 /* SPI burst read accessible. Registers organized functionally. See BPF in Table 31*/
#define 0x6A6 CV_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See CV_PCF in Table 31*/
#define 0x6A7 CI_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See CI_PCF in Table 31*/
#define 0x6A8 CIRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See CIRMS in Table 31*/
#define 0x6A9 CVRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See CVRMS in Table 31*/
#define 0x6AA CWATT_2_32 /* SPI burst read accessible. Registers organized functionally. See CWATT in Table 31*/
#define 0x6AB CVA_2_32 /* SPI burst read accessible. Registers organized functionally. See CVA in Table 31*/
#define 0x6AC CVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See CVAR in Table 31*/
#define 0x6AD CFVAR_2_32 /* SPI burst read accessible. Registers organized functionally. See CFVAR in Table 31*/
#define 0x6AE CPF_2_32 /* SPI burst read accessible. Registers organized functionally. See CPF in Table 31*/
#define 0x6B9 NI_PCF_2_32 /* SPI burst read accessible. Registers organized functionally. See NI_PCF in Table 31*/
#define 0x6BA NIRMS_2_32 /* SPI burst read accessible. Registers organized functionally. See NIRMS in Table 31*/






//****************User Program Functions*****************

uint8_t ADE7953::getVersion(){
  return spiAlgorithm8_read(functionBitVal(Version_8,1), functionBitVal(Version_8,0));  //An example of the address lookup - the spiAlgorithm8_read((functionBitVal(addr,1), functionBitVal(addr,1)) would return the eqivenet to spiAlgorithm8_read(0x07,0x02) when working properly
}

float ADE7953::getPowerFactorA(){
	int16_t value=0;
	value=spiAlgorithm16_read((functionBitVal(PFA_16,1)),(functionBitVal(PFA_16,0)));
	float decimal = decimalize(value, 327.67, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

int16_t ADE7953::getPhaseCalibA(){
	int16_t value=0;
	value=spiAlgorithm16_read((functionBitVal(PHCALA_16,1)),(functionBitVal(PHCALA_16,0)));
return value;
  }

float ADE7953::getPeriod(){
	uint16_t value=0;
	value=spiAlgorithm16_read((functionBitVal(Period_16,1)),(functionBitVal(Period_16,0)));
	float decimal = decimalize(value, 1, 0); //convert to float with calibration factors specified
return decimal;
  }

unsigned long ADE7953::getAPNOLOAD(){  //use signed long for signed registers, and unsigned long for unsigned registers
	unsigned long value=0;  //use signed long for signed registers, and unsigned long for unsigned registers
	value=spiAlgorithm32_read((functionBitVal(AP_NOLOAD_32,1)),(functionBitVal(AP_NOLOAD_32,0))); //Call MSB and LSB from the register constant (template for how all functions should be called)
return value;
  }

long ADE7953::getInstVoltage(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(V_32,1)),(functionBitVal(V_32,0)));
return value;
  }

float ADE7953::getVrms(){
	unsigned long value=0;
	value=spiAlgorithm32_read((functionBitVal(VRMS_32,1)),(functionBitVal(VRMS_32,0)));
	float decimal = decimalize(value, 19090, 0); //convert to float with calibration factors specified
return decimal;
  }

long ADE7953::getInstCurrentA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(IA_32,1)),(functionBitVal(IA_32,0)));
return value;
  }

float ADE7953::getIrmsA(){
	unsigned long value=0;
	value=spiAlgorithm32_read((functionBitVal(IRMSA_32,1)),(functionBitVal(IRMSA_32,0)));
	float decimal = decimalize(value, 1327, 0); //convert to float with calibration factors specified
return decimal;
  }

unsigned long ADE7953::getVpeak(){
	unsigned long value=0;
	value=spiAlgorithm32_read((functionBitVal(VPEAK_32,1)),(functionBitVal(VPEAK_32,0)));
return value;
  }

unsigned long ADE7953::getIpeakA(){
	unsigned long value=0;
	value=spiAlgorithm32_read((functionBitVal(IAPEAK_32,1)),(functionBitVal(IAPEAK_32,0)));
return value;
  }

long ADE7953::getActiveEnergyA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(AENERGYA_32,1)),(functionBitVal(AENERGYA_32,0)));
return value;
  }

long ADE7953::getReactiveEnergyA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(RENERGYA_32,1)),(functionBitVal(RENERGYA_32,0)));
return value;
  }

long ADE7953::getApparentEnergyA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(APENERGYA_32,1)),(functionBitVal(APENERGYA_32,0)));
return value;
  }

float ADE7953::getInstApparentPowerA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(AVA_32,1)),(functionBitVal(AVA_32,0)));
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE7953::getInstActivePowerA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(AWATT_32,1)),(functionBitVal(AWATT_32,0)));
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return abs(decimal);
  }

float ADE7953::getInstReactivePowerA(){
	long value=0;
	value=spiAlgorithm32_read((functionBitVal(AVAR_32,1)),(functionBitVal(AVAR_32,0)));
	float decimal = decimalize(value, 1.502, 0); //convert to float with calibration factors specified
return decimal;
  }

//*******************************************************


//****************ADE 7953 Library Control Functions**************************************

//****************Object Definition*****************
ADE7953::ADE7953(int SS, int SPI_freq)
{
  _SS=SS;
  _SPI_freq=SPI_freq;
  }
//**************************************************

//****************Initialization********************
void ADE7953::initialize(){

  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953:initialize function started ");
  #endif

  pinMode(_SS, OUTPUT); // FYI: SS is pin 10 by Arduino's SPI library on many boards (including the UNO), set SS pin as Output
  digitalWrite(_SS, HIGH); //Initialize pin as HIGH to bring communication inactive
  SPI.begin();
  delay(50);
  SPI.setBitOrder(MSBFIRST);  //Define MSB as first (explicitly)
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  delay(50);

  //Write 0x00AD to Register Address 0x00FE. "This unlocks Register 0x120." per datasheet
  digitalWrite(_SS, LOW);//Enable data transfer by bringing SS line LOW.
  SPI.transfer(0x00); //Pass in MSB of register 0x00FE first.
  SPI.transfer(0xFE); //Pass in LSB of register 0x00FE next.
  SPI.transfer(WRITE); //This tells the ADE7953 that data is to be written to register 0x00FE, per datasheet
  SPI.transfer(0x00); //Pass in MSB of 0x00AD first to write to 0x00FE, per datasheet
  SPI.transfer(0xAD); //Pass in LSB of 0x00AD next to write to 0x00FE, per datasheet

  //Write 0x0030 to Register Address 0x0120. "This configures the optimum settings." per datasheet
  SPI.transfer(0x01); //Pass in MSB of register 0x0120 first, per datasheet
  SPI.transfer(0x20); //Pass in LSB of register 0x0120 next, per datasheet
  SPI.transfer(WRITE);//This tells the ADE7953 that data is to be written to register 0x0120, per datasheet
  SPI.transfer(0x00); //Pass in MSB of 0x0030 first to write to 0x0120, per datasheet
  SPI.transfer(0x30); //Pass in LSB of 0x0030 next to write to 0x0120, per datasheet
  SPI.endTransaction();
  digitalWrite(_SS, HIGH);//End data transfer by bringing SS line HIGH.
  delay(100);
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print(" ADE7953:initialize function completed ");
  #endif

  //Default Calibrations - Per Datasheet
  //spiAlgorithm16_write((functionBitVal(PHCALA_16,1)),(functionBitVal(PHCALA_16,0)),0x00,0x00);
  //delay(100);
  spiAlgorithm32_write((functionBitVal(AP_NOLOAD_32,1)),(functionBitVal(AP_NOLOAD_32,0)),0x00,0x00,0x00,0x01); //Check for ensuring read and write operations are okay
  delay(100);
  spiAlgorithm8_write((functionBitVal(LCYCMODE_8,1)),(functionBitVal(LCYCMODE_8,0)),0b01111111); //Enable line cycle accumulation mode for all energies and channels
  delay(100);
  spiAlgorithm16_write((functionBitVal(LINECYC_16,1)),(functionBitVal(LINECYC_16,0)),0x00,0x78); //Sets number of half line cycle accumulations to 120
  delay(100);

}
//**************************************************

byte ADE7953::functionBitVal(int addr, uint8_t byteVal)
{
//Returns as integer an address of a specified byte - basically a byte controlled shift register with "byteVal" controlling the byte that is read and returned
  int x = ((addr >> (8*byteVal)) & 0xff);
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::functionBitVal function details: ");
   Serial.print("Address input (dec): ");
   Serial.print(addr, DEC);
   Serial.print(" Byte requested (dec): ");
   Serial.print(byteVal, DEC);
   Serial.print(" Returned Value (dec): ");
   Serial.print(x, DEC);
   Serial.print(" Returned Value (HEX): ");
   Serial.print(x, HEX);
   Serial.print(" ADE7953::functionBitVal function completed ");
  #endif
  return x;
}

uint8_t ADE7953::spiAlgorithm8_read(byte MSB, byte LSB) { //This is the algorithm that reads from a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm8_read function started ");
  #endif
  uint8_t readval_unsigned = 0;  //This variable is the unsigned integer value to compile read bytes into (if needed)
  byte one;
  byte two; //This may be a dummy read, it looks like the ADE7953 is outputting an extra byte as a 16 bit response even for a 1 byte return
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Read in values sequentially and bitshift for a 32 bit entry
  SPI.transfer(READ); //Send command to begin readout
  one = (SPI.transfer(WRITE));  //MSB Byte 1  (Read in data on dummy write (null MOSI signal)) - only one needed as 1 byte
  two = (SPI.transfer(WRITE));  //"LSB "Byte 2?"  (Read in data on dummy write (null MOSI signal)) - only one needed as 1 byte, but it seems like it responses will send a byte back in 16 bit response total, likely this LSB is useless, but for timing it will be collected.  This may always be a duplicate of the first byte,
  SPI.endTransaction(); //end SPI communication
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH (device made inactive)

  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm8_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Returned bytes (1(MSB) and 2 - 2nd is for 16-bit return form): ");
   Serial.print(one, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.print(" ADE7953::spiAlgorithm8_read function completed ");
  #endif

  //Post-read packing and bitshifting operation
    readval_unsigned = one;  //Process MSB (nothing much to see here for only one 8 bit value - nothing to shift)
	return readval_unsigned;  //uint8_t versus long because it is only an 8 bit value, function returns uint8_t.
 }


uint16_t ADE7953::spiAlgorithm16_read(byte MSB, byte LSB) { //This is the algorithm that reads from a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm16_read function started ");
  #endif
  uint16_t readval_unsigned = 0;  //This variable is the unsigned integer value to compile read bytes into (if needed)
  byte one;
  byte two;
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Read in values sequentially and bitshift for a 32 bit entry
  SPI.transfer(READ); //Send command to begin readout
  one = SPI.transfer(WRITE);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two = SPI.transfer(WRITE);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
  SPI.endTransaction();
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm16_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
   Serial.print(one, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.print(" ADE7953::spiAlgorithm16_read function completed ");
  #endif

   //Post-read packing and bitshifting operation
   readval_unsigned = (one << 8);  //Process MSB  (Bitshift algorithm)
   readval_unsigned = readval_unsigned + two;  //Process LSB

   //readval_unsigned = (((uint32_t) one << 8) + ((uint32_t) two));  //Alternate Bitshift algorithm)
   return readval_unsigned;
    }



uint32_t ADE7953::spiAlgorithm24_read(byte MSB, byte LSB) { //This is the algorithm that reads from a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm24_read function started ");
  #endif
  //long readval_signed=0;
  uint32_t readval_unsigned = 0;  //This variable is the unsigned integer value to compile read bytes into (if needed)
  byte one;
  byte two;
  byte three;
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Read in values sequentially and bitshift for a 32 bit entry
  SPI.transfer(READ); //Send command to begin readout
  one= SPI.transfer(WRITE); //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two= SPI.transfer(WRITE);   // (Read in data on dummy write (null MOSI signal))
  three= SPI.transfer(WRITE); //LSB Byte 3  (Read in data on dummy write (null MOSI signal))
  SPI.endTransaction();
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

 #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm24_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Returned bytes (1(MSB) to 3)[HEX]: ");
   Serial.print(one, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.print(" ");
   Serial.print(three, HEX);
   Serial.print(" ADE7953::spiAlgorithm24_read function completed ");
  #endif

  //Post-read packing and bitshifting operation
  readval_unsigned = (((uint32_t) one << 16)+ ((uint32_t) two << 8) + ((uint32_t) three)); //Shift algorithm

 //(Alternative Bitshift algorithm)
 // readval_unsigned =  ((one << 16) & 0x00FF0000);  //process MSB  //(Alternative shift algorithm)
 // readval_unsigned = readval_unsigned + ((two << 8) & 0X0000FF00);
 // readval_unsigned = readval_unsigned + (three & 0X000000FF);  //Process LSB

			return readval_unsigned;
  }


uint32_t ADE7953::spiAlgorithm32_read(byte MSB, byte LSB) { //This is the algorithm that reads from a 32 bit register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.  Caution, some register elements contain information that is only 24 bit with padding on the MSB
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm32_read function started ");
  #endif
  uint32_t readval_unsigned = 0;  //This variable is the unsigned integer value to compile read bytes into (if needed)
  byte one;
  byte two;
  byte three;
  byte four;
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Read in values sequentially and bitshift for a 32 bit entry
  SPI.transfer(READ); //Send command to begin readout
  one= SPI.transfer(WRITE); //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
  two= SPI.transfer(WRITE);   // (Read in data on dummy write (null MOSI signal))
  three= SPI.transfer(WRITE);   // (Read in data on dummy write (null MOSI signal))
  four= SPI.transfer(WRITE); //LSB Byte 4  (Read in data on dummy write (null MOSI signal))
  SPI.endTransaction();
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm32_read function details: ");
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
   Serial.print(" ADE7953::spiAlgorithm32_read function completed ");
  #endif

  //Post-read packing and bitshifting operations
  readval_unsigned = (((uint32_t) one << 24)+ ((uint32_t) two << 16) + ((uint32_t) three << 8) + (uint32_t) four);

  //Alternate Bitshifting approach
/*   readval_unsigned = (one << 24);  //Process MSB
  //Serial.println(readval_unsigned, HEX);
  readval_unsigned = readval_unsigned + (two << 16);
  //Serial.println(readval_unsigned, HEX);
  readval_unsigned = readval_unsigned + (three << 8);
  //Serial.println(readval_unsigned, HEX);
  readval_unsigned = (readval_unsigned + (four));  //Process LSB
  Serial.println(readval_unsigned, BIN);  */

  return readval_unsigned;
}


void ADE7953::spiAlgorithm32_write(byte MSB, byte LSB, byte onemsb, byte two, byte three, byte fourlsb) { //This is the algorithm that writes to a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print(" spiAlgorithm32_write function started ");
  #endif
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Send the Write command
  SPI.transfer(WRITE);
  SPI.transfer(onemsb);
  SPI.transfer(two);
  SPI.transfer(three);
  SPI.transfer(fourlsb);
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH

  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm32_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Written bytes (1(MSB) to 4)[HEX]: "); //MSB to LSB order
   Serial.print(onemsb, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.print(" ");
   Serial.print(three, HEX);
   Serial.print(" ");
   Serial.print(fourlsb, HEX);
   Serial.print(" spiAlgorithm32_write function completed ");
  #endif
  }


  void ADE7953::spiAlgorithm24_write(byte MSB, byte LSB, byte onemsb, byte two, byte threelsb) { //This is the algorithm that writes to a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print(" spiAlgorithm24_write function started ");
  #endif
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Send the Write command
  SPI.transfer(WRITE);
  SPI.transfer(onemsb);
  SPI.transfer(two);
  SPI.transfer(threelsb);
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm24_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Written bytes (1(MSB) to 3)[HEX]: ");  //MSB to LSB order
   Serial.print(onemsb, HEX);
   Serial.print(" ");
   Serial.print(two, HEX);
   Serial.print(" ");
   Serial.print(threelsb, HEX);
   Serial.print(" spiAlgorithm24_write function completed ");
  #endif
  }


void ADE7953::spiAlgorithm16_write(byte MSB, byte LSB, byte onemsb, byte twolsb) { //This is the algorithm that writes to a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print(" spiAlgorithm16_write function started ");
  #endif
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Send the Write command
  SPI.transfer(WRITE);
  SPI.transfer(onemsb);
  SPI.transfer(twolsb);
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm16_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Written bytes (1(MSB) to 2)[HEX]: ");  //MSB to LSB order
   Serial.print(onemsb, HEX);
   Serial.print(" ");
   Serial.print(twolsb, HEX);
   Serial.print(" spiAlgorithm16_write function completed ");
  #endif
  }


void ADE7953::spiAlgorithm8_write(byte MSB, byte LSB, byte onemsb) { //This is the algorithm that writes to a register in the ADE7953. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print(" spiAlgorithm8_write function started ");
  #endif
  digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
  SPI.beginTransaction(SPISettings(_SPI_freq, MSBFIRST, SPI_MODE3));  //Begin SPI transfer with most significant byte (MSB) first. Clock is high when inactive. Read at rising edge: SPIMODE3.
  SPI.transfer(MSB);  //Pass in MSB of register to be read first.
  SPI.transfer(LSB);  //Pass in LSB of register to be read next.
  //Send the Write command
  SPI.transfer(WRITE);
  SPI.transfer(onemsb);
  digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::spiAlgorithm8_read function details: ");
   Serial.print("Address Byte 1(MSB)[HEX]: ");
   Serial.print(MSB, HEX);
   Serial.print(" Address Byte 2(LSB)[HEX]: ");
   Serial.print(LSB, HEX);
   Serial.print(" Written bytes (1 of 1)[HEX]: ");  //MSB to LSB order
   Serial.print(onemsb, HEX);
   Serial.print(" spiAlgorithm16_write function completed ");
  #endif
  }


float ADE7953::decimalize(long input, float factor, float offset) //This function adds a decimal point to the input value and returns it as a float, it also provides linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
  #ifdef ADE7953_VERBOSE_DEBUG
   Serial.print("ADE7953::calibration and float type conversion function executed ");
  #endif
return ((float)input/factor)+offset;
}
