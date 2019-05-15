//*******************************************************************************************
//****************ADE 9078 REGISTERS *****************************************************
#define PFA_16 0x10A //PFA, (R/W) Reset:0x0000,

#define AIGAIN_32 0X000 // Reset: 0x00000000 Access: R/W Description: Phase A current gain adjust

#define AIGAIN0_32 0x001 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define AIGAIN1_32 0x002 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define AIGAIN2_32 0x003 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define AIGAIN3_32 0x004 /* Reset: 0x00000000 Access: R/W Description:  Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define AIGAIN4_32 0x005 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint gain correction factor. If multipoint gain and phase compenstation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN4, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */

#define APHCAL0_32 0x006 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define APHCAL1_32 0x007 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define APHCAL2_32 0x008 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define APHCAL3_32 0x009 /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define APHCAL4_32 0x00A /* Reset: 0x00000000 Access: R/W Description: Phase A multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in CONFIG0 register, the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

#define AVGAIN_32 0x00B // Reset: 0x00000000 Access: R/W Description: Phase A voltage gain adjust
#define AIRMSOS_32 0X00C // Reset: 0x00000000 Access: R/W Description: Phase A voltage rms offset for filter based AIRMS calculation
#define AVRMSOS_32 0X00D // Reset: 0x00000000 Access: R/W Description: Phase A current RMS offset for filter based AIRMS calucation
#define APGAIN_32 0X00E // Reset: 0x00000000 Access: R/W Description: Phase A power gain adjust for AWATT, AVA, avar, and AFVAR calculation
#define AWATTOS_32 0X00F // Reset: 0x00000000 Access: R/W Description: Phase A total active power offset correction for AWATT calculation.
#define AVAROS_32 0X010 // Reset: 0x00000000 Access: R/W Description: Phase A total active power offset correction for AVAR calculation.
#define AFVAROS_32 0x012 // Reset: 0x00000000 Access: R/W Description: Phase A fundamental reactive power offset correction for AFVAR calculation

#define BIGAIN_32 0x020 // Reset: 0x00000000 Access: R/W Description: Phrase B current gain adjust
#define BIGAIN0_32 0x021 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BIGAIN1_32 0x022 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BIGAIN2_32 0x023 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BIGAIN3_32 0x024 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BIGAIN4_32 0x025 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint gain correction factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN4, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

#define BPHCAL0_32 0x026 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BPHCAL1_32 0x027 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BPHCAL2_32 0x028 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BPHCAL3_32 0x029 /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/
#define BPHCAL4_32 0x02A /* Reset: 0x00000000 Access: R/W Description: Phase B multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the BPHCAL0 through BPHCAL4 value is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.*/

#define BVGAIN_32 0x02B // Reset: 0x00000000 Access: R/W Description: Phase B voltage gai nadjust
#define BIRMSOS_32 0x02C // Reset: 0x00000000 Access: R/W Description: Phase B current RMS offset for BIRMS calculation
#define BVRMSOS_32 0x02D // Reset: 0x00000000 Access: R/W Description: Phase B voltage RMS offset for BVRMS calculation
#define BPGAIN_32 0X02E // Reset: 0x00000000 Access: R/W Description: Phase B power gain adjust for BWATT, BVA, BVAR, and BFVAR calculations
#define BWATTOS_32 0X02F // Reset: 0x00000000 Access: R/W Description: Phase B total active power offset correction for BWATT calculation
#define BVAROS_32 0x030 // Reset: 0x00000000 Access: R/W Description: Phase B total active offset correction for BVAR calculation
#define BFVAROS_32 0x032 // Reset: 0x00000000 Access: R/W Description: Phase B fundamental reactive power offset correction for BFVAR calculation

#define CIGAIN_32 0x040 // Reset: 0x00000000 Access: R/W Description: Phase C current gain nadjust

// Phase C multipoint gain correction factor
#define CIGAIN0_32 0x041 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define CIGAIN1_32 0x042 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define CIGAIN2_32 0x043 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define CIGAIN3_32 0x044 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */
#define CIGAIN4_32 0x045 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint gain correctin factor. If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN4, is applied based on the CIRMS current rms amplitude and MTTHR_Lx and MTTHR_Hx register values. */

#define CPHCAL0_32 0X046 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define CPHCAL1_32 0X047 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define CPHCAL2_32 0X048 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define CPHCAL3_32 0X049 /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */
#define CPHCAL4_32 0X04A /* Reset: 0x00000000 Access: R/W Description: Phase C multipoint phase correction factor. If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTHR_Lx and MTTHR_Hx register values. */

#define CVGAIN_32 0x04B // Reset: 0x00000000 Access: R/W Description: Phase C voltage gain adjust
#define CIRMSOS_32 0x04C // Reset: 0x00000000 Access: R/W Description: Phase C current RMS offset for CIRMS calculation
#define CVRMSOS_32 0x04D // Reset: 0x00000000 Access: R/W Description: Phase C voltage RMS offset for CVRMS calcuation
#define CPGAIN_32 0x04E // Reset: 0x00000000 Access: R/W Description: Phase C power gain adjust for CWATT, CVA, CVAR, and CFVAR calculations
#define CWATTOS_32 0x04F // Reset: 0x00000000 Access: R/W Description: Phase C total active power offset correction for CWATT calculations
#define CVAROS_32 0x050 // Reset: 0x00000000 Access: R/W Description: Phase C total reactive power offset correction for CVAR calculation
#define CFVAROS_32 0x052 // Reset: 0x00000000 Access: R/W Description: Phase C total reactive power offset correction for CVAR calculations

#define CONFIG0_32 0x060
// Bits: [31:14] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 13 BitName: DISRPLPF Reset: 0x0 Access: R/W Description: Set this bit to disable the low-pass filter in the total reactive power datapath.
// Bits: 12 BitName: DISAPLPF Reset: 0x0 Access: R/W Description: Set this bit to disable the low-pass filter in the total active power datapath.
// Bits: 11 BitName: ININTEN Reset: 0x0 Access: R/W Description: Set this bit to enable the digital integrator in the Neutral Current channel.
// Bits: 10 BitName: VNOMC_EN Reset: 0x0 Access: R/W Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase C total apparent power, CVA.
// Bits: 9 BitName: VNOMB_EN Reset: 0x0 Access: R/W Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase B total apparent power, BVA.
// Bits: 8 BitName: VNOMA_EN Reset: 0x0 Access: R/W Description: Set this bit to use the nominal phase voltage rms, VNOM, in the computation of Phase A total apparent power, AVA.
// Bits: 7 BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 6 BitName: ZX_SRC_SEL Reset: 0x0 Access: R/W Description: This bit selects whether data going into the zero-crossing detection circuit comes before the highpass filter, integrator, and phase compensation or afterwards. Setting: 0 for After the high-pass filter, integrator, and phase compensation. Setting: 1 for Before the high-pass filter, integrator, and phase compensation.
// Bits: 5 BitName: INTEN Reset: 0x0 Access: R/W Description: Set this bit to enable the integrators in the phase current channels. The neutral current channel integrator is managed byb the ININTEN bit in the CONFIG0 register.
// Bits: 4 BitName: MTEN Reset: 0x0 Access: R/W Description: Set this bit to enable multipoint phase and gain compensation. If enabled, an additional gain factor, xIGAIN0 through xIGAIN4, is applied to the current channel based on the xIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values.
// Bits: 3 BitName: HPFDIS Reset: 0x0 Access: R/W Description: Set this bit to disable high-pass filters in all the voltage and current channels.
// Bits: 2 BitName: Reset: 0x0 Access: R RESERVED Description: Reserved
// Bits: [1:0] BitName: ISUM_CFG Reset: 0x0 Access: R/W Description: ISUM Calculation configuration. Setting: 00 for ISUM = AI_PCF + BI_PCF + CI_PCF (for approximated neutral current rms calculation) Setting: 01 for ISUM = AI_PCF + BI_PCF + CI_PCF+ NI_PCF(to determine mismatch between neutral and phase currents). Setting: 10 for ISUM = AI_PCF + BI_PCF + CI_PCF - NI_PCF(to determine mismatch between neutral and phase currents). Setting: 11 for ISUM = AI_PCF + BI_PCF + CI_PCF (for approximated neutral current rms calculation).

// Multipoint phase/gain threshold.
#define MTTHR_L0_32 0x061 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_L1_32 0x062 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_L2_32 0x063 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_L3_32 0x064 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_L4_32 0x065 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/

#define MTTHR_H0_32 0x066 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_H1_32 0x067 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_H2_32 0x068 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_H3_32 0x069 /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/
#define MTTHR_H4_32 0x06A /* Reset: 0x00000000 Access: R/W Description: Multipoint phase/gain threshold--see MTTHR_L0 for more information.*/

#define NIRMSOS_32 0x06B // Reset: 0x00000000 Access: R/W Description: Neutral current RMS offset for NIRMS calculations
#define ISUMRMSOS_32 0x06C // Reset: 0x00000000 Access: R/W Description: Offset correction for ISUMRMS calculation based on the sume of IA + IB + IC +- IN.
#define NIGAIN_32 0X06D // Reset: 0x00000000 Access: R/W Description: Neutral current again adjust
#define NPHCAL_32 0x06E // Reset: 0x00000000 Access: R/W Description: Neutral current-phase compensation
#define VNOM_32 0x071 // Reset: 0x00000000 Access: R/W Description: Nominal phase voltage RMS used in the computation of apparent power, xVA, when VNOMx_EN bit is set in the CONFIG0 register
#define DICOEFF_32 0x072 // Reset: 0x00000000 Access: R/W Description: Value used in the digital integrator algorithm
#define ISUMLVL_32 0x073 // Reset: 0x00000000 Access: R/W Description: Threshold to compare ISUMRMS against

// Access changes to read only here

#define AI_PCF_32 0x20A // Reset: 0x00000000 Access: Read only Description: Instantaneous Phase A current channel waveform processed by the DSP, at 4 kSPS.
#define AV_PCF_32 0x20B // Reset: 0x00000000 Access: Read only Description: Instantaneous Phase A voltage channel waveform processed by the DSP, at 4 kSPS.
#define AIRMS_32 0x20C // Reset: 0x00000000 Access: Read only Description: Phase A filter based current RMS value, updates at 4kSPS
#define AVRMS_32 0x20D // Reset: 0x00000000 Access: Read only Description: Phase A filter based voltage RMS value, updates at 4kSPS

