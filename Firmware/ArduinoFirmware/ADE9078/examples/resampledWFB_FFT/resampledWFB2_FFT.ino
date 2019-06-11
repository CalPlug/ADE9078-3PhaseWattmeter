//Resampled Wave form buffer for ADE9078 to read and report values (ADE9078_TEST)
//California Plug Load Research Center - 2019
//Enoch Chau 2019


#include <ADE9078.h>
#include <SPI.h>
#include "arduinoFFT.h"

// Use VSPI pins for ESP32 SPI
// MOSI	GPIO 23
// MISO	GPIO 19
// SCLK	GPIO 18
// CS/SS	GPIO 5
//
// If you get a core dumped error do the following:
// In: ../Documents/Arduino/hardware/espressif/esp32/cores/esp32/main.cpp
// Increase the stack size. In my hardware files I found that it was already 8192 so I made it 16384.
//
// Source: https://github.com/espressif/arduino-esp32/issues/523

//Architecture Control:
//Make sure you select in the ADE9078.h file the proper board architecture, either Arduino/AVR/ESP8266 or ESP32
//REMINDER: ONLY SELECT THE SINGLE OPTION FOR THE BOARD TYPE YOU ARE USING!
#define ESP32ARCH

//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 115200  //Set SPI_Freq at 1MHz
#define local_SS 5//VSPI SS pin for SPI communication

//****WFB settings********
#define WFB_ALL_SEGMENTS 512
#define BURST_MEMORY_BASE 0x801 //It may seem like the starting register is 0x800 but use 0x801 instead

arduinoFFT FFT = arduinoFFT();

#define SAMPLES 64             //FFT Total samples input - Must be a power of 2
unsigned int sampling_period_us;  //holder for microseconds for FFT
#define SAMPLING_FREQUENCY 60 //Hz, match rate to match sampling frequency for input data from data source

//Read, re-sample, process, report flow control
bool SampleBufferFilled = 0; //Used to indicate when the buffer has been filled and is ready for readout, ready to be read out
bool FFTCalculationComplete = 0; //Flow control for readout of values
bool FFTInputBufferFilled = 0; //Flow control for readout of values


//Declare object for buffer & FFT values to be received
struct FullResample
{
    int16_t Ia[WFB_ALL_SEGMENTS];
    int16_t Va[WFB_ALL_SEGMENTS];
    int16_t Ib[WFB_ALL_SEGMENTS];
    int16_t Vb[WFB_ALL_SEGMENTS];
    int16_t Ic[WFB_ALL_SEGMENTS];
    int16_t Vc[WFB_ALL_SEGMENTS];
    int16_t In[WFB_ALL_SEGMENTS];
};

struct FFTDataHolder  //this is the holder for the inputs and the FFT returns
	{
		double vRealPhaseAv[SAMPLES]; //holder for Real (frequency values): Phase A, Voltage
		double vImagPhaseAv[SAMPLES];  //holder for Img. (Phase values): Phase A, Voltage

		double vRealPhaseAi[SAMPLES]; //holder for Real (frequency values): Phase A, Current
		double vImagPhaseAi[SAMPLES];  //holder for Img. (Phase values): Phase A, Current
		//
		double vRealPhaseBv[SAMPLES]; //holder for Real (frequency values): Phase B, Voltage
		double vImagPhaseBv[SAMPLES];  //holder for Img. (Phase values): Phase B, Voltage

		double vRealPhaseBi[SAMPLES]; //holder for Real (frequency values): Phase B, Current
		double vImagPhaseBi[SAMPLES];  //holder for Img. (Phase values): Phase B, Current

		double vRealPhaseCv[SAMPLES]; //holder for Real (frequency values): Phase C, Voltage
		double vImagPhaseCv[SAMPLES];  //holder for Img. (Phase values): Phase C, Voltage

		double vRealPhaseCi[SAMPLES]; //holder for Real (frequency values): Phase C, Current
		double vImagPhaseCi[SAMPLES];  //holder for Img. (Phase values): Phase C, Current

		double vRealPhaseNi[SAMPLES]; //holder for Real (frequency values): Neutral, Current
		double vImagPhaseNi[SAMPLES];  //holder for Img. (Phase values): Neutral, Current
};

