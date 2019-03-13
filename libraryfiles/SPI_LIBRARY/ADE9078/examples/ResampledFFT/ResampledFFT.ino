// Basic Test Demonstration for ADE9078 to read and report values, using the waveform buffer.  The measured values are FFT processed and then the frequency, power components are reported over serial for each phase for voltage for voltage, current, and power
//California Plug Load Research Center - 2019


#include <ADE9078.h>
#include <SPI.h>
#include <EEPROM.h>
#include "arduinoFFT.h"  //FFT Components extended from example by Norwegian Creations:  https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/


//Architecture Control:
//Make sure you select in the ADE9078.h file the proper board architecture, either Arduino/AVR/ESP8266 or ESP32
//REMINDER: ONLY SELECT THE SINGLE OPTION FOR THE BOARD TYPE YOU ARE USING!


//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 115200  //Set SPI_Freq at 1MHz  - used for Arduino/AVR configuration
//#define local_SPI_freq 1000000  //Set SPI_Freq at 1MHz  - used for Arduino/AVR configuration
#define local_SS 10  //Set the SS pin for SPI communication as pin 10, typical on Arduino Uno and similar boards

#define WFB_ALL_SEGMENTS 512  //total array size to read in of each 64 sample buffer
#define BURST_MEMORY_BASE 0x800  //base address of the burst read function

arduinoFFT FFT = arduinoFFT(); //Call object for FFT calculations

#define SAMPLES 64             //FFT Total samples input - Must be a power of 2
unsigned int sampling_period_us;  //holder for microseconds for FFT
#define SAMPLING_FREQUENCY 1000 //Hz, match rate to match sampling frequency for input data from data source

//Read, re-sample, process, report flow control
bool SampleBufferFilled = 0; //Used to indicate when the buffer has been filled and is ready for readout, ready to be read out
bool FFTCalculationComplete = 0; //Flow control for readout of values
bool FFTInputBufferFilled = 0; //Flow control for readout of values

const int readCount = WFB_ALL_SEGMENTS/WFB_RESAMPLE_SEGMENTS;


struct FFTDataHolder  //this is the holder for the inputs and the FFT returns
	{
		double vRealPhaseAv[SAMPLES]; //holder for Real (frequency values): Phase A, Voltage
		double vImagPhaseAv[SAMPLES];  //holder for Img. (Phase values): Phase A, Voltage

		double vRealPhaseAi[SAMPLES]; //holder for Real (frequency values): Phase A, Current
		double vImagPhaseAi[SAMPLES];  //holder for Img. (Phase values): Phase A, Current

		double vRealPhaseAp[SAMPLES]; //holder for Real (frequency values): Phase A, Power
		double vImagPhaseAp[SAMPLES];  //holder for Img. (Phase values): Phase A, Power

		double vRealPhaseBv[SAMPLES]; //holder for Real (frequency values): Phase B, Voltage
		double vImagPhaseBv[SAMPLES];  //holder for Img. (Phase values): Phase B, Voltage

		double vRealPhaseBi[SAMPLES]; //holder for Real (frequency values): Phase B, Current
		double vImagPhaseBi[SAMPLES];  //holder for Img. (Phase values): Phase B, Current

		double vRealPhaseBp[SAMPLES]; //holder for Real (frequency values): Phase B, Power
		double vImagPhaseBp[SAMPLES];  //holder for Img. (Phase values): Phase B, Power

		double vRealPhaseCv[SAMPLES]; //holder for Real (frequency values): Phase C, Voltage
		double vImagPhaseCv[SAMPLES];  //holder for Img. (Phase values): Phase C, Voltage

		double vRealPhaseCi[SAMPLES]; //holder for Real (frequency values): Phase C, Current
		double vImagPhaseCi[SAMPLES];  //holder for Img. (Phase values): Phase C, Current

		double vRealPhaseCp[SAMPLES]; //holder for Real (frequency values): Phase C, Power
		double vImagPhaseCp[SAMPLES];  //holder for Img. (Phase values): Phase C, Power

		double vRealPhaseNv[SAMPLES]; //holder for Real (frequency values): Neutral, Voltage
		double vImagPhaseNv[SAMPLES];  //holder for Img. (Phase values): Neutral, Voltage

		double vRealPhaseNi[SAMPLES]; //holder for Real (frequency values): Neutral, Current
		double vImagPhaseNi[SAMPLES];  //holder for Img. (Phase values): Neutral, Current

		double vRealPhaseNp[SAMPLES]; //holder for Real (frequency values): Neutral, Power
		double vImagPhaseNp[SAMPLES];  //holder for Img. (Phase values): Neutral, Power
};


struct InitializationSettings* is = new InitializationSettings; //define structure for initialized values

ADE9078 myADE9078(local_SS, local_SPI_freq, is); // Call the ADE9078 Object with hardware parameters specified, local variables are copied to private variables inside the class when object is created.
struct FFTDataHolder* fftData;

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

  SPI.begin();
  delay(200);
  myADE9078.initialize(); //Call initialization of the ADE9078 withe default configuration plus options specified
	//EEPROMInit()  //call only once on a virgin chip to "partition" EEPROM for the input type expected moving forward
	//load_data_allfields();  //load EEPROM values

	sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));  //calculate the sampling period in microseconds for the FFT, relative to 1 MHZ

}