#define AWATT_32 0x210 // Reset: 0x00000000 Access: Read only Description: Phase A low-pass filtere total active power, updated at 4 4kSPS
#define AVAR_32 0x211 // Reset: 0x00000000 Access: Read only Description: Phase A low pass filtered total reactive power, updated at 4kSPS
#define AVA_32 0x212 // Reset: 0x00000000 Access: Read only Description: Phase A total apparent power, updated at 4kSPS
#define AFVAR_32 0x214 // Reset: 0x00000000 Access: Read only Description: Phase A fundamental reactive power, updated at 4kSPS
#define APF_32 0x216 // Reset: 0x00000000 Access: Read only Description: Phase A power factor, updated at 1.024 second

#define AMTREGION_32 0x21D // Reset: 0x00000000 Access: Read only Description: If multipoint gain and phase compensaion is enabled, with MTEN = 1 in the CONFIG0 register,these bits indicate which AIGAINXx and APHCALx is currently being used

// [31:4] : RESERVED Reset: 0x0 Access: R
// [3:0] : AREGION Reset: 0xF Access: R
// If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which AIGAINx and APHCALx currently being used.
// 0000 AIGAIN0, APHCAL0.
// 0001 AIGAIN1, APHCAL1.
// 0010 AIGAIN2, APHCAL2.
// 0011 AIGAIN3, APHCAL3.
// 0100 AIGAIN4, APHCAL4.
// 1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.



#define BI_PCF_32 0x22A // Reset: 0x00000000 Access: Read only Description: Instantaneous Phase B current channel waveform processed by the DSP, 4kSPS
#define BV_PCF_32 0x22B //Reset: 0x00000000 Access: Read only Description:  Instantaneous Phase B votage channel waveform processed by the DSP, 4kSPS
#define BIRMS_32 0x22C // Reset: 0x00000000 Access: Read only Description: Phase B filter based current RMS value, updates at 4kSPS
#define BVRMS_32 0x22D // Reset: 0x00000000 Access: Read only Description: Phase B filter based voltage RMS value, updates at 4kSPS
#define BWATT_32 0x230 // Reset: 0x00000000 Access: Read only Description: Phase B low-pass filtered total active power, updated at 4kSPS
#define BVAR_32 0x231 //Reset: 0x00000000 Access: Read only Description:  Phase B low pass filtered total reactive power, updated at 4kSPS.
#define BVA_32 0x232 // Reset: 0x00000000 Access: Read only Description: Phase B total apparent power, updated at 4kSPS
#define BFVAR_32 0x234 // Reset: 0x00000000 Access: Read only Description: Phase B fundamental reactive power, updated at 4kSPS
#define BPF_32 0x236 // Reset: 0x00000000 Access: Read only Description: Phase B power factor, updated at 1.024 sec.

#define BMTREGION_32 0x23D // Reset: 0x00000000 Access: Read only Description: If multipoint gain and phase.....
/*
[31:4] : RESERVED Reset: 0x0 Access: R
[3:0] : BREGION Reset: 0xF Access: R
If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which BIGAINx and BPHCALx currently being used.
0000 BIGAIN0, BPHCAL0.
0001 BIGAIN1, BPHCAL1.
0010 BIGAIN2, BPHCAL2.
0011 BIGAIN3, BPHCAL3.
0100 BIGAIN4, BPHCAL4.
1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.
*/


#define CI_PCF_32 0x24A //Reset: 0x00000000 Access: Read only Description:  Instantaneous Phase C current channel waveform proccessed by the DSP, at 4kSPS
#define CV_PCF_32 0x24B // Reset: 0x00000000 Access: Read only Description: Instantaneous Phase C voltage channel waveform proccessed by the DSP, at 4kSPS
#define CIRMS_32 0X24C // Reset: 0x00000000 Access: Read only Description: Phase C filter based current RMS value, updates at 4kSPS
#define CVRMS_32 0x24D //Reset: 0x00000000 Access: Read only Description: Phase C filter based voltage RMS value, updates at 4kSPS
#define CWATT_32 0x250 // Reset: 0x00000000 Access: Read only Description: Phase C low-pass filtered total active power, updated at 4kSPS
#define CVAR_32 0x251  // Reset: 0x00000000 Access: Read only Description: Phase C low pass filtered total reactive power, updated at 4kSPS.
#define CVA_32 0x252 // Reset: 0x00000000 Access: Read only Description: Phase C total apparent power, updated at 4kSPS
#define CFVAR_32 0x254 // Reset: 0x00000000 Access: Read only Description: Phase C fundamental reactive power, udpated at 4kSPS
#define CPF_32 0x256 // Reset: 0x00000000 Access: Read only Description: Phase C power factor, updated at 1.024 seconds

#define CMTREGION_32 0X25D // If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which CIGAINx and CPHCALx is currently being used.
// Bits: [31:4] : RESERVED Reset: 0x0 Access: R
// Bits: [3:0] : CREGION Reset: 0xF Access: R - Description: If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which CIGAINx and CPHCALx currently being used.
// Settings
// 0000 CIGAIN0, CPHCAL0.
// 0001 CIGAIN1, CPHCAL1.
// 0010 CIGAIN2, CPHCAL2.
// 0011 CIGAIN3, CPHCAL3.
// 0100 CIGAIN4, CPHCAL4.
// 1111 This feature is disabled because MTEN = 0 in the CONFIG0 register.

#define NI_PCF_32 0x265 // Reset: 0x00000000 Access: Read only Description: Instantaneous neutral current channel waveform processed by the DSP, at 4kSPS.
#define NIRMS_32 0x266 // Reset: 0x00000000 Access: Read only Description: Neutral current filter based RMS value
#define ISUMRMS_32 0x269 // Reset: 0x00000000 Access: Read only Description: Filter based RMS based on the sum of IA + IB + IC += IN.
#define VERSION2_32 0x26A // Reset: 0x00000000 Access: Read only Description: Indicates the version of the metrology algorithms after the user writes run = 1 to start the measuremnets.

#define AWATT_ACC_32 0x2E5 // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total active power, updated after PWR_TIME 4 ksps samples
#define AWATTHR_LO_32 0x2E6 //Reset: 0x00000000 Access: Read only Description:  Phase A accumulated total active energy, LSB's. Updated according to settings in EP_CFG and EGY_TIME Registers
#define AWATTHR_HI_32 0x2E7 //Reset: 0x00000000 Access: Read only Description:  Phase A accumulated total active energy, MSB's....
#define AVAR_ACC_32 0x2EF  // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total reactive power, updated after PWR_TIME 4 kSPS samples.
#define AVARHR_LO_32 0X2F0 // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total reactive energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME Registers
#define AVARHR_HI_32 0x2F1 // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total reactive energy, MSB's...
#define AVA_ACC_32 0x2F9 // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total apparent power, updated after PWR_TIME 4 kSPS samples
#define AVAHR_LO_32 0x2FA // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total apparent energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define AVAHR_HI_32 0x2FB // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total apparent energy, MSB's.

#define AFVAR_ACC_32 0x30D // Reset: 0x00000000 Access: Read only Description: Phase A accumulated fundamental reactive power, updated after PWR_TIME 4kSPS samples
#define AFVARHR_LO_32 0x30E // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total apparent energy, LSB's. Updated according to the settings in EP_CFG and EGY_TIME Registers
#define AFVARHR_HI_32 0x30F // Reset: 0x00000000 Access: Read only Description: Phase A accumulated total apparent energy, MSB's...
#define BWATT_ACC_32 0x321 // Reset: 0x00000000 Access: Read only Description: Phase B accumulated total active power, updated after PWR_TIME 4 kSPS samples
#define BWATTHR_LO_32 0x322 //Reset: 0x00000000 Access: Read only Description:  Phase B accumulated total active energy, LSB's, updated according to the settings in EP_CFG and EGY_TIME registers.
#define BWATTHR_HI_32 0x323 //Reset: 0x00000000 Access: Read only Description:  Phase B accumulated total active energy, MSB's...
#define BVAR_ACC_32 0x32B  // Reset: 0x00000000 Access: Read only Description: Phase B accumulated total reactive power, updated after PWR_TIME 4 ksSPS samples.

#define BVARHR_LO_32 0x32C //Reset: 0x00000000 Access: Read only Description: Phase B accumulate total ractive energy,LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define BVARHR_HI_32 0x32D // Reset: 0x00000000 Access: Read only Description: Phase B accumulate total ractive energy,MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define BVA_ACC_32 0x335 //Reset: 0x00000000 Access: Read only Description: Phase B accumulated total apparent power, updated after PWR_TIME 4kSPS samples.
#define BVAHR_LO_32 0x336 //Reset: 0x00000000 Access: Read only Description: Phase B accumulatecd total apparent energy, LSbs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define BVAHR_HI_32 0x337 //Reset: 0x00000000 Access: Read only Description: Phase B accumulate total ractive energy,MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define BFVAR_ACC_32 0x349 //Reset: 0x00000000 Access: Read only Description: Phase B accumulated fundamental ractive power, updated after PWR_TIME 4 kSPS samples.
#define BFVARHR_LO_32 0x34A //Reset: 0x00000000 Access: Read only Description: Phase B accumulated fundamental reactive energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define BFVARHR_HI_32 0x34B //Reset: 0x00000000 Access: Read only Description: Phase B accumulated fundamental reactive energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define CWATT_ACC_32 0x35D // Reset: 0x00000000 Access: Read only Description: Phase C accumulated total active power, updated after PWR_TIME 4 kSPS samples
#define CWARRHR_LO_32 0x35E //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total active energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define CWATTHR_HI_32 0x35F //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total active energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define CVAR_ACC_32 0x367 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total reactive power, updated after PWR_TIME 4kSPS samples.
#define CVARHR_LO_32 0x368 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total ractive energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define CVARHR_HI_32 0x369 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total ractive energy, LSBs. UPdated according to the settings in EP_CFG and EGY_TIME registers.
#define CVA_ACC_32 0x371 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total apparent powerm updated after PWR_TIME 4 kSPS samples.
#define CVAHR_LO_32 0x372 //Reset: 0x00000000 Access: Read only Description: Phase C  accumulated total apparent energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define CVAHR_HI_32 0x373 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated total apparent energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define CFVAR_ACC_32 0x385 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated fundamental reactive power, updated after PWR_TIME 4 kSPS samples.
#define CFVARHR_LO_32 0x386 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated fundamental reactive energy, LSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define CFVVARHR_HI_32 0x387 //Reset: 0x00000000 Access: Read only Description: Phase C accumulated fundamental reactive energy, MSBs. Updated according to the settings in EP_CFG and EGY_TIME registers.
#define PWATT_ACC_32 0x397 //Reset: 0x00000000 Access: Read only Description: Accumulated Positive Total Active Power, MSBs, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 4 kSPS samples.
#define NWATT_ACC_32 0x39B //Reset: 0x00000000 Access: Read only Description: Accumulated Negative Total Active Power, MSBs, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 4 kSPS samples.
#define PVAR_ACC_32 0x39F //Reset: 0x00000000 Access: Read only Description: Accumulated Positive Total Reactive Power, MSBs, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 4 kSPS samples.
#define NVAR_ACC_32 0x3A3 //Reset: 0x00000000 Access: Read only Description: Accumulated Negative Total Reactive Power, MSBs, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 4 kSPS samples
#define IPEAK_32 0x400 //Reset: 0x00000000 Access: Read only Description: Current peak register.