const int readCount = WFB_ALL_SEGMENTS/WFB_RESAMPLE_SEGMENTS; //==8

struct InitializationSettings* is = new InitializationSettings; //define structure for initialized values

ADE9078 myADE9078(local_SS, local_SPI_freq, is); // Call the ADE9078 Object with hardware parameters specified, local variables are copied to private variables inside the class when object is created.


//esp32 arch for spi
SPIClass * vspi = NULL;

void setup() {

	//Need to add:
	//1)Read in EEPROM values, check the "Configured bit", if 1, display, calibration values available, load these calibration values to the ADE9078's RAM
	//2)If 0, then display that no calibration values are present and load default values (Tell user to run calibration firmware)
	//3) Proceed with load and operation of this demo
  Serial.begin(115200);
  delay(200);
  is->vAGain=1;
  is->vBGain=1;
  is->vCGain=1;

  is->iAGain=1;
  is->iBGain=1;
  is->iCGain=1;
  is->iNGain=1;

  is->powerAGain=1;
  is->powerBGain=1;
  is->powerCGain=1;

  //Use these settings to configure wiring configuration at stertup
  //FYI: B010=2 in DEC
  //FYI: B100 = 4 in DEC

	//4 Wire Wye configuration - non-Blondel compliant:
	is->vConsel=0;
	is->iConsel=0;

	//Delta, Blondel compliant:
	//is->vConsel=4; //byte value of 100,
	//is->iConsel=0;


	//Please continue for all cases
  //SPI.begin(); //Arduino uno
  delay(200);
  myADE9078.initialize(); //Call initialization of the ADE9078 withe default configuration plus options specified
	//EEPROMInit()  //call only once on a virgin chip to "partition" EEPROM for the input type expected moving forward
	//load_data_allfields();  //load EEPROM values
  delay(200);
  //CONFIGURE WFB
  myADE9078.configureWFB();
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));  //calculate the sampling period in microseconds for the FFT, relative to 1 MHZ
}


