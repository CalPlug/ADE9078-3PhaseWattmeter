//Resampled Wave form buffer for ADE9078 to read and report values (ADE9078_TEST)
//California Plug Load Research Center - 2019
//Enoch Chau 2019

#include <ADE9078.h>
#include <SPI.h>

//Architecture Control:
//Make sure you select in the ADE9078.h file the proper board architecture, either Arduino/AVR/ESP8266 or ESP32
//REMINDER: ONLY SELECT THE SINGLE OPTION FOR THE BOARD TYPE YOU ARE USING!
#define ESP32ARCH

//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 115200  //Set SPI_Freq at 1MHz  - used for Arduino/AVR configuration
#define local_SS 5  //Set the SS pin for SPI communication as pin 10, typical on Arduino Uno and similar boards

//****WFB settings********
#define WFB_ALL_SEGMENTS 512
#define BURST_MEMORY_BASE 0x801//well, its supposed to be 0x800 but that doesn't work that well for some reason


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

  SPI.begin();
  delay(200);
    myADE9078.initialize(); //Call initialization of the ADE9078 withe default configuration plus options specified
	//EEPROMInit()  //call only once on a virgin chip to "partition" EEPROM for the input type expected moving forward
	//load_data_allfields();  //load EEPROM values
  delay(200);
    //CONFIGURE WFB
  myADE9078.configureWFB();
}


void loop() {
  FullResample fullResample;

  myADE9078.stopFillingBuffer();
  myADE9078.resetFullBufferBit();
  myADE9078.startFillingBuffer();

  bool check = 0;
  //Serial.println("check");
  while (check != 1){
  	delay(1);
  	check = myADE9078.isDoneSampling();
    Serial.print("wait status: ");
    Serial.println(check);
  }

  Serial.println("done sampling, start reading");


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

        Serial.println("Ia,Va, Ib,Vb, Ic,Vc, In: ");
        Serial.print(myADE9078.lastReads.resampledData.Ia[seg]); Serial.print(" ");
        Serial.print(myADE9078.lastReads.resampledData.Va[seg]); Serial.print(" ");
        Serial.print(myADE9078.lastReads.resampledData.Ib[seg]); Serial.print(" ");
        Serial.print(myADE9078.lastReads.resampledData.Vb[seg]); Serial.print(" ");
        Serial.print(myADE9078.lastReads.resampledData.Ic[seg]); Serial.print(" ");
        Serial.print(myADE9078.lastReads.resampledData.Ic[seg]); Serial.print(" ");
        Serial.println(myADE9078.lastReads.resampledData.In[seg]);
      }
  }
  Serial.println("Finished reading from ADE chip.");
}