// Bits: [31:27] RESERVED Reset: 0x0 Access: R
// Bits: [26:24]: IPPHASE Reset: 0x0 Access: R - These bits indicate which phases generate IPEAKVAL value. Note that the PEAKSEL[2:0] bits the CONFIG3 register determine which current channel to monitor the peak value on. When IPPHASE, Bit 0 is set to 1, Phase A current generated IPEAKVAL, Bits[23:0] value. Similarly, IPPHASE, Bit 1 indicates Phase B and IPPHASE, Bit 2 indicates Phase C current generated the peak value.
// Bits: [23:0]: IPEAKVAL Reset: 0x0 Access: R - The IPEAK register stores the absolute value of the peak current. IPEAK is equal to xI_PCF/25


#define VPEAK_32 0x401 //Reset: 0x00000000 Access: Read only Description:  Voltage peak register
// Bits: [31:27] Reserved Reset: 0x0 Access: R
// Bits: [26:24] VPPHASE Reset: 0x0 Access: R - These bits indicate which phases generate VPEAKVAL value. Note that the PEAKSEL[2:0] bits in the CONFIG3 register determine which voltage channels to monitor the peak value on. When VPPHASE[0] is 1, Phase A voltage generated VPEAKVAL[23:0] value. Similarly, VPPHASE[1] indicates Phase B and VPPHASE[2] indicates Phase C voltage generated the peak value.
// Bits: [23:0] VPEAKVAL Reset: 0x0 Access: R - The VPEAK register stores the absolute value of the peak voltage. VPEAK is equal to xV_PCF/25.

#define STATUS0_32 0x402 //Reset: 0x00000000 Access: Read only Description:  Status Register 0
// Bits: [31:25] RESERVED Reset: 0x0 Access: R
// Bits: 24 MISMTCH Reset: 0x0 Access: R/W1 - This bit is set to indicate a change in the relationship between ISUMRMS and ISUMLVL
// Bits: 23 COH_WFB_FULL Reset: 0x0 Access: R/W1 - This bit is set when the waveform buffer is full with resampled data, which is selected when WF_CAP_SEL = 0 in the WFB_CFG register.
// Bits: 22 WFB_TRIG Reset: 0x0 Access: R/W1 - This bit is set when one of the events configured in WFB_TRIG_CFG occurs
// Bits: 21 PF_RDY Reset: 0x0 Access: R/W1 - This bit goes high to indicate when the power factor measurements have been updated, every 1.024 seconds.
// Bits: [20:19] RESERVED Reset: 0x0 Access: R
// Bits: 18 PWRRDY Reset: 0x0 Access: R/W1 - This bit is set when the power values in the xWATT_ACC, xVA_ACC, xVAR_ACC, xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// Bits: 17 PAGE_FULL Reset: 0x0 Access: R/W1 - This bit is set when a page enabled in the WFB_PG_IRQEN register has been filled with fixed data rate samples, when WF_CAP_SEL bit in the WFB_CFG register = 0.
// Bits: 16 WFB_TRIG_IRQ Reset: 0x0 Access: R/W1 - This bit is set when the waveform buffer has stopped filling after an event configured in WFB_TRIG_CFG occurs. This happens with fixed data rate samples only, when WF_CAP_SEL bit in the WFB_CFG register = 0.
// Bits: 15 - DREAY Reset: 0x0 Access: R/W1 - This bit is set when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// Bits: 14 - CF4 Reset: 0x0 Access: R/W1 - This bit is set when a CF4 pulse is issued, when the CF4 pin goes from a high to low state.
// Bits: 13 - CF3 Reset: 0x0 Access: R/W1 - This bit is set when a CF3 pulse is issued, when the CF3 pin goes from a high to low state.
// Bits: 12 - CF2 Reset: 0x0 Access: R/W1 - This bit is set when a CF2 pulse is issued, when the CF2 pin goes from a high to low state.
// Bits: 11 - CF1 Reset: 0x0 Access: R/W1 - This bit is set when a CF1 pulse is issued, when the CF1 pin goes from a high to low state.
// Bits: 10 - REVPSUM4 Reset: 0x0 Access: R/W1 - This bit is set to indicate if the CF4 polarity changed sign. For example, if the last CF4 pulse was positive reactive energy and the next CF4 pulse is negative reactive energy, the REVPSUM4 bit is set. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low
// Bits: 9 - REVPSUM3 Reset: 0x0 Access: R/W1 - This bit is set to indicate if the CF3 polarity changed sign. See REVPSUM4.
// Bits: 8 - REVPSUM2 Reset: 0x0 Access: R/W1 - This bit is set to indicate if the CF2 polarity changed sign. See REVPSUM4.
// Bits: 7 - REVPSUM1 Reset: 0x0 Access: R/W1 - This bit is set to indicate if the CF1 polarity changed sign. See REVPSUM4.
// Bits: 6 - REVRPC Reset: 0x0 Access: R/W1 - This bit indicates if the Phase C total or fundamental reactive power has changed sign. The PWR_SIGN_SEL bit in the EP_CFG register selects whether total or fundamental reactive power is monitored. This bit is updated when the power values in the xVAR_ACC and xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// Bits: 5 - REVRPB Reset: 0x0 Access: R/W1 - This bit indicates if the Phase B total or fundamental reactive power has changed sign. See REVRPC.
// Bits: 4 - REVRPA Reset: 0x0 Access: R/W1 - This bit indicates if the Phase A total or fundamental reactive power has changed sign. See REVRPC.
// Bits: 3 - REVAPC Reset: 0x0 Access: R/W1 - This bit indicates if the Phase C total active power has changed sign. This bit is updated when the power values in the xWATT_ACC and xWATT_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// Bits: 2 - REVAPB Reset: 0x0 Access: R/W1 - This bit indicates if the Phase B total active power has changed sign. See REVAPC.
// Bits: 1 - REVAPA Reset: 0x0 Access: R/W1 - This bit indicates if the Phase A total active power has changed sign. See REVAPC.
// Bits: 0 - EGYRDY Reset: 0x0 Access: R/W1 - This bit is set when the power values in the xWATTHR, xVAHR, xVARHR, xFVARHR registers have been updated, after EGY_TIME 4 kSPS samples or line cycles, depending on the EGY_TMR_MODE bit in the EP_CFG register.

#define STATUS1_32 0x403 //Reset: 0x00000000 Access: Read only Description:  Status Register 1.

// Bits: 31- ERROR3 Reset: 0x0 Access: R/W1 - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
// Bits: 30 - ERROR2 Reset: 0x0 Access: R/W1 - This bit indicates that an error was detected and corrected. No action is required.
// Bits: 29 - ERROR1 Reset: 0x0 Access: R - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
// Bits: 28 - ERROR0 Reset: 0x0 Access: R - This bit indicates an error and generates a non- maskable interrupt. Issue a software or hardware reset to clear this error.
// Bits: 27 - CRC_DONE Reset: 0x0 Access: R/W1 - This bit is set to indicate when the configuration register CRC calculation is done, after initiated by writing the FORCE_CRC_UPDATE bit in the CRC_FORCE register.
// Bits: 26 - CRC_CHG Reset: 0x0 Access: R/W1 - This bit is set if any of the registers monitored by the configuration register CRC change value. The CRC_RSLT register holds the new configuration register CRC value.
// Bits: [25:19] - RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 18 - SEQERR Reset: 0x0 Access: R/W1 - This bit is set to indicate a phase sequence error on the Phase Voltage zero crossings.
// Bits: 17 - RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 16 - RSTDONE Reset: 0x0 Access: R/W1 - This bit is set to indicate that the IC has finished its power-up sequence after a reset or after changing between PSM2 or PSM3 operating mode to PSM0 or PSM1. This indicates that the user can configure the IC via the SPI port.
// Bits: 15 - ZXIC Reset: 0x0 Access: R/W1 - When this bit is set to 1, it indicates a zero crossing has been detected on Phase C current.
// Bits: 14 - ZXIB Reset: 0x0 Access: R/W1 - When this bit is set to 1, it indicates a zero crossing has been detected on Phase B current.
// Bits: 13 - ZXIA Reset: 0x0 Access: R/W1 - When this bit is set to 1, it indicates a zero crossing has been detected on Phase A current.
// Bits: 12 - ZXCOMB Reset: 0x0 Access: R/W1 - When this bit is set, it indicates a zero crossing has been detected on the combined signal from VA, VB, and VC.
// Bits: 11 - ZXVC Reset: 0x0 Access: R/W1 - When this bit is set, it indicates a zero crossing has been detected on the Phase C voltage channel.
// Bits: 10 - ZXVB Reset: 0x0 Access: R/W1 - When this bit is set, it indicates a zero crossing has been detected on the Phase B voltage channel.
// Bits: 9 - ZXVA Reset: 0x0 Access: R/W1 - When this bit is set, it indicates a zero crossing has been detected on the Phase A voltage channel.
// Bits: 8 - ZXTOVC Reset: 0x0 Access: R/W1 - This bit is set to indicate a zero crossing timeout on Phase C. This means that a zero crossing on the Phase C voltage is missing.
// Bits: 7 - ZXTOVB Reset: 0x0 Access: R/W1 - This bit is set to indicate a zero crossing timeout on Phase B. This means that a zero crossing on the Phase B voltage is missing.
// Bits: 6 - ZXTOVA Reset: 0x0 Access: R/W1 - This bit is set to indicate a zero crossing timeout on Phase A. This means that a zero crossing on the Phase A voltage is missing.
// Bits: 5 - RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 4 - RFNOLOAD Reset: 0x0 Access: R/W1 - This bit is set when one or more phase fundamental reactive energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
// Bits: 3 - RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 2 - VANLOAD Reset: 0x0 Access: R/W1 - This bit is set when one or more phase total apparent energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
// Bits: 1 - RNLOAD Reset: 0x0 Access: R/W1 - This bit is set when one or more phase total reactive energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.
// Bits: 0 - ANLOAD Reset: 0x0 Access: R/W1 - This bit is set when one or more phase total active energy enters or exits the no load condition. The phase is indicated in the PHNOLOAD register.