void loop() {
  FFTDataHolder fftData;
  arduinoFFT AvFFT = arduinoFFT(fftData.vRealPhaseAv, fftData.vImagPhaseAv, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT AiFFT = arduinoFFT(fftData.vRealPhaseAi, fftData.vImagPhaseAi, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT BvFFT = arduinoFFT(fftData.vRealPhaseBv, fftData.vImagPhaseBv, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT BiFFT = arduinoFFT(fftData.vRealPhaseBi, fftData.vImagPhaseBi, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT CvFFT = arduinoFFT(fftData.vRealPhaseCv, fftData.vImagPhaseCv, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT CiFFT = arduinoFFT(fftData.vRealPhaseCi, fftData.vImagPhaseCi, SAMPLES, SAMPLING_FREQUENCY);
  arduinoFFT NiFFT = arduinoFFT(fftData.vRealPhaseNi, fftData.vImagPhaseNi, SAMPLES, SAMPLING_FREQUENCY);//computations are not being done on IN, it is also not being printed, our current setup is blondel

  FullResample fullResample;

  myADE9078.stopFillingBuffer();
  myADE9078.resetFullBufferBit();
  myADE9078.startFillingBuffer();

  bool check = 0;

  while (check != 1){
  	delay(1);
  	check = myADE9078.isDoneSampling();
    // Serial.print("wait status: ");
    // Serial.println(check);
  }

  //Serial.println("done sampling, start reading");


  for (int i=0; i < readCount; ++i)//readcount = 8
  {
      // Serial.println("Outer loop starting");

      uint16_t burstMemoryOffset = i* 4 * 64; // each segment is 16 bytes, we read in sets of 64
      uint16_t startingAddress = BURST_MEMORY_BASE + burstMemoryOffset;
      myADE9078.spiBurstResampledWFB(startingAddress);

      // Serial.print("Outer Loop: ");
      // Serial.println(i);

      //memcpy
      for (int seg=0; seg < WFB_RESAMPLE_SEGMENTS; ++seg)
      {
        // Serial.print("Loop position: ");
        // Serial.print(i);
        // Serial.print(", ");
        // Serial.println(seg);
        // Serial.print("Segment Offset: ");
        // Serial.println(segOffSet);
        int segOffSet = seg + (i*64);

        // Serial.println("Ia,Va, Ib,Vb, Ic,Vc, In: ");
        // // Serial.print("Ia\t");
        // Serial.print(myADE9078.lastReads.resampledData.Ia[seg]); Serial.print(" ");
        // //Serial.print("Va\t");
        // Serial.print(myADE9078.lastReads.resampledData.Va[seg]); Serial.print(" ");
        // Serial.print(myADE9078.lastReads.resampledData.Ib[seg]); Serial.print(" ");
        // Serial.print(myADE9078.lastReads.resampledData.Vb[seg]); Serial.print(" ");
        // Serial.print(myADE9078.lastReads.resampledData.Ic[seg]); Serial.print(" ");
        // Serial.print(myADE9078.lastReads.resampledData.Ic[seg]); Serial.print(" ");
        // Serial.println(myADE9078.lastReads.resampledData.In[seg]);

        fftData.vRealPhaseAv[seg] = (double)myADE9078.lastReads.resampledData.Va[seg];
        fftData.vImagPhaseAv[seg] = 0.0;
        fftData.vRealPhaseAi[seg] = (double)myADE9078.lastReads.resampledData.Ia[seg];
        fftData.vImagPhaseAi[seg] = 0.0;
        fftData.vRealPhaseBv[seg] = (double)myADE9078.lastReads.resampledData.Vb[seg];
        fftData.vImagPhaseBv[seg] = 0.0;
        fftData.vRealPhaseBi[seg] = (double)myADE9078.lastReads.resampledData.Ib[seg];
        fftData.vImagPhaseBi[seg] = 0.0;
        fftData.vRealPhaseCv[seg] = (double)myADE9078.lastReads.resampledData.Vc[seg];
        fftData.vImagPhaseCv[seg] = 0.0;
        fftData.vRealPhaseCi[seg] = (double)myADE9078.lastReads.resampledData.Ic[seg];
        fftData.vImagPhaseCi[seg] = 0.0;
        fftData.vRealPhaseNi[seg] = (double)myADE9078.lastReads.resampledData.In[seg];
        fftData.vImagPhaseNi[seg] = 0.0;

      }
      AvFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      AvFFT.Compute(FFT_FORWARD);
      AvFFT.ComplexToMagnitude();

      AiFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      AiFFT.Compute(FFT_FORWARD);
      AiFFT.ComplexToMagnitude();

      BvFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      BvFFT.Compute(FFT_FORWARD);
      BvFFT.ComplexToMagnitude();
      BiFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      BiFFT.Compute(FFT_FORWARD);
      BiFFT.ComplexToMagnitude();

      CvFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      CvFFT.Compute(FFT_FORWARD);
      CvFFT.ComplexToMagnitude();

      CiFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      CiFFT.Compute(FFT_FORWARD);
      CiFFT.ComplexToMagnitude();

      NiFFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      NiFFT.Compute(FFT_FORWARD);
      NiFFT.ComplexToMagnitude();

      //Serial.print("FFT:");
//Phase A
      Serial.print("Av:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseAv[i], 1);
        Serial.print(";");
      }
      Serial.println("$");

      Serial.print("Ai:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseAi[i], 1);
        Serial.print(";");
      }
      Serial.println("$");
//phase B
      Serial.print("Bv:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseBv[i], 1);
        Serial.print(";");
      }
      Serial.println("$");

      Serial.print("Bi:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseBi[i], 1);
        Serial.print(";");
      }
      Serial.println("$");
//phase C
      Serial.print("Cv:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseCv[i], 1);
        Serial.print(";");
      }
      Serial.println("$");

      Serial.print("Ci:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseCi[i], 1);
        Serial.print(";");
      }
      Serial.println("$");

      Serial.print("Ni:");
      for(int i=0; i<(SAMPLES); i++){
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.print(fftData.vRealPhaseNi[i], 1);
        Serial.print(";");
      }
      Serial.println("$");

  }
  //Serial.println("Finished reading from ADE chip.");
}