void loop() {

    myADE9078.configureWFB(1); // begin waveform buffer  - do you want to call this in the loop each time?
    delay(300);

    // int samplingDone = 0;
    // while (samplingDone == 0)
    // {
    //   if (myADE9078.isDoneSampling())
    //   {
    //       samplingDone = 1;
    //   }
    // }

    Serial.println("Finished sampling. Reading beginning.");

    for (int i=0; i < readCount; ++i)
    {
        uint16_t burstMemoryOffset = i*16*64; // each segment is 16 bytes, we read in sets of 64
        uint16_t startingAddress = BURST_MEMORY_BASE + burstMemoryOffset;
        myADE9078.spiBurstResampledWFB(startingAddress);
        myADE9078.configureWFB(0); // per datasheet, have to set a certain bit to 0 to restart with stop on full. 23rd bit in status0
        Serial.print("Outer Loop: ");
        Serial.println(i);

        for(int i=0; i<SAMPLES; i++)
        {
            //Copy values read in last sample into the FFT input/Output handler  "Datasource" is a placeholder for the collected sample array
            fftData->vRealPhaseAv[i] = myADE9078.lastReads.resampledData.Va[i]; //time space sampled values: Phase A, Voltage
            fftData->vImagPhaseAv[i] = 0;  //holder for Img. (Phase values): Phase A, Voltage

            fftData->vRealPhaseAi[i] = myADE9078.lastReads.resampledData.Ia[i]; //time space sampled values: Phase A, Current
            fftData->vImagPhaseAi[i] = 0;  //holder for Img. (Phase values): Phase A, Current

            fftData->vRealPhaseBv[i] = myADE9078.lastReads.resampledData.Vb[i]; //time space sampled values: Phase B, Voltage
            fftData->vImagPhaseBv[i] = 0;  //holder for Img. (Phase values): Phase B, Voltage

            fftData->vRealPhaseBi[i] = myADE9078.lastReads.resampledData.Ib[i]; //time space sampled values: Phase B, Current
            fftData->vImagPhaseBi[i] = 0;  //holder for Img. (Phase values): Phase B, Current

            fftData->vRealPhaseCv[i] = myADE9078.lastReads.resampledData.Vc[i]; //time space sampled values: Phase C, Voltage
            fftData->vImagPhaseCv[i] = 0;  //holder for Img. (Phase values): Phase C, Voltage

            fftData->vRealPhaseCi[i] = myADE9078.lastReads.resampledData.Vc[i]; //time space sampled values: Phase C, Current
            fftData->vImagPhaseCi[i] = 0;  //holder for Img. (Phase values): Phase C, Current

            fftData->vRealPhaseNi[i] = myADE9078.lastReads.resampledData.In[i]; //time space sampled values: Neutral, Current
            fftData->vImagPhaseNi[i] = 0;  //holder for Img. (Phase values): Neutral, Current
        }

        /*Calculate FFT from collected values*/
        //Phase A
        //Phase A - Voltage
        FFT.Windowing(fftData->vRealPhaseAv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseAv, fftData->vImagPhaseAv, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseAv, fftData->vImagPhaseAv, SAMPLES); //Calculate magnitudes
        //double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);  //return dominant frequency, not needed in this example

        //Phase A - Current
        FFT.Windowing(fftData->vRealPhaseAi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseAi, fftData->vImagPhaseAi, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseAi, fftData->vImagPhaseAi, SAMPLES); //Calculate magnitudes


        //Phase B
        //Phase B - Voltage
        FFT.Windowing(fftData->vRealPhaseBv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseBv, fftData->vImagPhaseBv, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseBv, fftData->vImagPhaseBv, SAMPLES); //Calculate magnitudes

        //Phase B - Current
        FFT.Windowing(fftData->vRealPhaseBi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseBi, fftData->vImagPhaseBi, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseBi, fftData->vImagPhaseBi, SAMPLES); //Calculate magnitudes


        //Phase C
        //Phase C - Voltage
        FFT.Windowing(fftData->vRealPhaseCv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseCv, fftData->vImagPhaseCv, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseCv, fftData->vImagPhaseCv, SAMPLES); //Calculate magnitudes

        //Phase C - Current
        FFT.Windowing(fftData->vRealPhaseCi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
        FFT.Compute(fftData->vRealPhaseCi, fftData->vImagPhaseCi, SAMPLES, FFT_FORWARD); //Compute FFT
        FFT.ComplexToMagnitude(fftData->vRealPhaseCi, fftData->vImagPhaseCi, SAMPLES); //Calculate magnitudes


        //Phase A printout
        //Voltage
        Serial.print("Av:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
        /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
        Serial.print(","); //print the intra-value separator for the ordered pair
        Serial.print(fftData->vRealPhaseAv[i], 1);    //View only this line in serial plotter to visualize the bins
        Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Current
        Serial.print("Ai:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
        /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
        Serial.print(","); //print the intra-value separator for the ordered pair
        Serial.print(fftData->vRealPhaseAi[i], 1);    //View only this line in serial plotter to visualize the bins
        Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Power
        Serial.print("Ai:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseAp[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Phase B printout
        //Voltage
        Serial.print("Bv:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseBv[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Current
        Serial.print("Bi:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseBi[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Power
        Serial.print("Bi:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseBp[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Phase C printout
        //Voltage
        Serial.print("Cv:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseCv[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Current
        Serial.print("Ci:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseCi[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
        }
        Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        //Power
        Serial.print("Ci:");    //Print out the start character set for the output
        for(int i=0; i<(SAMPLES/2); i++)
        {
            /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/

            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
            Serial.print(","); //print the intra-value separator for the ordered pair
            Serial.print(fftData->vRealPhaseCp[i], 1);    //View only this line in serial plotter to visualize the bins
            Serial.print(";"); //print the inter-value separator between ordered pairs
            }
            Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data

        }
}