#define EVENT_STATUS32 0x404 //Reset: 0x00000000 Access: Read only Description:  Event Status Register.
// Bits: [31:17] - RESERVED Reset: 0x0 Access: R - Reserved
// Bits: 16 - DREADY Reset: 0x0 Access: R - This bit changes from a one to a zero when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// Bits: 15 - RESERED Reset: 0x0 Access: R - Reserved
// Bits: 14 RFNOLOAD Reset: 0x0 Access: R - This bit is set when the fundamental reactive energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of fundamental reactive energy accumulation goes into no load.
// Bits: 13-  RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 12 - VANLOAD Reset: 0x0 Access: R - This bit is set when the total apparent energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total apparent energy accumulation goes into no load.
// Bits: 11 - RNLOAD Reset: 0x0 Access: R - This bit is set when the total reactive energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total reactive energy accumulation goes into no load.
// Bits: 10 - ANLOAD Reset: 0x0 Access: R - This bit is set when the total active energy accumulations in all phases are out of no load. This bit goes to zero when one or more phases of total active energy accumulation goes into no load.
// Bits: 9 - REVPSUM4 Reset: 0x0 Access: R - This bit indicates the sign of the last CF4 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low.
// Bits: 8 - REVPSUM3 Reset: 0x0 Access: R - This bit indicates the sign of the last CF3 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF3 pulse is output, when the CF3 pin goes from high to low.
// Bits: 7 - REVPSUM2 Reset: 0x0 Access: R - This bit indicates the sign of the last CF2 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF2 pulse is output, when the CF2 pin goes from high to low.
// Bits: 6 - REVPSUM1 Reset: 0x0 Access: R - This bit indicates the sign of the last CF1 pulse. A zero indicates that the pulse was from negative energy and a one indicates that the energy was positive. This bit is updated when a CF1 pulse is output, when the CF1 pin goes from high to low.
// Bits: 5[:0] - Reserved Reset: 0x0 Access: R - Reserved


#define MASK0_32 0x405 //Reset: 0x00000000 Access: Read only Description:  Interrupt Enable Register 0.
// Bits: [31:25] RESERVED Reset: 0x0 Access: R - Reserved
// Bits: 24 - MISMTCH Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when there is a change in the relationship between ISUMRMS and ISUMLVL.
// Bits: 23 - COH_WFB_FULL Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the waveform buffer is full with resampled data, which is selected when WF_CAP_SEL = 0 in the WFB_CFG register.
// Bits: 22 - WFB_TRIG Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when one of the events configured in WFB_TRIG_CFG occurs.
// Bits: 21 - PF_RDY Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the power factor measurements have been updated, every 1.024 seconds
// Bits: [20:19] - RESERVED Reset: 0x0 Access: R - Reserved.
// Bits: 18 - PWRRDY Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the power values in the xWATT_ACC, xVA_ACC, xVAR_ACC, xFVAR_ACC registers have been updated, after PWR_TIME 4 kSPS samples.
// Bits: 17 - PAGE_FULL Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when a page enabled in the WFB_PG_IRQEN register has been filled.
// Bits: 16 - WFB_TRIG_IRQ Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when This bit is set when the waveform buffer has stopped filling after an event configured in WFB_TRIG_CFG occurs.
// Bits: 15 - DREADY Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// Bits: 14 - CF4 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF4 pulse is issued, when the CF4 pin goes from a high to low state.
// Bits: 13 - CF3 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF3 pulse is issued, when the CF3 pin goes from a high to low state.
// Bits: 12 - CF2 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF2 pulse is issued, when the CF2 pin goes from a high to low state.
// Bits: 11 - CF1 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF1 pulse is issued, when the CF1 pin goes from a high to low state.
// Bits: 10 - REVPSUM4 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF4 polarity changed sign.
// Bits: 9 - REVPSUM3 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF3 polarity changed sign.
// Bits: 8 - REVPSUM2 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF2 polarity changed sign.
// Bits: 7 - REVPSUM1 Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the CF1 polarity changed sign.
// Bits: 6 - REVRPC Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase C total or fundamental reactive power has changed sign.
// Bits: 5 - REVRPB Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase C total or fundamental reactive power has changed sign.
// Bits: 4- REVRPA Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase A total or fundamental reactive power has changed sign.
// Bits: 3 - REVAPC Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase C total active power has changed sign.
// Bits: 2 - REVAPB Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase B total active power has changed sign.
// Bits: 1 - REVAPA Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the Phase A total active power has changed sign.
// Bits: 0 - EGYRDY Reset: 0x0 Access: R/W - Set this bit to enable an interrupt when the power values in the xWATTHR, xVAHR, xVARHR, and xFVARHR registers have been updated, after EGY_TIME 4 kSPS samples or line cycles, depending on the EGY_TMR_MODE bit in the EP_CFG register.


#define MASK1_32 0x406 //Reset: 0x00000000 Access: Read only Description:  Interrupt Enable Register 1.
// Bits: 31 - ERROR3 - Reset: 0x0 Access: R/W Description: Set this bit to enable an interrupt if ERROR3 occurs. Issue a software reset or hardware reset to clear this error.
// Bits: 30 - ERROR2 - Reset: 0x0 Access: R/W Description: Set this bit to enable an interrupt if ERROR2 occurs.
// Bits: 29 - ERROR1 - Reset: 0x0 Access: R/W Description: This interrupt is not maskable. Issue a software reset or hardware reset to clear this error.
// Bits: 28 - ERROR0 - Reset: 0x0 Access: R/W Description: This interrupt is not maskable. Issue a software reset or hardware reset to clear this error.
// Bits: 27 - Reset: 0x0 Access: R/W Description: CRC_DONE - Set this bit to enable an interrupt when the configuration register CRC calculation is done, after initiated by writing the FORCE_CRC_UPDATE bit in the CRC_FORCE register.
// Bits: 26 - Reset: 0x0 Access: R/W Description: CRC_CHG - Set this bit to enable an interrupt if any of the registers monitored by the configuration register CRC change value. The CRC_RSLT register holds the new configuration register CRC value.
// Bits: [25:19] - RESERVED Reset: 0x0 Access: Read only Description: Reserved.
// Bits: 18 - SEQERR - Reset: 0x0 Access: R/W Description: Set this bit to set an interrupt when on a phase sequence error on the phase voltage zero crossings.
// Bits: [17:16] - RESERVED Reset: 0x0 Access: Read only Description: Reserved.
// Bits: 15 - ZXIC - Reset: 0x0 Access: R/W Description: Set this bit to set an interrupt when a zero crossing has been detected on the Phase C current channel.
// Bits: 14 - ZXIB - Reset: 0x0 Access: R/W Description: Set this bit to set an interrupt when a zero crossing has been detected on the Phase B current channel.
// Bits: 13 - ZXIA - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when a zero crossing has been detected on the Phase A current channel.
// Bits: 12 - ZXCOMB - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when a zero crossing has been detected on the combined signal from VA, VB, and VC.
// Bits: 11 - ZXVC - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when a zero crossing has been detected on the Phase C voltage channel.
// Bits: 10 - ZXVB - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when a zero crossing has been detected on the Phase B voltage channel.
// Bits: 9 - ZXVA - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when a zero crossing has been detected on the Phase A voltage channel.
// Bits: 8 - ZXTOVC - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when there is a zero crossing timeout on Phase C. This means that a zero crossing on the Phase C voltage is missing.
// Bits: 7 - ZXTOVB - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when there is a zero crossing timeout on Phase B. This means that a zero crossing on the Phase B voltage is missing
// Bits: 6 - ZXTOVA - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when there is a zero crossing timeout on Phase A. This means that a zero crossing on the Phase A voltage is missing.
// Bits: 5 - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.
// Bits: 4 - RFNOLOAD - Reset: 0x0 Access: R/W Description:  Set this bit to set an interrupt when one or more phase total reactive energy enters or exits the no load condition.
// Bits: 3 - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.
// Bits: 2 - Reset: 0x0 Access: R/W Description:  VANLOAD - Set this bit to set an interrupt when one or more phase total apparent energy enters or exits the no load condition.
// Bits: 1 - Reset: 0x0 Access: R/W Description:  RNLOAD - Set this bit to set an interrupt when one or more phase total reactive energy enters or exits the no load condition.
// Bits: 0 - Reset: 0x0 Access: R/W Description:  ANLOAD - Set this bit to set an interrupt when one or more phase total active energy enters or exits the no load condition.

