/* ================================================================================

     Project      :   ade90xx
     File         :   ade90xx.h
     Description  :   API macros header definition register file.

     Date         :   May 3, 2016

     Copyright (c) 2016 Analog Devices, Inc.  All Rights Reserved.
     This software is proprietary and confidential to Analog Devices, Inc. and
     its licensors.

     This file was auto-generated. Do not make local changes to this file.

   ================================================================================ */


#define ADDR_AIGAIN                          0x00000000            /*  Phase A current gain adjust. */
#define ADDR_AIGAIN0                         0x00000001            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, AIGAIN0 through AIGAIN5, is applied based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_AIGAIN1                         0x00000002            /*  Phase A Multipoint gain correction factor--see AIGAIN0. */
#define ADDR_AIGAIN2                         0x00000003            /*  Phase A Multipoint gain correction factor--see AIGAIN0. */
#define ADDR_AIGAIN3                         0x00000004            /*  Phase A Multipoint gain correction factor--see AIGAIN0. */
#define ADDR_AIGAIN4                         0x00000005            /*  Phase A Multipoint gain correction factor--see AIGAIN0. */
#define ADDR_APHCAL0                         0x00000006            /*  If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, then the APHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the APHCAL0 through APHCAL4 value is applied, based on the AIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_APHCAL1                         0x00000007            /*  Phase A Multipoint phase correction factor--see APHCAL0. */
#define ADDR_APHCAL2                         0x00000008            /*  Phase A Multipoint phase correction factor--see APHCAL0. */
#define ADDR_APHCAL3                         0x00000009            /*  Phase A Multipoint phase correction factor--see APHCAL0. */
#define ADDR_APHCAL4                         0x0000000A            /*  Phase A Multipoint phase correction factor--see APHCAL0. */
#define ADDR_AVGAIN                          0x0000000B            /*  Phase A voltage gain adjust. */
#define ADDR_AIRMSOS                         0x0000000C            /*  Phase A current rms offset for filter-based AIRMS calculation */
#define ADDR_AVRMSOS                         0x0000000D            /*  Phase A voltage rms offset for filter-based AVRMS calculation */
#define ADDR_APGAIN                          0x0000000E            /*  Phase A power gain adjust for AWATT, AVA, AVAR, AFWATT, AFVA and AFVAR calculations */
#define ADDR_AWATTOS                         0x0000000F            /*  Phase A total active power offset correction for AWATT calculation */
#define ADDR_AVAROS                          0x00000010            /*  Phase A total reactive power offset correction for AVAR calculation */
#define ADDR_AFWATTOS                        0x00000011            /*  Phase A fundamental active power offset correction for AFWATT calculation. */
#define ADDR_AFVAROS                         0x00000012            /*  Phase A fundamental reactive power offset correction for AFVAR calculation */
#define ADDR_AIFRMSOS                        0x00000013            /*  Phase A current rms offset for fundamental current rms, AIFRMS calculation */
#define ADDR_AVFRMSOS                        0x00000014            /*  Phase A voltage rms offset for fundamental voltage rms, AVFRMS calculation */
#define ADDR_AVRMSONEOS                      0x00000015            /*  Phase A voltage rms offset for fast RMS1/2, AVRMSONE calculation */
#define ADDR_AIRMSONEOS                      0x00000016            /*  Phase A current rms offset for fast RMS1/2, AIRMSONE calculation */
#define ADDR_AVRMS1012OS                     0x00000017            /*  Phase A voltage rms offset for 10/12 cycle rms, AVRMS1012 calculation */
#define ADDR_AIRMS1012OS                     0x00000018            /*  Phase A current rms offset for 10/12 cycle rms, AIRMS1012 calculation */
#define ADDR_BIGAIN                          0x00000020            /*  Phase B current gain adjust. */
#define ADDR_BIGAIN0                         0x00000021            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, BIGAIN0 through BIGAIN5, is applied based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_BIGAIN1                         0x00000022            /*  Phase B Multipoint gain correction factor--see BIGAIN0. */
#define ADDR_BIGAIN2                         0x00000023            /*  Phase B Multipoint gain correction factor--see BIGAIN0. */
#define ADDR_BIGAIN3                         0x00000024            /*  Phase B Multipoint gain correction factor--see BIGAIN0. */
#define ADDR_BIGAIN4                         0x00000025            /*  Phase B Multipoint gain correction factor--see BIGAIN0. */
#define ADDR_BPHCAL0                         0x00000026            /*  If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, then the BPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the BPHCAL0 through BPHCAL4 value is applied, based on the BIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_BPHCAL1                         0x00000027            /*  Phase B Multipoint phase correction factor--see BPHCAL0. */
#define ADDR_BPHCAL2                         0x00000028            /*  Phase B Multipoint phase correction factor--see BPHCAL0. */
#define ADDR_BPHCAL3                         0x00000029            /*  Phase B Multipoint phase correction factor--see BPHCAL0. */
#define ADDR_BPHCAL4                         0x0000002A            /*  Phase B Multipoint phase correction factor--see BPHCAL0. */
#define ADDR_BVGAIN                          0x0000002B            /*  Phase B voltage gain adjust. */
#define ADDR_BIRMSOS                         0x0000002C            /*  Phase B current rms offset for BIRMS calculation */
#define ADDR_BVRMSOS                         0x0000002D            /*  Phase B voltage rms offset for BVRMS calculation */
#define ADDR_BPGAIN                          0x0000002E            /*  Phase B power gain adjust for BWATT, BVA, BVAR, BFWATT, BFVA and BFVAR calculations */
#define ADDR_BWATTOS                         0x0000002F            /*  Phase B total active power offset correction for BWATT calculation */
#define ADDR_BVAROS                          0x00000030            /*  Phase B total reactive power offset correction for BVAR calculation */
#define ADDR_BFWATTOS                        0x00000031            /*  Phase B fundamental active power offset correction for BFWATT calculation. */
#define ADDR_BFVAROS                         0x00000032            /*  Phase B fundamental reactive power offset correction for BFVAR calculation */
#define ADDR_BIFRMSOS                        0x00000033            /*  Phase B current rms offset for fundamental current rms, BIFRMS calculation */
#define ADDR_BVFRMSOS                        0x00000034            /*  Phase B voltage rms offset for fundamental voltage rms, BVFRMS calculation */
#define ADDR_BVRMSONEOS                      0x00000035            /*  Phase B voltage rms offset for fast RMS1/2, BVRMSONE calculation */
#define ADDR_BIRMSONEOS                      0x00000036            /*  Phase B current rms offset for fast RMS1/2, BIRMSONE calculation */
#define ADDR_BVRMS1012OS                     0x00000037            /*  Phase B voltage rms offset for 10/12 cycle rms, BVRMS1012 calculation */
#define ADDR_BIRMS1012OS                     0x00000038            /*  Phase B current rms offset for 10/12 cycle rms, BVRMS1012 calculation */
#define ADDR_CIGAIN                          0x00000040            /*  Phase C current gain adjust. */
#define ADDR_CIGAIN0                         0x00000041            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, an additional gain factor, CIGAIN0 through CIGAIN5, is applied based on the CIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_CIGAIN1                         0x00000042            /*  Phase C Multipoint gain correction factor--see CIGAIN0. */
#define ADDR_CIGAIN2                         0x00000043            /*  Phase C Multipoint gain correction factor--see CIGAIN0. */
#define ADDR_CIGAIN3                         0x00000044            /*  Phase C Multipoint gain correction factor--see CIGAIN0. */
#define ADDR_CIGAIN4                         0x00000045            /*  Phase C Multipoint gain correction factor--see CIGAIN0. */
#define ADDR_CPHCAL0                         0x00000046            /*  If multipoint phase and gain calibration is disabled, with MTEN = 0 in the CONFIG0 register, then the CPHCAL0 phase compensation is applied. If multipoint phase and gain correction is enabled, with MTEN = 1, then the CPHCAL0 through CPHCAL4 value is applied, based on the CIRMS current rms amplitude and the MTTHR_Lx and MTTHR_Hx register values */
#define ADDR_CPHCAL1                         0x00000047            /*  Phase C Multipoint phase correction factor--see CPHCAL0. */
#define ADDR_CPHCAL2                         0x00000048            /*  Phase C Multipoint phase correction factor--see CPHCAL0. */
#define ADDR_CPHCAL3                         0x00000049            /*  Phase C Multipoint phase correction factor--see CPHCAL0. */
#define ADDR_CPHCAL4                         0x0000004A            /*  Phase C Multipoint phase correction factor--see CPHCAL0. */
#define ADDR_CVGAIN                          0x0000004B            /*  Phase C voltage gain adjust. */
#define ADDR_CIRMSOS                         0x0000004C            /*  Phase C current rms offset for CIRMS calculation */
#define ADDR_CVRMSOS                         0x0000004D            /*  Phase C voltage rms offset for CVRMS calculation */
#define ADDR_CPGAIN                          0x0000004E            /*  Phase C power gain adjust for CWATT, CVA, CVAR, CFWATT, CFVA and CFVAR calculations */
#define ADDR_CWATTOS                         0x0000004F            /*  Phase C total active power offset correction for CWATT calculation */
#define ADDR_CVAROS                          0x00000050            /*  Phase C total reactive power offset correction for CVAR calculation */
#define ADDR_CFWATTOS                        0x00000051            /*  Phase C fundamental active power offset correction for CFWATT calculation. */
#define ADDR_CFVAROS                         0x00000052            /*  Phase C fundamental reactive power offset correction for CFVAR calculation */
#define ADDR_CIFRMSOS                        0x00000053            /*  Phase C current rms offset for fundamental current rms, CIFRMS calculation */
#define ADDR_CVFRMSOS                        0x00000054            /*  Phase C voltage rms offset for fundamental voltage rms, CVFRMS calculation */
#define ADDR_CVRMSONEOS                      0x00000055            /*  Phase C voltage rms offset for fast RMS1/2, CVRMSONE calculation */
#define ADDR_CIRMSONEOS                      0x00000056            /*  Phase C current rms offset for fast RMS1/2, CIRMSONE calculation */
#define ADDR_CVRMS1012OS                     0x00000057            /*  Phase C voltage rms offset for 10/12 cycle rms, CVRMS1012 calculation */
#define ADDR_CIRMS1012OS                     0x00000058            /*  Phase C current rms offset for 10/12 cycle rms, CIRMS1012 calculation */
#define ADDR_CONFIG0                         0x00000060            /*  Configuration register 0 */
#define ADDR_MTTHR_L0                        0x00000061            /*  Multipoint Phase/Gain Threshold. If MTEN = 1 in the CONFIG0 register, the MTGNTHR_Lx and MTGNTHR_Hx registers set up the ranges in which to apply each set of corrections, allowing for hysteresis--see the Multipoint Phase/Gain Correction section for more information */
#define ADDR_MTTHR_L1                        0x00000062            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_L2                        0x00000063            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_L3                        0x00000064            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_L4                        0x00000065            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_H0                        0x00000066            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_H1                        0x00000067            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_H2                        0x00000068            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_H3                        0x00000069            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_MTTHR_H4                        0x0000006A            /*  Multipoint Phase/Gain threshold--see MTTHR_L0 for more information. */
#define ADDR_NIRMSOS                         0x0000006B            /*  Neutral current rms offset for NIRMS calculation */
#define ADDR_ISUMRMSOS                       0x0000006C            /*  Offset correction for ISUMRMS calculation based on the sum of IA+IB+IC+/-IN */
#define ADDR_NIGAIN                          0x0000006D            /*  Neutral current gain adjust. */
#define ADDR_NPHCAL                          0x0000006E            /*  Neutral current phase compensation */
#define ADDR_NIRMSONEOS                      0x0000006F            /*  Neutral current rms offset for fast RMS1/2, NIRMSONE calculation */
#define ADDR_NIRMS1012OS                     0x00000070            /*  Neutral current rms offset for 10/12 cycle rms, NIRMS1012 calculation */
#define ADDR_VNOM                            0x00000071            /*  Nominal phase voltage rms used in the computation of apparent power, xVA, when VNOMx_EN bit is set in the CONFIG0 register */
#define ADDR_DICOEFF                         0x00000072            /*  Value used in the digital integrator algorithm. If the integrator is turned on, with INTEN or ININTEN equal to one in the CONFIG0 register, it is recommended to set this value to 0xFFFFE000. */
#define ADDR_ISUMLVL                         0x00000073            /*  Threshold to compare ISUMRMS against. Configure this register to get a MISMTCH indication in STATUS0 if ISUMRMS exceeds this threshold. */
#define ADDR_AI_PCF                          0x0000020A            /*  Instantaneous Phase A Current Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_AV_PCF                          0x0000020B            /*  Instantaneous Phase A Voltage Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_AIRMS                           0x0000020C            /*  Phase A Filter-based Current rms value, updates at 8ksps */
#define ADDR_AVRMS                           0x0000020D            /*  Phase A Filter-based Voltage rms value, updates at 8ksps */
#define ADDR_AIFRMS                          0x0000020E            /*  Phase A Current Fundamental rms, updates at 8ksps */
#define ADDR_AVFRMS                          0x0000020F            /*  Phase A Voltage Fundamental RMS, updates at 8ksps */
#define ADDR_AWATT                           0x00000210            /*  Phase A Low-pass filtered total active power, updated at 8ksps */
#define ADDR_AVAR                            0x00000211            /*  Phase A Low-pass filtered total reactive power, updated at 8ksps */
#define ADDR_AVA                             0x00000212            /*  Phase A Total apparent power, updated at 8ksps */
#define ADDR_AFWATT                          0x00000213            /*  Phase A Fundamental active power, updated at 8ksps */
#define ADDR_AFVAR                           0x00000214            /*  Phase A Fundamental reactive power, updated at 8ksps */
#define ADDR_AFVA                            0x00000215            /*  Phase A Fundamental apparent power, updated at 8ksps */
#define ADDR_APF                             0x00000216            /*  Phase A Power Factor, updated at 1.024s */
#define ADDR_AVTHD                           0x00000217            /*  Phase A Voltage Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_AITHD                           0x00000218            /*  Phase A Current Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_AIRMSONE                        0x00000219            /*  Phase A Current fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_AVRMSONE                        0x0000021A            /*  Phase A Voltage fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_AIRMS1012                       0x0000021B            /*  Phase A Current fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_AVRMS1012                       0x0000021C            /*  Phase A Voltage fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_AMTREGION                       0x0000021D            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which AIGAINx and APHCALx is currently being used */
#define ADDR_BI_PCF                          0x0000022A            /*  Instantaneous Phase B Current Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_BV_PCF                          0x0000022B            /*  Instantaneous Phase B Voltage Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_BIRMS                           0x0000022C            /*  Phase B Filter-based Current rms value, updates at 8ksps */
#define ADDR_BVRMS                           0x0000022D            /*  Phase B Filter-based Voltage rms value, updates at 8ksps */
#define ADDR_BIFRMS                          0x0000022E            /*  Phase B Current Fundamental rms, updates at 8ksps */
#define ADDR_BVFRMS                          0x0000022F            /*  Phase B Voltage Fundamental rms, updates at 8ksps */
#define ADDR_BWATT                           0x00000230            /*  Phase B Low-pass filtered total active power, updated at 8ksps */
#define ADDR_BVAR                            0x00000231            /*  Phase B Low-pass filtered total reactive power, updated at 8ksps */
#define ADDR_BVA                             0x00000232            /*  Phase B Total apparent power, updated at 8ksps */
#define ADDR_BFWATT                          0x00000233            /*  Phase B Fundamental active power, updated at 8ksps */
#define ADDR_BFVAR                           0x00000234            /*  Phase B Fundamental reactive power, updated at 8ksps */
#define ADDR_BFVA                            0x00000235            /*  Phase B Fundamental apparent power, updated at 8ksps */
#define ADDR_BPF                             0x00000236            /*  Phase B Power Factor, updated at 1.024s */
#define ADDR_BVTHD                           0x00000237            /*  Phase B Voltage Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_BITHD                           0x00000238            /*  Phase B Current Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_BIRMSONE                        0x00000239            /*  Phase B Current fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_BVRMSONE                        0x0000023A            /*  Phase B Voltage fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_BIRMS1012                       0x0000023B            /*  Phase B Current fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_BVRMS1012                       0x0000023C            /*  Phase B Voltage fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_BMTREGION                       0x0000023D            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the COFIG0 register, these bits indicate which BIGAINx and BPHCALx is currently being used */
#define ADDR_CI_PCF                          0x0000024A            /*  Instantaneous Phase C Current Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_CV_PCF                          0x0000024B            /*  Instantaneous Phase C Voltage Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_CIRMS                           0x0000024C            /*  Phase C Filter-based Current rms value, updates at 8ksps */
#define ADDR_CVRMS                           0x0000024D            /*  Phase C Filter-based Voltage rms value, updates at 8ksps */
#define ADDR_CIFRMS                          0x0000024E            /*  Phase C Current Fundamental rms, updates at 8ksps */
#define ADDR_CVFRMS                          0x0000024F            /*  Phase C Voltage Fundamental rms, updates at 8ksps */
#define ADDR_CWATT                           0x00000250            /*  Phase C Low-pass filtered total active power, updated at 8ksps */
#define ADDR_CVAR                            0x00000251            /*  Phase C Low-pass filtered total reactive power, updated at 8ksps */
#define ADDR_CVA                             0x00000252            /*  Phase C Total apparent power, updated at 8ksps */
#define ADDR_CFWATT                          0x00000253            /*  Phase C Fundamental active power, updated at 8ksps */
#define ADDR_CFVAR                           0x00000254            /*  Phase C Fundamental reactive power, updated at 8ksps */
#define ADDR_CFVA                            0x00000255            /*  Phase C Fundamental apparent power, updated at 8ksps */
#define ADDR_CPF                             0x00000256            /*  Phase C Power Factor, updated at 1.024s */
#define ADDR_CVTHD                           0x00000257            /*  Phase C Voltage Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_CITHD                           0x00000258            /*  Phase C Current Total Harmonic Distortion, THD, updated every 1.024s */
#define ADDR_CIRMSONE                        0x00000259            /*  Phase C Current fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_CVRMSONE                        0x0000025A            /*  Phase C Voltage fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_CIRMS1012                       0x0000025B            /*  Phase C Current fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_CVRMS1012                       0x0000025C            /*  Phase C Voltage fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_CMTREGION                       0x0000025D            /*  If multipoint gain and phase compensation is enabled, with MTEN = 1 in the CONFIG0 register, these bits indicate which CIGAINx and CPHCALx is currently being used */
#define ADDR_NI_PCF                          0x00000265            /*  Instantaneous Neutral Current Channel Waveform processed by the DSP, at 8ksps */
#define ADDR_NIRMS                           0x00000266            /*  Neutral Current Filter-based rms value */
#define ADDR_NIRMSONE                        0x00000267            /*  Neutral Current fast RMS1/2 calculation, one cycle rms updated every half-cycle */
#define ADDR_NIRMS1012                       0x00000268            /*  Neutral Current fast 10/12 cycle rms calculation.The calculation is done over 10 cycles if SELFREQ = 0 for a 50Hz network or 12 cycles if SELFREQ = 1 for a 60Hz network, in the ACCMODE register. */
#define ADDR_ISUMRMS                         0x00000269            /*  Filter-based RMS based on the sum of IA+IB+IC+/-IN */
#define ADDR_VERSION2                        0x0000026A            /*  This register indicates the version of the metrology algorithms after the user writes RUN=1 to start the measurements */
#define ADDR_AWATT_ACC                       0x000002E5            /*  Phase A accumulated total active power, updated after PWR_TIME 8ksps samples */
#define ADDR_AWATTHR_LO                      0x000002E6            /*  Phase A accumulated total active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AWATTHR_HI                      0x000002E7            /*  Phase A accumulated total active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AVAR_ACC                        0x000002EF            /*  Phase A accumulated total reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_AVARHR_LO                       0x000002F0            /*  Phase A accumulated total reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AVARHR_HI                       0x000002F1            /*  Phase A accumulated total reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AVA_ACC                         0x000002F9            /*  Phase A accumulated total apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_AVAHR_LO                        0x000002FA            /*  Phase A accumulated total apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AVAHR_HI                        0x000002FB            /*  Phase A accumulated total apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AFWATT_ACC                      0x00000303            /*  Phase A accumulated fundamental active power, updated after PWR_TIME 8ksps samples */
#define ADDR_AFWATTHR_LO                     0x00000304            /*  Phase A accumulated fundamental active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AFWATTHR_HI                     0x00000305            /*  Phase A accumulated fundamental active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers. */
#define ADDR_AFVAR_ACC                       0x0000030D            /*  Phase A accumulated fundamental reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_AFVARHR_LO                      0x0000030E            /*  Phase A accumulated fundamental reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AFVARHR_HI                      0x0000030F            /*  Phase A accumulated fundamental reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AFVA_ACC                        0x00000317            /*  Phase A accumulated fundamental apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_AFVAHR_LO                       0x00000318            /*  Phase A accumulated fundamental apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_AFVAHR_HI                       0x00000319            /*  Phase A accumulated fundamental apparent energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BWATT_ACC                       0x00000321            /*  Phase B accumulated total active power, updated after PWR_TIME 8ksps samples */
#define ADDR_BWATTHR_LO                      0x00000322            /*  Phase B accumulated total active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BWATTHR_HI                      0x00000323            /*  Phase B accumulated total active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BVAR_ACC                        0x0000032B            /*  Phase B accumulated total reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_BVARHR_LO                       0x0000032C            /*  Phase B accumulated total reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BVARHR_HI                       0x0000032D            /*  Phase B accumulated total reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BVA_ACC                         0x00000335            /*  Phase B accumulated total apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_BVAHR_LO                        0x00000336            /*  Phase B accumulated total apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BVAHR_HI                        0x00000337            /*  Phase B accumulated total apparent energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFWATT_ACC                      0x0000033F            /*  Phase B accumulated fundamental active power, updated after PWR_TIME 8ksps samples */
#define ADDR_BFWATTHR_LO                     0x00000340            /*  Phase B accumulated fundamental active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFWATTHR_HI                     0x00000341            /*  Phase B accumulated fundamental active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFVAR_ACC                       0x00000349            /*  Phase B accumulated fundamental reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_BFVARHR_LO                      0x0000034A            /*  Phase B accumulated fundamental reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFVARHR_HI                      0x0000034B            /*  Phase B accumulated fundamental reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFVA_ACC                        0x00000353            /*  Phase B accumulated fundamental apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_BFVAHR_LO                       0x00000354            /*  Phase B accumulated fundamental apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_BFVAHR_HI                       0x00000355            /*  Phase B accumulated fundamental apparent energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CWATT_ACC                       0x0000035D            /*  Phase C accumulated total active power, updated after PWR_TIME 8ksps samples */
#define ADDR_CWATTHR_LO                      0x0000035E            /*  Phase C accumulated total active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CWATTHR_HI                      0x0000035F            /*  Phase C accumulated total active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CVAR_ACC                        0x00000367            /*  Phase C accumulated total reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_CVARHR_LO                       0x00000368            /*  Phase C accumulated total reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CVARHR_HI                       0x00000369            /*  Phase C accumulated total reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CVA_ACC                         0x00000371            /*  Phase C accumulated total apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_CVAHR_LO                        0x00000372            /*  Phase C accumulated total apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CVAHR_HI                        0x00000373            /*  Phase C accumulated total apparent energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFWATT_ACC                      0x0000037B            /*  Phase C accumulated fundamental active power, updated after PWR_TIME 8ksps samples */
#define ADDR_CFWATTHR_LO                     0x0000037C            /*  Phase C accumulated fundamental active energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFWATTHR_HI                     0x0000037D            /*  Phase C accumulated fundamental active energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFVAR_ACC                       0x00000385            /*  Phase C accumulated fundamental reactive power, updated after PWR_TIME 8ksps samples */
#define ADDR_CFVARHR_LO                      0x00000386            /*  Phase C accumulated fundamental reactive energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFVARHR_HI                      0x00000387            /*  Phase C accumulated fundamental reactive energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFVA_ACC                        0x0000038F            /*  Phase C accumulated fundamental apparent power, updated after PWR_TIME 8ksps samples */
#define ADDR_CFVAHR_LO                       0x00000390            /*  Phase C accumulated fundamental apparent energy, Least Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_CFVAHR_HI                       0x00000391            /*  Phase C accumulated fundamental apparent energy, Most Significant Bits. Updated according to the settings in EP_CFG and EGY_TIME registers */
#define ADDR_PWATT_ACC                       0x00000397            /*  Accumulated Positive Total Active Power, Most Significant Bits, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 8ksps samples */
#define ADDR_NWATT_ACC                       0x0000039B            /*  Accumulated Negative Total Active Power, Most Significant Bits, from AWATT, BWATT and CWATT registers, updated after PWR_TIME 8ksps samples */
#define ADDR_PVAR_ACC                        0x0000039F            /*  Accumulated Positive Total Reactive Power, Most Significant Bits, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 8ksps samples */
#define ADDR_NVAR_ACC                        0x000003A3            /*  Accumulated Negative Total Reactive Power, Most Significant Bits, from AVAR, BVAR and CVAR registers, updated after PWR_TIME 8ksps samples */
#define ADDR_IPEAK                           0x00000400            /*  Current peak register */
#define ADDR_VPEAK                           0x00000401            /*  Voltage peak register */
#define ADDR_STATUS0                         0x00000402            /*  Status Register 0 */
#define ADDR_STATUS1                         0x00000403            /*  Status Register 1 */
#define ADDR_EVENT_STATUS                    0x00000404            /*  Event Status Register */
#define ADDR_MASK0                           0x00000405            /*  Interrupt Enable Register 0 */
#define ADDR_MASK1                           0x00000406            /*  Interrupt Enable Register 1 */
#define ADDR_EVENT_MASK                      0x00000407            /*  Event Enable Register */
#define ADDR_OILVL                           0x00000409            /*  Over current detection threshold level */
#define ADDR_OIA                             0x0000040A            /*  Phase A overcurrent RMS 1/2 value. If a phase is enabled, with the OC_ENA bit set in the CONFIG3 register and the AIRMSONE is greater than the OILVL threshold then this value is updated. */
#define ADDR_OIB                             0x0000040B            /*  Phase B overcurrent RMS 1/2 value. If a phase is enabled, with the OC_ENB bit set in the CONFIG3 register and the BIRMSONE is greater than the OILVL threshold then this value is updated. */
#define ADDR_OIC                             0x0000040C            /*  Phase C overcurrent RMS 1/2 value. If a phase is enabled, with the OC_ENC bit set in the CONFIG3 register and the CIRMSONE is greater than the OILVL threshold then this value is updated. */
#define ADDR_OIN                             0x0000040D            /*  Neutral Current overcurrent RMS 1/2 value. If enabled, with the OC_ENN bit set in the CONFIG3 register and the NIRMSONE is greater than the OILVL threshold then this value is updated. */
#define ADDR_USER_PERIOD                     0x0000040E            /*  User configured line period value used for resampling, fast rms 1/2 and 10/12 cycle rms when the UPERIOD_SEL bit in the CONFIG2 register is set */
#define ADDR_VLEVEL                          0x0000040F            /*  Register used in the algorithm that computes the fundamental active, reactive and apparent powers as well as the fundemantal IRMS and VRMS */
#define ADDR_DIP_LVL                         0x00000410            /*  Voltage RMS1/2 Dip detection threshold level. */
#define ADDR_DIPA                            0x00000411            /*  Phase A Voltage RMS 1/2 value during a dip condition. */
#define ADDR_DIPB                            0x00000412            /*  Phase B Voltage RMS 1/2 value during a dip condition. */
#define ADDR_DIPC                            0x00000413            /*  Phase C Voltage RMS 1/2 value during a dip condition. */
#define ADDR_SWELL_LVL                       0x00000414            /*  Voltage RMS1/2 Swell detection threshold level. */
#define ADDR_SWELLA                          0x00000415            /*  Phase A Voltage RMS 1/2 value during a swell condition. */
#define ADDR_SWELLB                          0x00000416            /*  Phase B Voltage RMS 1/2 value during a swell condition. */
#define ADDR_SWELLC                          0x00000417            /*  Phase C Voltage RMS 1/2 value during a swell condition. */
#define ADDR_APERIOD                         0x00000418            /*  Line period on Phase A voltage */
#define ADDR_BPERIOD                         0x00000419            /*  Line period on Phase B voltage */
#define ADDR_CPERIOD                         0x0000041A            /*  Line period on Phase C voltage */
#define ADDR_COM_PERIOD                      0x0000041B            /*  Line period measurement on combined signal from Phase A, B, C Voltages */
#define ADDR_ACT_NL_LVL                      0x0000041C            /*  No-load threshold in the total and fundamental active power datapath. */
#define ADDR_REACT_NL_LVL                    0x0000041D            /*  No-load threshold in the total and fundamental reactive power datapath. */
#define ADDR_APP_NL_LVL                      0x0000041E            /*  No-load threshold in the total and fundamental apparent power datapath. */
#define ADDR_PHNOLOAD                        0x0000041F            /*  Phase No-load register */
#define ADDR_WTHR                            0x00000420            /*  Sets the maximum output rate from the digital to frequency converter for the total and fundamental active power for the CF calibration pulse output. It is recommended to write WTHR = 0x0010_0000. */
#define ADDR_VARTHR                          0x00000421            /*  Sets the maximum output rate from the digital to frequency converter for the total and fundamental reactive power for the CF calibration pulse output. It is recommended to write VARTHR = 0x0010_0000. */
#define ADDR_VATHR                           0x00000422            /*  Sets the maximum output rate from the digital to frequency converter for the total and fundamental apparent power for the CF calibration pulse output. It is recommended to write VATHR = 0x0010_0000. */
#define ADDR_LAST_DATA_32                    0x00000423            /*  This register holds the data read or written during the last 32-bit transaction on the SPI port */
#define ADDR_ADC_REDIRECT                    0x00000424            /*  This register allows any ADC output to be redirected to any digital datapath */
#define ADDR_CF_LCFG                         0x00000425            /*  CF calibration pulse width configuration register */
#define ADDR_TEMP_TRIM                       0x00000474            /*  Temperature sensor gain and offset, calculated during the manufacturing process */
#define ADDR_RUN                             0x00000480            /*  Write this register to 1 to start the measurements. */
#define ADDR_CONFIG1                         0x00000481            /*  Configuration register 1 */
#define ADDR_ANGL_VA_VB                      0x00000482            /*  Time between positive to negative zero crossings on Phase A and Phase B Voltages */
#define ADDR_ANGL_VB_VC                      0x00000483            /*  Time between positive to negative zero crossings on Phase B and Phase C Voltages */
#define ADDR_ANGL_VA_VC                      0x00000484            /*  Time between positive to negative zero crossings on Phase A and Phase C Voltages */
#define ADDR_ANGL_VA_IA                      0x00000485            /*  Time between positive to negative zero crossings on Phase A Voltage and Current */
#define ADDR_ANGL_VB_IB                      0x00000486            /*  Time between positive to negative zero crossings on Phase B Voltage and Current */
#define ADDR_ANGL_VC_IC                      0x00000487            /*  Time between positive to negative zero crossings on Phase C Voltage and Current */
#define ADDR_ANGL_IA_IB                      0x00000488            /*  Time between positive to negative zero crossings on Phase A and Phase B Current */
#define ADDR_ANGL_IB_IC                      0x00000489            /*  Time between positive to negative zero crossings on Phase B and Phase C Current */
#define ADDR_ANGL_IA_IC                      0x0000048A            /*  Time between positive to negative zero crossings on Phase A and Phase C Current */
#define ADDR_DIP_CYC                         0x0000048B            /*  Voltage RMS1/2 Dip detection cycle configuration. */
#define ADDR_SWELL_CYC                       0x0000048C            /*  Voltage RMS1/2 Swell detection cycle configuration. */
#define ADDR_OISTATUS                        0x0000048F            /*  Overcurrent Status register */
#define ADDR_CFMODE                          0x00000490            /*  CFx configuration register */
#define ADDR_COMPMODE                        0x00000491            /*  Computation mode register */
#define ADDR_ACCMODE                         0x00000492            /*  Accumulation mode register */
#define ADDR_CONFIG3                         0x00000493            /*  Configuration register 3 */
#define ADDR_CF1DEN                          0x00000494            /*  CF1 denominator register. */
#define ADDR_CF2DEN                          0x00000495            /*  CF2 denominator register. */
#define ADDR_CF3DEN                          0x00000496            /*  CF3 denominator register. */
#define ADDR_CF4DEN                          0x00000497            /*  CF4 denominator register. */
#define ADDR_ZXTOUT                          0x00000498            /*  Zero-crossing timeout configuration register */
#define ADDR_ZXTHRSH                         0x00000499            /*  Voltage Channel Zero-crossing threshold register */
#define ADDR_ZX_LP_SEL                       0x0000049A            /*  This register selects which zero crossing and which line period measurement are used for other calculations */
#define ADDR_SEQ_CYC                         0x0000049C            /*  Number of line cycles used for phase sequence detection. It is recommended to set this register to 1. */
#define ADDR_PHSIGN                          0x0000049D            /*  Power sign register */
#define ADDR_WFB_CFG                         0x000004A0            /*  Waveform Buffer Configuration register */
#define ADDR_WFB_PG_IRQEN                    0x000004A1            /*  This register enables interrupts to occur after specific pages of the waveform buffer have been filled */
#define ADDR_WFB_TRG_CFG                     0x000004A2            /*  This register enables events to trigger a capture in the waveform buffer */
#define ADDR_WFB_TRG_STAT                    0x000004A3            /*  This register indicates the last page which was filled in the waveform buffer and the location of trigger events */
#define ADDR_CONFIG5                         0x000004A4            /*  Configuration register 5 */
#define ADDR_CRC_RSLT                        0x000004A8            /*  This register holds the CRC of configuration registers */
#define ADDR_CRC_SPI                         0x000004A9            /*  This register holds the 16-bit CRC of the data sent out on the MOSI pin during the last SPI register read */
#define ADDR_LAST_DATA_16                    0x000004AC            /*  This register holds the data read or written during the last 16-bit transaction on the SPI port */
#define ADDR_LAST_CMD                        0x000004AE            /*  This register holds the address and read/write operation request (CMD_HDR) for the last transaction on the SPI port */
#define ADDR_CONFIG2                         0x000004AF            /*  Configuration register 2 */
#define ADDR_EP_CFG                          0x000004B0            /*  Energy and power accumulation configuration */
#define ADDR_PWR_TIME                        0x000004B1            /*  Power Update time configuration */
#define ADDR_EGY_TIME                        0x000004B2            /*  Energy accumulation update time configuration */
#define ADDR_CRC_FORCE                       0x000004B4            /*  This register forces an update of the CRC of configuration registers */
#define ADDR_CRC_OPTEN                       0x000004B5            /*  This register selects which registers are optionally included in the configuration register CRC feature */
#define ADDR_TEMP_CFG                        0x000004B6            /*  Temperature sensor configuration register */
#define ADDR_TEMP_RSLT                       0x000004B7            /*  Temperature measurement result */
#define ADDR_PSM2_CFG                        0x000004B8            /*  This register configures settings for the low power PSM2 operating mode. This register value is retained in PSM2 and PSM3 but is rewritten to its default value when entering PSM0. */
#define ADDR_PGA_GAIN                        0x000004B9            /*  This register configures the PGA gain for each ADC */
#define ADDR_CHNL_DIS                        0x000004BA            /*  ADC Channel Enable/Disable */
#define ADDR_WR_LOCK                         0x000004BF            /*  This register enables the configuration lock feature */
#define ADDR_VAR_DIS                         0x000004E0            /*  Enable/disable total reactive power calculation */
#define ADDR_RESERVED1                       0x000004F0            /*  This register is reserved. */
#define ADDR_VERSION                         0x000004FE            /*  Version of ADE9000 IC */
#define ADDR_AI_SINC_DAT                     0x00000500            /*  Current channel A ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_AV_SINC_DAT                     0x00000501            /*  Voltage channel A ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_BI_SINC_DAT                     0x00000502            /*  Current channel B ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_BV_SINC_DAT                     0x00000503            /*  Voltage channel B ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_CI_SINC_DAT                     0x00000504            /*  Current channel C ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_CV_SINC_DAT                     0x00000505            /*  Voltage channel C ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_NI_SINC_DAT                     0x00000506            /*  Neutral current channel ADC waveforms from Sinc4 output, at 32ksps */
#define ADDR_AI_LPF_DAT                      0x00000510            /*  Current channel A ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_AV_LPF_DAT                      0x00000511            /*  Voltage channel A ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_BI_LPF_DAT                      0x00000512            /*  Current channel B ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_BV_LPF_DAT                      0x00000513            /*  Voltage channel B ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_CI_LPF_DAT                      0x00000514            /*  Current channel C ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_CV_LPF_DAT                      0x00000515            /*  Voltage channel C ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_NI_LPF_DAT                      0x00000516            /*  Neutral current channel ADC waveforms from Sinc4 + IIR LPF output, at 8ksps */
#define ADDR_AV_PCF_1                        0x00000600            /*  SPI Burst Read Accessible. Registers organized functionally. See AV_PCF. */
#define ADDR_BV_PCF_1                        0x00000601            /*  SPI Burst Read Accessible. Registers organized functionally. See BV_PCF. */
#define ADDR_CV_PCF_1                        0x00000602            /*  SPI Burst Read Accessible. Registers organized functionally. See CV_PCF. */
#define ADDR_NI_PCF_1                        0x00000603            /*  SPI Burst Read Accessible. Registers organized functionally. See NI_PCF. */
#define ADDR_AI_PCF_1                        0x00000604            /*  SPI Burst Read Accessible. Registers organized functionally. See AI_PCF. */
#define ADDR_BI_PCF_1                        0x00000605            /*  SPI Burst Read Accessible. Registers organized functionally. See BI_PCF. */
#define ADDR_CI_PCF_1                        0x00000606            /*  SPI Burst Read Accessible. Registers organized functionally. See CI_PCF. */
#define ADDR_AIRMS_1                         0x00000607            /*  SPI Burst Read Accessible. Registers organized functionally. See AIRMS. */
#define ADDR_BIRMS_1                         0x00000608            /*  SPI Burst Read Accessible. Registers organized functionally. See BIRMS. */
#define ADDR_CIRMS_1                         0x00000609            /*  SPI Burst Read Accessible. Registers organized functionally. See CIRMS. */
#define ADDR_AVRMS_1                         0x0000060A            /*  SPI Burst Read Accessible. Registers organized functionally. See AVRMS. */
#define ADDR_BVRMS_1                         0x0000060B            /*  SPI Burst Read Accessible. Registers organized functionally. See BVRMS. */
#define ADDR_CVRMS_1                         0x0000060C            /*  SPI Burst Read Accessible. Registers organized functionally. See CVRMS. */
#define ADDR_NIRMS_1                         0x0000060D            /*  SPI Burst Read Accessible. Registers organized functionally. See NIRMS. */
#define ADDR_AWATT_1                         0x0000060E            /*  SPI Burst Read Accessible. Registers organized functionally. See AWATT. */
#define ADDR_BWATT_1                         0x0000060F            /*  SPI Burst Read Accessible. Registers organized functionally. See BWATT. */
#define ADDR_CWATT_1                         0x00000610            /*  SPI Burst Read Accessible. Registers organized functionally. See CWATT. */
#define ADDR_AVA_1                           0x00000611            /*  SPI Burst Read Accessible. Registers organized functionally. See AVA. */
#define ADDR_BVA_1                           0x00000612            /*  SPI Burst Read Accessible. Registers organized functionally. See BVA. */
#define ADDR_CVA_1                           0x00000613            /*  SPI Burst Read Accessible. Registers organized functionally. See CVA. */
#define ADDR_AVAR_1                          0x00000614            /*  SPI Burst Read Accessible. Registers organized functionally. See AVAR. */
#define ADDR_BVAR_1                          0x00000615            /*  SPI Burst Read Accessible. Registers organized functionally. See BVAR. */
#define ADDR_CVAR_1                          0x00000616            /*  SPI Burst Read Accessible. Registers organized functionally. See CVAR. */
#define ADDR_AFVAR_1                         0x00000617            /*  SPI Burst Read Accessible. Registers organized functionally. See AFVAR. */
#define ADDR_BFVAR_1                         0x00000618            /*  SPI Burst Read Accessible. Registers organized functionally. See BFVAR. */
#define ADDR_CFVAR_1                         0x00000619            /*  SPI Burst Read Accessible. Registers organized functionally. See CFVAR. */
#define ADDR_APF_1                           0x0000061A            /*  SPI Burst Read Accessible. Registers organized functionally. See APF. */
#define ADDR_BPF_1                           0x0000061B            /*  SPI Burst Read Accessible. Registers organized functionally. See BPF. */
#define ADDR_CPF_1                           0x0000061C            /*  SPI Burst Read Accessible. Registers organized functionally. See CPF. */
#define ADDR_AVTHD_1                         0x0000061D            /*  SPI Burst Read Accessible. Registers organized functionally. See AVTHD. */
#define ADDR_BVTHD_1                         0x0000061E            /*  SPI Burst Read Accessible. Registers organized functionally. See BVTHD. */
#define ADDR_CVTHD_1                         0x0000061F            /*  SPI Burst Read Accessible. Registers organized functionally. See CVTHD. */
#define ADDR_AITHD_1                         0x00000620            /*  SPI Burst Read Accessible. Registers organized functionally. See AITHD. */
#define ADDR_BITHD_1                         0x00000621            /*  SPI Burst Read Accessible. Registers organized functionally. See BITHD. */
#define ADDR_CITHD_1                         0x00000622            /*  SPI Burst Read Accessible. Registers organized functionally. See CITHD. */
#define ADDR_AFWATT_1                        0x00000623            /*  SPI Burst Read Accessible. Registers organized functionally. See AFWATT. */
#define ADDR_BFWATT_1                        0x00000624            /*  SPI Burst Read Accessible. Registers organized functionally. See BFWATT. */
#define ADDR_CFWATT_1                        0x00000625            /*  SPI Burst Read Accessible. Registers organized functionally. See CFWATT. */
#define ADDR_AFVA_1                          0x00000626            /*  SPI Burst Read Accessible. Registers organized functionally. See AFVA. */
#define ADDR_BFVA_1                          0x00000627            /*  SPI Burst Read Accessible. Registers organized functionally. See BFVA. */
#define ADDR_CFVA_1                          0x00000628            /*  SPI Burst Read Accessible. Registers organized functionally. See CFVA. */
#define ADDR_AFIRMS_1                        0x00000629            /*  SPI Burst Read Accessible. Registers organized functionally. See AFIRMS. */
#define ADDR_BFIRMS_1                        0x0000062A            /*  SPI Burst Read Accessible. Registers organized functionally. See BFIRMS. */
#define ADDR_CFIRMS_1                        0x0000062B            /*  SPI Burst Read Accessible. Registers organized functionally. See CFIRMS. */
#define ADDR_AFVRMS_1                        0x0000062C            /*  SPI Burst Read Accessible. Registers organized functionally. See AFVRMS. */
#define ADDR_BFVRMS_1                        0x0000062D            /*  SPI Burst Read Accessible. Registers organized functionally. See BFVRMS. */
#define ADDR_CFVRMS_1                        0x0000062E            /*  SPI Burst Read Accessible. Registers organized functionally. See CFVRMS. */
#define ADDR_AIRMSONE_1                      0x0000062F            /*  SPI Burst Read Accessible. Registers organized functionally. See AIRMSONE. */
#define ADDR_BIRMSONE_1                      0x00000630            /*  SPI Burst Read Accessible. Registers organized functionally. See BIRMSONE. */
#define ADDR_CIRMSONE_1                      0x00000631            /*  SPI Burst Read Accessible. Registers organized functionally. See CIRMSONE. */
#define ADDR_AVRMSONE_1                      0x00000632            /*  SPI Burst Read Accessible. Registers organized functionally. See AVRMSONE. */
#define ADDR_BVRMSONE_1                      0x00000633            /*  SPI Burst Read Accessible. Registers organized functionally. See BVRMSONE. */
#define ADDR_CVRMSONE_1                      0x00000634            /*  SPI Burst Read Accessible. Registers organized functionally. See CVRMSONE. */
#define ADDR_NIRMSONE_1                      0x00000635            /*  SPI Burst Read Accessible. Registers organized functionally. See NIRMSONE. */
#define ADDR_AIRMS1012_1                     0x00000636            /*  SPI Burst Read Accessible. Registers organized functionally. See AIRMS1012. */
#define ADDR_BIRMS1012_1                     0x00000637            /*  SPI Burst Read Accessible. Registers organized functionally. See BIRMS1012. */
#define ADDR_CIRMS1012_1                     0x00000638            /*  SPI Burst Read Accessible. Registers organized functionally. See CIRMS1012. */
#define ADDR_AVRMS1012_1                     0x00000639            /*  SPI Burst Read Accessible. Registers organized functionally. See AVRMS1012. */
#define ADDR_BVRMS1012_1                     0x0000063A            /*  SPI Burst Read Accessible. Registers organized functionally. See BVRMS1012. */
#define ADDR_CVRMS1012_1                     0x0000063B            /*  SPI Burst Read Accessible. Registers organized functionally. See CVRMS1012. */
#define ADDR_NIRMS1012_1                     0x0000063C            /*  SPI Burst Read Accessible. Registers organized functionally. See NIRMS1012. */
#define ADDR_AV_PCF_2                        0x00000680            /*  SPI Burst Read Accessible. Registers organized by phase. See AV_PCF. */
#define ADDR_AI_PCF_2                        0x00000681            /*  SPI Burst Read Accessible. Registers organized by phase. See AI_PCF. */
#define ADDR_AIRMS_2                         0x00000682            /*  SPI Burst Read Accessible. Registers organized by phase. See AIRMS. */
#define ADDR_AVRMS_2                         0x00000683            /*  SPI Burst Read Accessible. Registers organized by phase. See AVRMS. */
#define ADDR_AWATT_2                         0x00000684            /*  SPI Burst Read Accessible. Registers organized by phase. See AWATT. */
#define ADDR_AVA_2                           0x00000685            /*  SPI Burst Read Accessible. Registers organized by phase. See AVA. */
#define ADDR_AVAR_2                          0x00000686            /*  SPI Burst Read Accessible. Registers organized by phase. See AVAR. */
#define ADDR_AFVAR_2                         0x00000687            /*  SPI Burst Read Accessible. Registers organized by phase. See AFVAR. */
#define ADDR_APF_2                           0x00000688            /*  SPI Burst Read Accessible. Registers organized by phase. See APF. */
#define ADDR_AVTHD_2                         0x00000689            /*  SPI Burst Read Accessible. Registers organized by phase. See AVTHD. */
#define ADDR_AITHD_2                         0x0000068A            /*  SPI Burst Read Accessible. Registers organized by phase. See AITHD. */
#define ADDR_AFWATT_2                        0x0000068B            /*  SPI Burst Read Accessible. Registers organized by phase. See AFWATT. */
#define ADDR_AFVA_2                          0x0000068C            /*  SPI Burst Read Accessible. Registers organized by phase. See AFVA. */
#define ADDR_AFIRMS_2                        0x0000068D            /*  SPI Burst Read Accessible. Registers organized by phase. See AFIRMS. */
#define ADDR_AFVRMS_2                        0x0000068E            /*  SPI Burst Read Accessible. Registers organized by phase. See AFVRMS. */
#define ADDR_AIRMSONE_2                      0x0000068F            /*  SPI Burst Read Accessible. Registers organized by phase. See AIRMSONE. */
#define ADDR_AVRMSONE_2                      0x00000690            /*  SPI Burst Read Accessible. Registers organized by phase. See AVRMSONE. */
#define ADDR_AIRMS1012_2                     0x00000691            /*  SPI Burst Read Accessible. Registers organized by phase. See AIRMS1012. */
#define ADDR_AVRMS1012_2                     0x00000692            /*  SPI Burst Read Accessible. Registers organized by phase. See AVRMS1012. */
#define ADDR_BV_PCF_2                        0x00000693            /*  SPI Burst Read Accessible. Registers organized by phase. See BV_PCF. */
#define ADDR_BI_PCF_2                        0x00000694            /*  SPI Burst Read Accessible. Registers organized by phase. See BI_PCF. */
#define ADDR_BIRMS_2                         0x00000695            /*  SPI Burst Read Accessible. Registers organized by phase. See BIRMS. */
#define ADDR_BVRMS_2                         0x00000696            /*  SPI Burst Read Accessible. Registers organized by phase. See BVRMS. */
#define ADDR_BWATT_2                         0x00000697            /*  SPI Burst Read Accessible. Registers organized by phase. See BWATT. */
#define ADDR_BVA_2                           0x00000698            /*  SPI Burst Read Accessible. Registers organized by phase. See BVA. */
#define ADDR_BVAR_2                          0x00000699            /*  SPI Burst Read Accessible. Registers organized by phase. See BVAR. */
#define ADDR_BFVAR_2                         0x0000069A            /*  SPI Burst Read Accessible. Registers organized by phase. See BFVAR. */
#define ADDR_BPF_2                           0x0000069B            /*  SPI Burst Read Accessible. Registers organized by phase. See BPF. */
#define ADDR_BVTHD_2                         0x0000069C            /*  SPI Burst Read Accessible. Registers organized by phase. See BVTHD. */
#define ADDR_BITHD_2                         0x0000069D            /*  SPI Burst Read Accessible. Registers organized by phase. See BITHD. */
#define ADDR_BFWATT_2                        0x0000069E            /*  SPI Burst Read Accessible. Registers organized by phase. See BFWATT. */
#define ADDR_BFVA_2                          0x0000069F            /*  SPI Burst Read Accessible. Registers organized by phase. See BFVA. */
#define ADDR_BFIRMS_2                        0x000006A0            /*  SPI Burst Read Accessible. Registers organized by phase. See BFIRMS. */
#define ADDR_BFVRMS_2                        0x000006A1            /*  SPI Burst Read Accessible. Registers organized by phase. See BFVRMS. */
#define ADDR_BIRMSONE_2                      0x000006A2            /*  SPI Burst Read Accessible. Registers organized by phase. See BIRMSONE. */
#define ADDR_BVRMSONE_2                      0x000006A3            /*  SPI Burst Read Accessible. Registers organized by phase. See BVRMSONE. */
#define ADDR_BIRMS1012_2                     0x000006A4            /*  SPI Burst Read Accessible. Registers organized by phase. See BIRMS1012. */
#define ADDR_BVRMS1012_2                     0x000006A5            /*  SPI Burst Read Accessible. Registers organized by phase. See BVRMS1012. */
#define ADDR_CV_PCF_2                        0x000006A6            /*  SPI Burst Read Accessible. Registers organized by phase. See CV_PCF. */
#define ADDR_CI_PCF_2                        0x000006A7            /*  SPI Burst Read Accessible. Registers organized by phase. See CI_PCF. */
#define ADDR_CIRMS_2                         0x000006A8            /*  SPI Burst Read Accessible. Registers organized by phase. See CIRMS. */
#define ADDR_CVRMS_2                         0x000006A9            /*  SPI Burst Read Accessible. Registers organized by phase. See CVRMS. */
#define ADDR_CWATT_2                         0x000006AA            /*  SPI Burst Read Accessible. Registers organized by phase. See CWATT. */
#define ADDR_CVA_2                           0x000006AB            /*  SPI Burst Read Accessible. Registers organized by phase. See CVA. */
#define ADDR_CVAR_2                          0x000006AC            /*  SPI Burst Read Accessible. Registers organized by phase. See CVAR. */
#define ADDR_CFVAR_2                         0x000006AD            /*  SPI Burst Read Accessible. Registers organized by phase. See CFVAR. */
#define ADDR_CPF_2                           0x000006AE            /*  SPI Burst Read Accessible. Registers organized by phase. See CPF. */
#define ADDR_CVTHD_2                         0x000006AF            /*  SPI Burst Read Accessible. Registers organized by phase. See CVTHD. */
#define ADDR_CITHD_2                         0x000006B0            /*  SPI Burst Read Accessible. Registers organized by phase. See CITHD. */
#define ADDR_CFWATT_2                        0x000006B1            /*  SPI Burst Read Accessible. Registers organized by phase. See CFWATT. */
#define ADDR_CFVA_2                          0x000006B2            /*  SPI Burst Read Accessible. Registers organized by phase. See CFVA. */
#define ADDR_CFIRMS_2                        0x000006B3            /*  SPI Burst Read Accessible. Registers organized by phase. See CFIRMS. */
#define ADDR_CFVRMS_2                        0x000006B4            /*  SPI Burst Read Accessible. Registers organized by phase. See CFVRMS. */
#define ADDR_CIRMSONE_2                      0x000006B5            /*  SPI Burst Read Accessible. Registers organized by phase. See CIRMSONE. */
#define ADDR_CVRMSONE_2                      0x000006B6            /*  SPI Burst Read Accessible. Registers organized by phase. See CVRMSONE. */
#define ADDR_CIRMS1012_2                     0x000006B7            /*  SPI Burst Read Accessible. Registers organized by phase. See CIRMS1012. */
#define ADDR_CVRMS1012_2                     0x000006B8            /*  SPI Burst Read Accessible. Registers organized by phase. See CVRMS1012. */
#define ADDR_NI_PCF_2                        0x000006B9            /*  SPI Burst Read Accessible. Registers organized by phase. See NI_PCF. */
#define ADDR_NIRMS_2                         0x000006BA            /*  SPI Burst Read Accessible. Registers organized by phase. See NIRMS. */
#define ADDR_NIRMSONE_2                      0x000006BB            /*  SPI Burst Read Accessible. Registers organized by phase. See NIRMSONE. */
#define ADDR_NIRMS1012_2                     0x000006BC            /*  SPI Burst Read Accessible. Registers organized by phase. See NIRMS1012. */



