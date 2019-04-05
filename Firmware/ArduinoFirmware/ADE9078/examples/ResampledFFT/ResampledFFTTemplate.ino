#include "arduinoFFT.h"
//extended from example by Norwegian Creations:  https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/
 
#define SAMPLES 512             //FFT Total samples input - Must be a power of 2, 8 times the 64 value buffer
#define SAMPLING_FREQUENCY 1000 //Hz, match rate to match sampling frequency for input data from data source
 
arduinoFFT FFT = arduinoFFT(); //Define object for FFT calculations
 
unsigned int sampling_period_us;  //holder for microseconds for FFT
 
bool SampleBufferFilled = 0; //Used to indicate when the buffer has been filled and is ready for readout, ready to be read out
bool FFTCalculationComplete = 0; //Flow control for readout of values
 
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

 
void setup() {
    Serial.begin(115200);
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));  //calculate the sampling period in microseconds for the FFT, relative to 1 MHZ
}
 
void loop() {


//Begin loop to perform waveform buffering
   
    /*Copy Sample Buffer to FFT Processing Handlers*/
	if (SampleBufferFilled == 1) //buffer not filled, take samples
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
		(SampleBufferFilled = 0) //buffer now filled, ready to process FFT, then begin re-sampling on next loop
	}
 
    /*Calculate FFT from collected values*/
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
	

 

 

    //print results to serial port at the end of the FFT calculation:
	
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
	
	
 

}