#define EVENT_MASK_32 0x407 //Reset: 0x00000000 Access: Read only Description: Event enable register.
// [31:17] - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.
// Bits: 16 - DREADY - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low when new waveform samples are ready. The update rate depends on the data selected in the WF_SRC bits in the WFB_CFG register.
// Bits: 15 - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.
// Bits: 14 - RFNOLOAD - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low when one or more phases of fundamental reactive energy accumulation goes into no load.
// Bits: 13 - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.
// Bits: 12 - VANLOAD - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low when one or more phases of total apparent energy accumulation goes into no load.
// Bits: 11 - RNLOAD - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low when one or more phases of total reactive energy accumulation goes into no load.
// Bits: 10 - ANLOAD - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low when one or more phases of total active energy accumulation goes into no load.
// Bits: 9 - REVPSUM4 - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low to indicate if the last CF4 pulse was from negative energy. This bit is updated when a CF4 pulse is output, when the CF4 pin goes from high to low.
// Bits: 8 - REVPSUM3 - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low to indicate if the last CF3 pulse was from negative energy. This bit is updated when a CF3 pulse is output, when the CF3 pin goes from high to low.
// Bits: 7 - REVPSUM2 - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low to indicate if the last CF2 pulse was from negative energy. This bit is updated when a CF2 pulse is output, when the CF2 pin goes from high to low.
// Bits: 6 - REVPSUM1 - Reset: 0x0 Access: R/W Description:  Set this bit to enable the EVENT pin to go low to indicate if the last CF1 pulse was from negative energy. This bit is updated when a CF1 pulse is output, when the CF1 pin goes from high to low.
// Bits: [5:0] - RESERVED - Reset: 0x0 Access: Read only Description:  Reserved.

#define USER_PERIOD_32 0x40E //Reset: 0x00500000 Access: R/W Description: User configured line period value used for resampling when the UPERIOD_SEL bit in the CONFIG2 register is set.

#define VLEVEL_32 0x40F //Reset: 0x00045D45 Access: R/W Description: Register used in the algorithm that computes the fundamental reactive power
// Bits: [31:24] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: [23:0] BitName: VLEVEL_VAL - Reset: 0x45D45 Access: R/W Description: Register used in the algorithm that computes the fundamental reactive power.

#define APERIOD_32 0x418 //Reset: 0x00A00000 Access: Read only Description: Line period on Phase A voltage
#define BPERIOD_32 0x419 //Reset: 0x00A00000 Access: Read only Description: Line period on Phase B voltage
#define CPERIOD_32 0x41A //Reset: 0x00A00000 Access: Read only Description: Line period on Phase C voltage
#define COM_PERIOD_32 0x41B //Reset: 0x00A00000 Access: Read only Description: Line period measurement on combined signal from Phase A, Phase B, and Phase C voltages
#define ACT_NL_LVL_32 0x41C //Reset: 0x0000FFFF Access: R/W Description: No load threshold in the total active power datapath
#define REACT_NL_LVL_32 0x41D //Reset: 0x0000FFFF Access: R/W Description: No load threshold in the total and fundamental reactive power datapath.
#define APP_NL_LVL_32 0x41E //Reset: 0x0000FFFF Access: R/W Description: No load threshold in the total apparent power datapath.



#define PHNOLOAD_32 0x41F //Reset: 0x00000000 Access: Read only Description: Phase no load register.
// Bits: [31:17] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 16 BitName: CFVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase C fundamental reactive energy is in no load.
// Bits: 15 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 14 BitName: CVANL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase C total apparent energy is in no load.
// Bits: 13 BitName: CVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase C total reactive energy is in no load.
// Bits: 12 BitName: CWATTNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase C total active energy is in no load.
// Bits: 11 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 10 BitName: BFVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase B fundamental reactive energy is in no load.
// Bits: 9 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 8 BitName: BVANL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase B apparent energy is in no load.
// Bits: 7 BitName: BVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase B total reactive energy is in no load.
// Bits: 6 BitName: BWATTNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase B total active energy is in no load.
// Bits: 5 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 4 BitName: AFVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase A fundamental reactive energy is in no load.
// Bits: 3 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 2 BitName: AVANL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase A total apparent energy is in no load.
// Bits: 1 BitName: AVARNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase A total reactive energy is in no load.
// Bits: 0 BitName: AWATTNL - Reset: 0x0 Access: Read only Description: This bit is set if the Phase A total active energy is in no load.

#define WTHR_32 0x420 //Reset: 0x0000FFFF Access: R/W Description: Sets the maximum output rate from the digital to frequency converter for the total active power for the CF calibration pulse output. It is recommended to write WTHR = 0x0010 0000.
#define VARTHR_32 0x421 //Reset: 0x0000FFFF Access: R/W Description: Sets the maximum output rate from the digital to frequency converter for the total and fundamental reactive power for the CF calibration pulse output. It is recommended to write VARTHR = 0x0010 0000.
#define VATHR_32 0x422 //Reset: 0x0000FFFF Access: R/W Description: Sets the maximum output rate from the digital to frequency converter for the total apparent power for the CF calibration pulse output. It is recommended to write VATHR = 0x0010 0000.

#define LAST_DATA_32_32 0x423 //Reset: 0x00000000 Access: Read only Description: This register holds the data read or written during the last 32-bittransaction on the SPI port.

#define ADC_REDIRECT_32 0x424 //Reset: 0x001FFFFF Access: R/W Description: This register allows any ADC output to be redirected to any digital datapath.
// Bits: [31:21] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: [20:18] BitName: VC_DIN - Reset: 0x7 Access: R/W Description: Voltage C channel data can be selected from: Setting: 000 for IA ADC data. Setting: 001 for IB ADC data. Setting: 010 for IC ADC data. Setting: 011 for IN ADC data. Setting: 100 for VA ADC data. Setting: 101 for VB ADC data. Setting: 110 for VC ADC data. Setting: 111 for VC ADC data.
// Bits: [17:15] BitName: VB_DIN - Reset: 0x7 Access: R/W Description: VB channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for VB ADC data.
// Bits: [14:12] BitName: VA_DIN - Reset: 0x7 Access: R/W Description: VA channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for VA ADC data.
// Bits: [11:9] BitName: IN_DIN - Reset: 0x7 Access: R/W Description: IN channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IN ADC data.
// Bits: [8:6] BitName: IC_DIN - Reset: 0x7 Access: R/W Description: IC channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IC ADC data.
// Bits: [5:3] BitName: IB_DIN - Reset: 0x7 Access: R/W Description: IB channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IB ADC data.
// Bits: [2:0] BitName: IA_DIN - Reset: 0x7 Access: R/W Description: IA channel data can be selected from all channels. The bit descriptions for 000b through 110b match VC_DIN. When the value is equal to 111b then: Setting: 111 for IA ADC data.

#define CF_LCFG_32 0x425 //Reset: 0x00000000 Access: R/W Description: CF calibration pulse width configuration register.
// Bits: [31:23] BitName: RESERVED Description: Reserved
// Bits: 22 BitName: CF4_LT - Reset: 0x0 Access: R/W Description: If this bit is set, the CF4 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 21 BitName: CF3_LT - Reset: 0x0 Access: R/W Description: If this bit is set, the CF3 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 20 BitName: CF2_LT - Reset: 0x0 Access: R/W Description: If this bit is set, the CF2 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: 19 BitName: CF1_LT - Reset: 0x0 Access: R/W Description: If this bit is set, the CF1 pulse width is determined by the CF_LTMR register value. If this bit = 0, the active low pulse width is set at 80 ms for frequencies lower than 6.25 Hz.
// Bits: [18:0] BitName: CF_LTMR - Reset: 0x0 Access: R/W Description: If the CFx_LT bit in CF_LCFG register is set, this value determines the active low pulse width of the CFx pulse.

#define PART_ID_32 0x472 //Reset: 0x00000000 Access: Read only Description: This register identifies the IC. If the ADE9000_ID bit is 0, the IC is an ADE9078
// Bits: [31:22] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 21 BitName: AD73370_ID - Reset: 0x0 Access: Read only Description: This bit is set to identify an ADE73370 IC.
// Bits: 20 BitName: ADE9000_ID - Reset: 0x0 Access: Read only Description: This bit is set to identify an ADE9000 IC.
// Bits: [19:17]  BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 16 BitName: ADE9004_ID - Reset: 0x0 Access: Read only Description: This bit is set to identify an ADE9004 IC.
// Bits: [15:0] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved

//16-Bit Registers
#define RUN_16 0x480 //Reset: 0x0000 Access: R/W Description: Write this register to 1 to start the measurements

#define CONFIG1_16 0x481 //Reset: 0x0000 Access: R/W Description: Configuration Register 1.
// Bits: 15 BitName: EXT_REF - Reset: 0x0 Access: R/W Description:
// Bits: [14:13] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 12 BitName: IRQ0_ON_IRQ1 - Reset: 0x0 Access: R/W Description:
// Bits: 11 BitName: BURST_EN - Reset: 0x0 Access: R/W Description:
// Bits: 10 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: [9:8] BitName: PWR_SETTLE - Reset: 0x0 Access: R/W Description:
// Bits: [7:6] BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: 5 BitName: CF_ACC_CLR - Reset: 0x0 Access: Write only Description: Set this bit to clear the acculumation in the digital to frequency converter and CFDEN counter. Note that this bit automatically clears itself.
// Bits: 4 BitName: RESERVED - Reset: 0x0 Access: Read only Description: Reserved
// Bits: [3:2] BitName: CF4_CFG - Reset: 0x0 Access: R/W Description: These bits select which function to output on the CF4 pin. Setting: 00 for CF4, from digital to frequency converter. Setting: 01 for CF4, from digital to frequency converter. Setting: 10 for EVENT. Setting: 11 for DREADY.
// Bits: 1 BitName: CF3_CFG - Reset: 0x0 Access: R/W Description: This bit selects which function to output on the CF3 pin. Setting: 0 for CF3, from digital to freqency converter. Setting: 1 for Zero Crossing output selected by the ZX_SEL bits in the ZX_LP_SEL register.
// Bits: 0 BitName: SWRST - Reset: 0x0 Access: W1 Description: Set this bit to initiate a software reset. Note that this bit is self clearing.

