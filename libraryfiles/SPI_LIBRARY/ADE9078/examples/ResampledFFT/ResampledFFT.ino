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

#define SAMPLES 512             //FFT Total samples input - Must be a power of 2, 8 times the 64 value buffer, should match waveform buffer all segments value
unsigned int sampling_period_us;  //holder for microseconds for FFT
#define SAMPLING_FREQUENCY 1000 //Hz, match rate to match sampling frequency for input data from data source
 
//Read, re-sample, process, report flow control 
bool SampleBufferFilled = 0; //Used to indicate when the buffer has been filled and is ready for readout, ready to be read out
bool FFTCalculationComplete = 0; //Flow control for readout of values
bool FFTInputBufferFilled = 0; //Flow control for readout of values

const int readCount = WFB_ALL_SEGMENTS/WFB_RESAMPLE_SEGMENTS;

struct FullResample  //buffer for resampled values
{
	//Phase A
    int16_t Ia[WFB_ALL_SEGMENTS];
    int16_t Va[WFB_ALL_SEGMENTS];
	int16_t Pa[WFB_ALL_SEGMENTS];
	//Phase B
    int16_t Ib[WFB_ALL_SEGMENTS];
    int16_t Vb[WFB_ALL_SEGMENTS];
	int16_t Pb[WFB_ALL_SEGMENTS];
	//Phase c
    int16_t Ic[WFB_ALL_SEGMENTS];
    int16_t Vc[WFB_ALL_SEGMENTS];
	int16_t Pc[WFB_ALL_SEGMENTS];
	//Neutral
    int16_t Vn[WFB_ALL_SEGMENTS];
	int16_t In[WFB_ALL_SEGMENTS];
	int16_t Pn[WFB_ALL_SEGMENTS];
};

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
FullResample* fullResample = (FullResample*)malloc(sizeof(FullResample));