#define ANGL_VA_VB_16 0x482 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase A and Phase B voltages.
#define ANGL_VB_VC_16 0x483 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase B and Phase C voltages.
#define ANGL_VA_VC_16 0x484 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase A and Phase C voltages.
#define ANGL_VA_IA_16 0x485 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase A voltage and current.
#define ANGL_VB_IB_16 0x486 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase B voltage and current.
#define ANGL_VC_IC_16 0x487 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase C voltage and current.
#define ANGL_IA_IB_16 0x488 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase A and Phase B current.
#define ANGL_IB_IC_16 0x489 //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase B and Phase C current.
#define ANGL_IA_IC_16 0x48A //Reset: 0x0000 Access: Read only Description: Time between positive to negative zero crossings on Phase A and Phase C current

#define CFMODE_16 0x490 //Reset: 0x0000 Access: R/W Description: CFx configureation register
// Bits: 15 BitName: CF4DIS - Reset: 0x0 Access: R/W Description: CF4 output disable. Set this bit to disable the CF4 output and bring the pin high. Note that when this bit is set, the CFx bit in STATUS0 is not set when a CF pulse is accumulated in the digital to frequency converter.
// Bits: 14 BitName: CF3DIS - Reset: 0x0 Access: R/W Description: CF1 output disable -- see CF4DIS
// Bits: 13 BitName: CF2DIS - Reset: 0x0 Access: R/W Description: CF1 output disable -- see CF4DIS
// Bits: 12 BitName: CF1DIS - Reset: 0x0 Access: R/W Description: CF1 output disable -- see CF4DIS
// Bits: [11:9] BitName: CF4SEL Reset: 0x0 Access: R/W Description: Type of energy output on the CF4 pin. Configure TERMSEL4 in the COMPMODE register to select which phases are included. Setting: 000 for Total Active Power. Setting: 001 for Total Reactive Power. Setting: 010 for Total Apparent Power. Setting: 100 for Fundamental reactive power. Setting: 110 for Total Active Power. Setting: 111 for Total Active Power.
// Bits: [8:6] BitName: CF3SEL Reset: 0x0 Access: R/W Description: Selects type of energy output on CF3 pin --see CF4SEL
// Bits: [5:3] BitName: CF2SEL Reset: 0x0 Access: R/W Description: Selects type of energy output on CF2 pin --see CF4SEL
// Bits: [2:0] BitName: CF1SEL Reset: 0x0 Access: R/W Description: Selects type of energy output on CF1 pin --see CF4SEL

#define COMPMODE_16 0x491 //Reset: 0x0000 Access: R/W Description: Computation mode register
// Bits: [15:12] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: [11:9] BitName: TERMSEL4 Reset: 0x0 Access: R/W Description: Phases to include in CF4 pulse output. Set the TERMSEL4[2] bit to one to include Phase C in the CF4 pulse output. Similarly, set TERMSEL4[1] to include Phase B and TERMSEL4[0] for Phase A.
// Bits: [8:6] BitName: TERMSEL3 Reset: 0x0 Access: R/W Description: Phases to include in CF3 pulse output --see TERMSEL4
// Bits: [5:3] BitName: TERMSEL2 Reset: 0x0 Access: R/W Description: Phases to include in CF2 pulse output --see TERMSEL4
// Bits: [2:0] BitName: TERMSEL1 Reset: 0x0 Access: R/W Description: Phases to include in CF1 pulse output --see TERMSEL4

#define ACCMODE_16 0x492 //Reset: 0x0000 Access: R/W Description: Accumulation mode register
// Bits: [15:9] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 8 BitName: SELFREQ Reset: 0x0 Access: R/W Description:This bit is used to configure the IC for a 50 Hz or 60 Hz system. This setting is used in the fundamental reactive power measurement and to set the default line period used for resampling calculations if a zero crossing is not present. Setting: 0 for 50 Hz. Setting: 1 for 60 Hz.
// Bits: 7 BitName: ICONSEL Reset: 0x0 Access: R/W Description: Set this bit to calculate the current flowing through IB from the IA and IC measurements. if this bit is set, IB = -IA - IC.
// Bits: [6:4] BitName: VCONSEL Reset: 0x0 Access: R/W Description: Three-wire and four-wire hardware configuration selection. Setting: 000 for 4-wire wye. Setting: 001 for 3-wire delta. VB' = VA-VC. Setting: 010 for 4-wire delta, non-Blondel compliant. VB' = -VA - VC. Setting: 011 for 4-wire delta non-Blondel compliant. VB' = -VA. Setting: 100 for 3-wire delta. VA'=VA-VB; VB' = VA-VC; VC'=VC-VB.
// Bits: [3:2] BitName: VARACC Reset: 0x0 Access: R/W Description: Total and fundamental reactive power accumulation mode for energy registers and CFx pulses. Setting: 00 for Signed accumulation mode. Setting: 01 for Absolute Value accumulation mode. Setting: 10 for Positve accumulation mode. Setting: 11 for Negative accumulation mode.
// Bits: [1:0] BitName: WATTACC Reset: 0x0 Access: R/W Description: Total and fundamental active power accumulation mode for energy registers and CFx pulses--see VARACC.

#define CONFIG3_16 0x493 //Reset: 0x0000 Access: R/W Description: Configuraiton Register 3
// Bits: [15:5] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: [4:2] BitName: PEAKSEL Reset: 0x0 Access: R/W Description: Set this bit to select which phase(s) to monitor peak voltages and currents on. Write PEAKSEL[0] to one to enable Phase A peak detection. Similarly, PEAKSEL[1] enables Phase B peak detection and PEAKSEL[2] enables Phase C peak detection.
// Bits: [1:0] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved

#define CF1DEN_16 0x494 //Reset: 0xFFFF Access: R/W Description: CF1 denominator register
#define CF2DEN_16 0x495 //Reset: 0xFFFF Access: R/W Description: CF2 denominator register
#define CF3DEN_16 0x496 //Reset: 0xFFFF Access: R/W Description: CF3 denominator register
#define CF4DEN_16 0x497 //Reset: 0xFFFF Access: R/W Description: CF4 denomoinator register
#define ZXTOUT_16 0x498 //Reset: 0xFFFF Access: R/W Description: Zero-crossing timeout configuration register.
#define ZXTHRSH_16 0x499 //Reset: 0x0009 Access: R/W Description: Voltage channel zero-crossing threshold register.

#define ZX_LP_SEL_16 0x49A //Reset: 0x001E Access: R/W Description: This register selects which zero crossing and which line period measurement are used for other calculations.
// Bits: [15:5] BitName: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: [4:3] BitName: LP_SEL Reset: 0x3 Access: R/W Description: Selects line period measurement used for resampling. Setting: 00 APERIOD, line period measurement from Phase A voltage. Setting: 01 for BPERIOD, line period measurement from Phase B voltage. Setting: 10 for CPERIOD, line period measurement from Phase C voltage. Setting: 11 for COM_PERIOD, line period measurement on combined signal from VA, VB, and VC.
// Bits: [2:1] BitName: ZX_SEL Reset: 0x3 Access: R/W Description: Selects the zero-crossing signal, which can be routed to CF3/ZX output pin and which is used for line cycle energy accumulation. Setting: 00 for ZXVA, Phase A voltage zero-crossing signal. Setting: 01 ZXVB, Phase B voltage zero-crossing signal.  Setting: 10 for ZXVC, Phase C voltage zero-crossing signal. Setting: 11 for ZXCOMB, zero crossing on combined signal from VA,VB and VC.
// Bits: 0 BitName: RESERVED Reset: 0x0 Access: R Description: Reserved

#define SEQ_CYC_16 0x49C //Reset: 0x00FF Access: R/W Description: Number of line cycles used for phase sequence detection. It is recommended to set this register to 1.
#define PHSIGN_16 0x49D //Reset: 0x0000 Access: Read only Description: Power sign register
// Bits: [15:10] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 9 BitName: SUM4SIGN Reset: 0x0 Access: R Description: Sign of the sum of the powers included in the CF4 datapath. The CF4 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 8 BitName: SUM3SIGN Reset: 0x0 Access: R Description: Sign of the sum of the powers included in the CF3 datapath. The CF3 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 7 BitName: SUM2SIGN Reset: 0x0 Access: R Description: Sign of the sum of the powers included in the CF2 datapath. The CF2 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 6 BitName: SUM1SIGN Reset: 0x0 Access: R Description: Sign of the sum of the powers included in the CF1 datapath. The CF1 energy is positive if this bit is clear and negative if this bit is set.
// Bits: 5 BitName: CVARSIGN Reset: 0x0 Access: R Description: Phase C reactive power sign bit. The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 4 BitName: CWSIGN Reset: 0x0 Access: R Description: Phase C active power sign bit
// Bits: 3 BitName: BVARSIGN Reset: 0x0 Access: R Description: Phase B reactive power sign bit. The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 2 BitName: BWSIGN Reset: 0x0 Access: R Description: Phase B active power sign bit.
// Bits: 1 BitName: AVARSIGN Reset: 0x0 Access: R Description: Phase A reactive power sign bit.  The PWR_SIGN_SEL bit in the EP_CFG selects whether this feature monitors total or fundamental reactive power.
// Bits: 0 BitName: AWSIGN Reset: 0x0 Access: R Description: Phase A active power sign bit
#define WFB_CFG_16 0x4A0 //Reset: 0x0000 Access: R/W Description: Waveform buffer configuration register
// Bits: [15:13] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 12 BitName: WF_IN_EN Reset: 0x0 Access: R/W Description: This setting determines whether the IN waveform samples are read out of the waveform buffer through SPI. 0: IN waveform samples are not read out of waveform buffer through SPI. 1: IN waveform samples are read out of waveform buffer through SPI
// Bits: [11:10] BitName: RESERVED Reset: 0x0 Access: R Description: Sign of the sum of the powers included in the CF3 datapath. The CF3 energy is positive if this bit is clear and negative if this bit is set.
// Bits: [9:8] BitName: WF_SRC Reset: 0x0 Access: R/W Description: Waveform buffer souce and DREADY, data ready update rate, selection. 00: Sinc4 output, at 16kSPS. 01: Reserved. 10: Sinc4 + IIR LPF output, at 4 kSPS. 11: Current and voltage channel waveform samples, processed by the DSP (xl_PCF, xV_PCF) at 4 kSPS.
// Bits: [7:6] BitName: WF_MODE Reset: 0x0 Access: R/W Description: fixed data rate waveforms filling and trigger based modes. 00: stop when waveform buffer is full. 01: continuous fill-stop only on enabled trigger events. 10: Continuous filling-center capture around enabled trigger events. 11: continuous fill-save event address of enabled trigger events
// Bits: 5 BitName: WF_CAP_SEL Reset: 0x0 Access: R/W Description: This bit selects whether the waveform buffer is filled with resampled data or fixed data rate data, selected in the WF_CAP_SEL bits. 0: resampled data. 1: fixed data rate data
// Bits: 4 BitName: WF_CAP_EN Reset: 0x0 Access: R/W Description: When this bit is set, waveform capture is started. 0: the waveform capture is disabled. the waveform buffer contents are maintained. 1: the waveform capture is started, according to the type of capture in WF_CAP_SEL and the WF_SRC bits when this bit goes from a 0 to a 1.
// Bits: [3:0] BitName: BURST_CHAN Reset: 0x0 Access: R/W Description: selects which data to read out of the waveform buffer through SPI. 0000: all channels. 0001: IA and VA. 0010: IB and VB. 0011: IC and VC. 1000: IA. 1001: VA. 1010: IB. 1011:VB 1100:IC. 1101:VC. 1110:In if WF_IN_EN =1 in the WFB_CFG registers. 1111: single address read (SPI burst read mode is disabled)
#define WFB_PG_IRQEN_16 0x4A1 //Reset: 0x0000 Access: R/W Description: This register enables interrupts to occur after specific pages of the waveform buffer have been filled.
#define WFB_TRG_CFG_16 0x4A2 //Reset: 0x0000 Access: R/W Description: This register enables events to trigger a capture in the waveform buffer
// Bits: [15:11] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: 10 Bitname: TRIG_FORCE Reset: 0x0 Access: R/W Description: Set this bit to trigger an even to stop the waveform buffer filling
// Bits: 9 Bitname: ZXCOMB Reset: 0x0 Access: R/W Description: Zero crossing on combined signal from VA, VB, and VC
// Bits: 8 Bitname: ZXVC Reset: 0x0 Access: R/W Description: Phase C voltage zero crossing.
// Bits: 7 Bitname: ZXVB Reset: 0x0 Access: R/W Description: Phase B voltage zero crossing.
// Bits: 6 Bitname: ZXVA Reset: 0x0 Access: R/W Description: Phase A voltage zero crossing.
// Bits: 5 Bitname: ZXIC Reset: 0x0 Access: R/W Description: Phase C current zero crossing.
// Bits: 4 Bitname: ZXIB Reset: 0x0 Access: R/W Description: Phase B current zero crossing.
// Bits: 3 Bitname: ZXIA Reset: 0x0 Access: R/W Description: Phase A current zero crossing.
// Bits: [2:0] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
#define WFB_TRG_STAT_16 0x4A3 //Reset: 0x0000 Access: R/W Description: This register indicates the last page that was filled in the waveform buffer and the location of trigger events.
// Bits: [15:12] Bitname: WFB_LAST_PAGE Reset: 0x0 Access: R/W Description: These bits indicate which page of the waveform buffer was filled last, when filling with fixed rate data samples
// Bits: 11 Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits: [10:0]  Bitname: WFB_TRIG_ADDR Reset: 0x0 Access: R Description: This holds the address of the last sample put into the waveform buffer after a trigger event occurred, which is within a sample or two of when the actual trigger event occurred.
#define CONFIG5_16 0x4A4 //Reset: 0x0063 Access: R/W Description: Reset: 0x0063 Access: R/W Description: Configuration Register 5
#define CRC_RSLT_16 0x4A8 //Reset: 0x0000 Access: R Description: This register holds the CRC of configuration registers.
#define CRC_SPI_16 0x4A9 //Reset: 0x0000 Access: R Description: This register holds the 16-bit CRC of the data sent out on the MOSI pin during the last SPI register read.
#define LAST_DATA_16 0x4AC //Reset: 0x0000 Access: R Description: This register holds the data read or written during the last 16-bit transaction on the SPI port.
#define LAST_CMD_16 0x4AE //Reset: 0x0000 Access: R Description: This register holds the address and read/write operation request (CMD_HDR) for the last transaction on the SPI port.
#define CONFIG2_16 0x4AF //Reset: 0x0C00 Access: R/W Description: Configuration Register 2
// Bits [15:13] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits 12 Bitname: UPERIOD_SEL Reset: 0x0 Access: R/W Description: Set this bit to use a user configured line period, in USER_PERIOD, for the resampling calculation. If this bit is clear, the phase voltage line period selected by the LP_SEL[1:0] bits in the ZX_LP_SEL register is used.
// Bits [11:9] Bitname: HPF_CRN Reset: 0x6 Access: R/W Description: High-Pass filter corner (f3dB) enabled when the HPFDIS is bit in the CONFIGO register=0
//000 38.695 Hz.
//001 19.6375 Hz.
//010 9.895 Hz.
//011 4.9675 Hz.
//100 2.49 Hz.
//101 1.2475 Hz.
//110 0.625 Hz.
//111 0.3125 Hz.
// Bits [8:0] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved.
#define EP_CFG_16 0x4B0 //Reset: 0x0000 Access: R/W Description: Energy and power accumulation configuration
// Bits [15:13] Bitname: NOLOAD_TMR Reset: 0x0 Access: R/W Description: This register configures how many 4 kSPS samples to evaluate the no load condition convert
//000 64.
//001 128.
//010 256.
//011 512.
//100 1024.
//101 2048.
//110 4096.
//111 Disable no load threshold.

// Bits [12:8] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits 7 Bitname: PWR_SIGN_SEL Reset: 0x0 Access: R/W Description: Selects whether the REVRPx bit follows the sign of the total or fundamental reactive power. 0: Total reactive power. 1: Fundamental reactive power
// Bits 6 Bitname: RESERVED  Reset: 0x0 Access: R Description: Reserved
// Bits 5 Bitname: RD_RST_EN Reset: 0x0 Access: R/W Description: Set this bit to enable the energy register read with reset feature. If this bit is set, when one of the xWATTHR, xVAHR, xVARHR and xFVARHR register is read, it is reset and begins accumulating energy from zero.
// Bits 4 Bitname: EGY_LD_ACCUM Reset: 0x0 Access: R/W Description: If this bit = 0, the internal energy register is added to the user accessible energy register. If the bit is set, the internal energy register overwrites the user accessible energy register when the EGYRDY event occurs.
// Bits [3:2] Bitname: RESERVED Reset: 0x0 Access: R Description: Reserved
// Bits 1 Bitname: EGY_TMR_MODE Reset: 0x0 Access: R/W Description: This bit determines whether energy is accumulated based on the number of 4 kSPS samples or zero crossing events configured in the EGY_TIME register
        // 0 Accumulate energy based on 4 kSPS samples.
        // 1 Accumulate energy based on the zero crossing selected by the ZX_SEL bits in the ZX_LP_SEL register.
// Bits 0 Bitname: EGY_PWR_EN Reset: 0x0 Access: R/W Description: Set this bit to enable the energy and power accumulator, when the run bit is also set.

#define PWR_TIME_16 0x4B1 //Reset: 0x00FF Access: R/W Description: POwer and time configuration
#define EGY_TIME_16 0x4B2 //Reset: 0x00FF Access: R/W Description: Energy accumulation update time configuration
#define CRC_FORCE_16 0x4B4 //Reset: 0x0000 Access: R/W Description: This register forces an update of the CRC of configuration registers.
// Bits [15:1] Bitname: RESERVED Reset: 0x0 Access: R Description: RESERVED
// Bits 0 Bitname: FORCE_CRC_UPDATE Reset: 0x0 Access: R/W Description: Write this bit to force the configuration register CRC calculation to start. When the calculation is complete, the CRC_DONE bit is set in the STATUS1 register

#define CRC_OPTEN_16 0x4B5 //Reset: 0x0000 Access: R/W Description: This register selects which registers are optionally included in the configuration register CRC feature
// Bits: 15 CRC_WFB_TRG_CFG_EN Reset: 0x0 Access: R/W Description: Set this bit to include the WFB_TRG_CFG register in the configuration register CRC calculation.
// Bits: 14 CRC_WFB_PG_IRQEN Reset: 0x0 Access: R/W Description: Set this bit to include the WFB_PG_IRQEN register in the configuration register CRC calculation.
// Bits: 13 CRC_WFB_CFG_EN Reset: 0x0 Access: R/W Description: Set this bit to include the WFB_CFG register in the configuration register CRC calculation.
// Bits: 12 CRC_SEQ_CYC_EN Reset: 0x0 Access: R/W Description: Set this bit to include the SEQ_CYC register in the configuration register CRC calculation.
// Bits: 11 CRC_ZXLPSEL_EN Reset: 0x0 Access: R/W Description: Set this bit to include the ZX_LP_SEL register in the configuration register CRC calculation.
// Bits: 10 CRC_ZXTOUT_EN Reset: 0x0 Access: R/W Description: Set this bit to include the CRC_ZXTOUT_EN register in the configuration register CRC calculation.
// Bits: 9 CRC_APP_NL_LVL_EN Reset: 0x0 Access: R/W Description: Set this bit to include the APP_NL_LVL register in the configuration register CRC calculation.
// Bits: 8 CRC_REACT_NL_LVL_EN Reset: 0x0 Access: R/W Description: Set this bit to include the REACT_NL_LVL register in the configuration register CRC calculation.
// Bits: 7 CRC_ACT_NL_LVL_EN Reset: 0x0 Access: R/W Description: Set this bit to include the ACT_NL_LVL register in the configuration register CRC calculation.
// Bits: [6:3] RESERVED Reset: 0x0 Access: R Description: Reserved.
// Bits: 2 CRC_EVENT_MASK_EN Reset: 0x0 Access: R/W Description: Set this bit to include the EVENT_MASK register in the configuration register CRC calculation.
// Bits: 1 CRC_MASK1_EN Reset: 0x0 Access: R/W Description: Set this bit to include the MASK1 register in the configuration register CRC calculation.
// Bits: 0 CRC_MASK0_EN Reset: 0x0 Access: R/W Description: Set this bit to include the MASK0 register in the configuration register CRC calculation.