void copySegments(int offsetMult)
{
    Serial.print("Loop sould go to... ");
    Serial.println(WFB_RESAMPLE_SEGMENTS);
    for (int i=0; i < WFB_RESAMPLE_SEGMENTS; ++i)
    {
      Serial.println(i);
      int16_t t2 = myADE9078.lastReads.resampledData.Ia[i];
      int blah = i;
      fullResample->Ia[blah] = t2;
      fullResample->Ia[i+(offsetMult*64)] = myADE9078.lastReads.resampledData.Ia[i];

      //Serial.println(t2);

      // fr->Va[i+(offsetMult*64)] = partial->Va[i];
      // fr->Ib[i+(offsetMult*64)] = partial->Ib[i];
      // fr->Vb[i+(offsetMult*64)] = partial->Vb[i];
      // fr->Ic[i+(offsetMult*64)] = partial->Ic[i];
      // fr->Vc[i+(offsetMult*64)] = partial->Vc[i];
      // fr->Ia[i+(offsetMult*64)] = partial->In[i];
    }
}

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

    if (SampleBufferFilled == 0) //check to see if the buffer is empty, if so, sample and fill it
	{
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

        Serial.print("Outer Loop: ");
        Serial.println(i);

        for (int seg=0; seg < WFB_RESAMPLE_SEGMENTS; ++seg)
        {
          Serial.print("Loop position: ");
          Serial.print(i);
          Serial.print(", ");
          Serial.println(seg);
          Serial.print("Segment Offset: ");
          int segOffSet = seg + (i*64);
          Serial.println(segOffSet);

          int16_t t2 = myADE9078.lastReads.resampledData.Ia[seg];
          //fullResample->Ia[seg+(i*64)] = t2;
          //int16_t t1 = fullResample->Ia[segOffSet];

          fullResample->Ia[segOffSet] = t2;

          //fullResample->Ia[seg+(i*64)] = myADE9078.lastReads.resampledData.Ia[seg];
        }
    }
	SampleBufferFilled = 1;  //indicate the sampling is complete and the buffer is filled
	    
	myADE9078.configureWFB(0); // per datasheet, have to set a certain bit to 0 to restart with stop on full
    // might need to write 23rd bit in STATUS0 to 0?

    Serial.println("Finished reading from ADE chip.");
	}
	
	//This part needs to be integrated, after the value read-in is complete as resampled, they then need to be copied to the FFT structure which handles the I/O for the FFT
	   /*Copy Sample Buffer to FFT Processing Handlers*/
	if (SampleBufferFilled == 1) //if buffer filled, copy samples to FFT input buffer
	{
		for(int i=0; i<SAMPLES; i++)
		{
		//Copy values read in last sample into the FFT input/Output handler  "Datasource" is a placeholder for the collected sample array
		vRealPhaseAv[i] = datasource[i]; //time space sampled values: Phase A, Voltage
		vImagPhaseAv[i] = 0;  //holder for Img. (Phase values): Phase A, Voltage

		vRealPhaseAi[i] = datasource[i]; //time space sampled values: Phase A, Current
		vImagPhaseAi[i] = 0;  //holder for Img. (Phase values): Phase A, Current

		vRealPhaseAp[i] = datasource[i]; //time space sampled values: Phase A, Power
		vImagPhaseAp[i] = 0;  //holder for Img. (Phase values): Phase A, Power

		vRealPhaseBv[i] = datasource[i]; //time space sampled values: Phase B, Voltage
		vImagPhaseBv[i] = 0;  //holder for Img. (Phase values): Phase B, Voltage

		vRealPhaseBi[i] = datasource[i]; //time space sampled values: Phase B, Current
		vImagPhaseBi[i] = 0;  //holder for Img. (Phase values): Phase B, Current

		vRealPhaseBp[i] = datasource[i]; //time space sampled values: Phase B, Power
		vImagPhaseBp[i] = 0;  //holder for Img. (Phase values): Phase B, Power

		vRealPhaseCv[i] = datasource[i]; //time space sampled values: Phase C, Voltage
		vImagPhaseCv[i] = 0;  //holder for Img. (Phase values): Phase C, Voltage

		vRealPhaseCi[i] = datasource[i]; //time space sampled values: Phase C, Current
		vImagPhaseCi[i] = 0;  //holder for Img. (Phase values): Phase C, Current

		vRealPhaseCp[i] = datasource[i]; //time space sampled values: Phase C, Power
		vImagPhaseCp[i] = 0;  //holder for Img. (Phase values): Phase C, Power

		vRealPhaseNv[i] = datasource[i]; //time space sampled values: Neutral, Voltage
		vImagPhaseNv[i] = 0;  //holder for Img. (Phase values): Neutral, Voltage

		vRealPhaseNi[i] = datasource[i]; //time space sampled values: Neutral, Current
		vImagPhaseNi[i] = 0;  //holder for Img. (Phase values): Neutral, Current

		vRealPhaseNp[i] = datasource[i]; //time space sampled values: Neutral, Power
		vImagPhaseNp[i] = 0;  //holder for Img. (Phase values): Neutral, Power
		 
			}
		}
		SampleBufferFilled = 0; //buffer now filled, ready to process FFT, then begin re-sampling on next loop
		FFTInputBufferFilled = 1; //data transferred to the input buffer and ready to be processed
	}


	
	
	 
    /*Calculate FFT from collected values*/
	if (FFTInputBufferFilled == 1) //check to see if input buffer is filled
	{
	//Phase A
	//Phase A - Voltage
    FFT.Windowing(FFTDataHolder.vRealPhaseAv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseAv, FFTDataHolder.vImagPhaseAv, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseAv, FFTDataHolder.vImagPhaseAv, SAMPLES); //Calculate magnitudes
    //double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);  //return dominant frequency, not needed in this example
	
	//Phase A - Current
    FFT.Windowing(FFTDataHolder.vRealPhaseAi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseAi, FFTDataHolder.vImagPhaseAi, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseAi, FFTDataHolder.vImagPhaseAi, SAMPLES); //Calculate magnitudes

	
	//Phase A - Power
    FFT.Windowing(FFTDataHolder.vRealPhaseAp, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseAp, FFTDataHolder.vImagPhaseAp, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseAp, FFTDataHolder.vImagPhaseAp, SAMPLES); //Calculate magnitudes
	
	//Phase B
	//Phase B - Voltage
	FFT.Windowing(FFTDataHolder.vRealPhaseBv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseBv, FFTDataHolder.vImagPhaseBv, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseBv, FFTDataHolder.vImagPhaseBv, SAMPLES); //Calculate magnitudes
	
	//Phase B - Current
    FFT.Windowing(FFTDataHolder.vRealPhaseBi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseBi, FFTDataHolder.vImagPhaseBi, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseBi, FFTDataHolder.vImagPhaseBi, SAMPLES); //Calculate magnitudes

	
	//Phase B - Power
    FFT.Windowing(FFTDataHolder.vRealPhaseBp, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseBp, FFTDataHolder.vImagPhaseBp, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseBp, FFTDataHolder.vImagPhaseBp, SAMPLES); //Calculate magnitudes
	
	//Phase C
	//Phase C - Voltage
	FFT.Windowing(FFTDataHolder.vRealPhaseCv, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseCv, FFTDataHolder.vImagPhaseCv, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseCv, FFTDataHolder.vImagPhaseCv, SAMPLES); //Calculate magnitudes
	
	//Phase C - Current
    FFT.Windowing(FFTDataHolder.vRealPhaseCi, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseCi, FFTDataHolder.vImagPhaseCi, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseCi, FFTDataHolder.vImagPhaseCi, SAMPLES); //Calculate magnitudes

	
	//Phase C - Power
    FFT.Windowing(FFTDataHolder.vRealPhaseCp, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Initialize the FFT type
    FFT.Compute(FFTDataHolder.vRealPhaseCp, FFTDataHolder.vImagPhaseCp, SAMPLES, FFT_FORWARD); //Compute FFT
    FFT.ComplexToMagnitude(FFTDataHolder.vRealPhaseCp, FFTDataHolder.vImagPhaseCp, SAMPLES); //Calculate magnitudes
	
	SampleBufferFilled = 0; //prior values read-out complete and processed , prepare to take more values
	FFTCalculationComplete = 1;  //indicate calculation is complete
	FFTInputBufferFilled = 0; //inputs now converted to outputs after processing
	}
	

//Read out collected values
	//if (SampleBufferFilled == 1)
	//{
    //for (int i=0; i < WFB_ALL_SEGMENTS; ++i)
   // {
   //     Serial.print(i);
  //      Serial.print("Ia, Va, Ib, Vb, Ic, Vc, In: ");
  //      Serial.print(fullResample->Ia[i]);
  //      Serial.print(fullResample->Va[i]);
   //     Serial.print(fullResample->Ib[i]);
  //      Serial.print(fullResample->Vb[i]);
  //      Serial.print(fullResample->Ic[i]);
  //      Serial.print(fullResample->Vc[i]);
  //      Serial.print(fullResample->In[i]);
  //      Serial.println();
  //  }
  //}

  //print results to serial port at the end of the FFT calculation:
	if (FFTCalculationComplete == 1)
	{
		//Phase A printout
		//Voltage
		Serial.print("Av:");    //Print out the start character set for the output
		for(int i=0; i<(SAMPLES/2); i++)
		{
			/*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
			 
			Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1); //print the frequency value
			Serial.print(","); //print the intra-value separator for the ordered pair
			Serial.print(FFTDataHolder.vRealPhaseAv[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseAi[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseAp[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseBv[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseBi[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseBp[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseCv[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseCi[i], 1);    //View only this line in serial plotter to visualize the bins
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
			Serial.print(FFTDataHolder.vRealPhaseCp[i], 1);    //View only this line in serial plotter to visualize the bins
			Serial.print(";"); //print the inter-value separator between ordered pairs
		}
		Serial.print("$");    //Use the "$" character followed by a LF as the end character for a line of data
		
		FFTCalculationComplete = 0; //readout complete, re-initialize flag
	}
	
 


}