#define PSM2_CFG_16 0x4B8 //Reset: 0x001F Access: R/W
/* This register configures settings for the low power PSM2 operating mode. This register value is retained in PSM2 and PSM3 but is rewritten to its default value when entering PSM0 and PSM1. */
// Bits: [15:9] Reset: 0x0 Access: R Description: Reserved
// Bits: [8:5] Reset: 0x0 Access: R/W Description: PKDET_LVL //These bits configure the PSM2 low power comparator peak current detection Level, listed as the input signal level with respect to full scale. The register value is retained in PSM2 and PSM3. It returns to its default value if PSM0 is entered.
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
// [Bits: 4:0] LPLINE Reset: 0x1F Access: R/W Description: This register determines the time used to detect 0x1F R/W peak currents in the low power comparator in
//  PSM2 operating mode. Note that this register
//  retains its value in PSM2 and PSM3 operating
//  modes but is reset to its default value upon entering PSM0 or PSM1.

#define PGA_GAIN_16 0x4B9 //Reset: 0x0000 Access: R/W
/*This register configures the PGA gain for each ADC */
// Bits: [15:14] RESERVED Reset: 0x0 Access: R Description: Reserved.
// Bits: [13:12] VC_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Voltage Channel C ADC. 0x0 R/W
    //  00 Gain = 1.
    //  01 Gain = 2.
    //  10 Gain = 4.
    //  11 Gain = 4.
// Bits: [11:10] VB_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Voltage Channel B ADC. See 0x0 R/W VC_GAIN.
// Bits: [9:8] VA_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Voltage Channel A ADC. See 0x0 R/W VC_GAIN.
// Bits: [7:6] IN_GAIN Reset: 0x0 Access: R/W Description: PGA gain for neutral current channel ADC. See 0x0 R/W VC_GAIN.
// Bits: [5:4] IC_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Current Channel C ADC. See 0x0 R/W VC_GAIN.
// Bits: [3:2] IB_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Voltage Channel B ADC. See 0x0 R/W VC_GAIN.
// Bits: [1:0] IA_GAIN Reset: 0x0 Access: R/W Description: PGA gain for Current Channel A ADC. See 0x0 R/W VC_GAIN.

#define CHNL_DIS_16 0x4BA //Reset: 0x0000 Access: R/W
/* This register can be disables the ADCs individually */
// Bits: [15:7] RESERVED Reset: 0x0 Access: R Description: Reserved.
// Bits: 6 VC_DISAD Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 5 VB_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 4 VA_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 3 IN_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 2 IC_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 1 IB_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.
// Bits: 0 IA_DISADC Reset: 0x0 Access: R/W Description: Set this bit to one to disable the ADC.


#define WR_LOCK_16 0x4BF //Reset: 0x0000 Access: R/W
/* This register enables the configuration lock feature */
#define VAR_DIS_16 0x4E0 //Reset: 0x0000 Access: R/W
/* Enable/disable total reactive power calculation */
// [15:1] - Reserved Reset: 0x0 Access: R Description: Reserved.
// 0 - VARDIS Reset: 0x0 Access: R/W Description: Set this bit to disable the total VAR calculation. This 0x0 R/W bit must be set before writing the run bit for proper operation.

#define RESERVED1_16 0x4F0 //Reset: 0x0000 Access: R
/* This register is reserved */
#define VERSION_16 0x4FE //Reset: 0x0040 Access: R
/* Version of the ADE9078 IC */
#define AI_SINC_DAT_32 0x500 //Reset: 0x00000000 Access: R
/* Current Channel A ADC waveforms from sinc4 output, at 16 kSPS */
#define AV_SINC_DAT_32 0x501 //Reset: 0x00000000 Access: R
/* Voltage Channel A ADC waveforms from sinc4 output, at 16 kSPS */
#define BI_SINC_DAT_32 0x502 //Reset: 0x00000000 Access: R
/* Current Channel B ADC waveforms from sinc4 output, at 16 kSPS */
#define BV_SINC_DAT_32 0x503 //Reset: 0x00000000 Access: R
/* Voltage Channel B ADC waveforms from sinc4 output, at 16 kSPS */
#define CI_SINC_DAT_32 0x504 //Reset: 0x00000000 Access: R
/* Current Channel C ADC waveforms from sinc4 output, at 16 kSPS */
#define CV_SINC_DAT_32 0x505 //Reset: 0x00000000 Access: R
/* Voltage Channel C ADC waveforms from sinc4 output, at 16 kSPS */
#define NI_SINC_DAT_32 0x506 //Reset: 0x00000000 Access: R
/* Neutral current channel ADC waveforms from sinc4 output, at 16 kSPS */
#define AI_LPF_DAT_32 0x510 //Reset: 0x00000000 Access: R
/* Current Channel A ADC waveforms from sinc4 + IIR LPF and decimator output, at 4 kSPS */
#define AV_LPF_DAT_32 0x511 //Reset: 0x00000000 Access: R
/* Voltage Channel A ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define BI_LPF_DAT_32 0x512 //Reset: 0x00000000 Access: R
/* Current Channel B ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define BV_LPF_DAT_32 0x513 //Reset: 0x00000000 Access: R
/* Voltage Channel B ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define CI_LPF_DAT_32 0x514 //Reset: 0x00000000 Access: R
/* Current Channel C ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define CV_LPF_DAT_32 0x515 //Reset: 0x00000000 Access: R
/* Voltage Channel C ADC waveforms from sinc4 + IIR LPF output, at 4 kSPS */
#define NI_LPF_DAT_32 0x516 //Reset: 0x00000000 Access: R
/* Neutral current channel ADC waveforms from since4 + IIR LPF output, at 4 kSPS*/
#define AV_PCF_1_32 0x600 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AV_PCF in Table 31*/
#define BV_PCF_1_32 0x601 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BV_PCF in Table 31*/
#define CV_PCF_1_32 0x602 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CV_PCF in Table 31*/
#define NI_PCF 0x603-1_32 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See NI_PCF in Table 31*/
#define AI_PCF_1_32 0x604 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AI_PCF in Table 31*/
#define BI_PCF_1_32 0x605 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BI_PCF in Table 31*/
#define CI_PCF_1_32 0x606 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CI_PCF in Table 31*/
#define AIRMS_1_32 0x607 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AIRMS in Table 31*/
#define BIRMS_1_32 0x608 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BIRMS in Table 31*/
#define CIRMS_1_32 0x609 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CIRMS in Table 31*/
#define AVRMS_1_32 0x60A //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVRMS in Table 31*/
#define BVRMS_1_32 0x60B //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVRMS in Table 31*/
#define CVRMS_1_32 0x60C //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVRMS in Table 31*/
#define NIRMS_1_32 0x60D //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See NIRMS in Table 31*/
#define AWATT_1_32 0x60E //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AWATT in Table 31*/
#define BWATT_1_32 0x60F //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BWATT in Table 31*/
#define CWATT_1_32 0x610 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CWATT in Table 31*/
#define AVA_1_32 0x611 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVA in Table 31*/
#define BVA_1_32 0x612 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVA in Table 31*/
#define CVA_1_32 0x613 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVA in Table 31*/
#define AVAR_1_32 0x614 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVAR in Table 31*/
#define BVAR_1_32 0x615 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVAR in Table 31*/
#define CVAR_1_32 0x616 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVAR in Table 31*/
#define AFVAR_1_32 0x617 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AFVAR in Table 31*/
#define BFVAR_1_32 0x618 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BFVAR in Table 31*/
#define CFVAR_1_32 0x619 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CFVAR in Table 31*/
#define APF_1_32 0x61A //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See APF in Table 31*/
#define BPF_1_32 0x61B //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BPF in Table 31*/
#define CPF_1_32 0x61C //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CPF in Table 31*/
#define AV_PCF_2_32 0x680 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AV_PCF in Table 31*/
#define AI_PCF_2_32 0x681 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AI_PCF in Table 31*/
#define AIRMS_2_32 0x682 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AIRMS in Table 31*/
#define AVRMS_2_32 0x683 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVRMS in Table 31*/
#define AWATT_2_32 0x684 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AWATT in Table 31*/
#define AVA_2_32 0x685 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVA in Table 31*/
#define AVAR_2_32 0x686 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AVAR in Table 31*/
#define AFVAR_2_32 0x687 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See AFVAR in Table 31*/
#define APF_2_32 0x688 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See APF in Table 31*/
#define BV_PCF_2_32 0x693 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BV_PCF in Table 31*/
#define BI_PCF_2_32 0x694 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BI_PCF in Table 31*/
#define BIRMS_2_32 0x695 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BIRMS in Table 31*/
#define BVRMS_2_32 0x696//Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVRMS in Table 31*/
#define BWATT_2_32 0x697 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BWATT in Table 31*/
#define BVA_2_32 0x698 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVA in Table 31*/
#define BVAR_2_32 0x699 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BVAR in Table 31*/
#define BFVAR_2_32 0x69A //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BFVAR in Table 31*/
#define BPF_2_32 0x69B //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See BPF in Table 31*/
#define CV_PCF_2_32 0x6A6 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CV_PCF in Table 31*/
#define CI_PCF_2_32 0x6A7 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CI_PCF in Table 31*/
#define CIRMS_2_32 0x6A8 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CIRMS in Table 31*/
#define CVRMS_2_32 0x6A9 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVRMS in Table 31*/
#define CWATT_2_32 0x6AA //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CWATT in Table 31*/
#define CVA_2_32 0x6AB //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVA in Table 31*/
#define CVAR_2_32 0x6AC //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CVAR in Table 31*/
#define CFVAR_2_32 0x6AD //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CFVAR in Table 31*/
#define CPF_2_32 0x6AE //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See CPF in Table 31*/
#define NI_PCF_2_32 0x6B9 //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See NI_PCF in Table 31*/
#define NIRMS_2_32 0x6BA //Reset: 0x00000000 Access: R/W
/* SPI burst read accessible. Registers organized functionally. See NIRMS in Table 31*/
