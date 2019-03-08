// Basic Test Demonstration for ADE9078 to read and report values (ADE9078_TEST)
//California Plug Load Research Center - 2019


#include <ADE9078.h>
#include <SPI.h>
#include <EEPROM.h>


//Architecture Control:
//Make sure you select in the ADE9078.h file the proper board architecture, either Arduino/AVR/ESP8266 or ESP32
//REMINDER: ONLY SELECT THE SINGLE OPTION FOR THE BOARD TYPE YOU ARE USING!


//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 115200  //Set SPI_Freq at 1MHz  - used for Arduino/AVR configuration
//#define local_SPI_freq 1000000  //Set SPI_Freq at 1MHz  - used for Arduino/AVR configuration
#define local_SS 10  //Set the SS pin for SPI communication as pin 10, typical on Arduino Uno and similar boards

#define WFB_ALL_SEGMENTS 512
#define BURST_MEMORY_BASE 0x800

const int readCount = WFB_ALL_SEGMENTS/WFB_RESAMPLE_SEGMENTS;

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

}


void loop() {

    myADE9078.configureWFB(1); // begin

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

    myADE9078.configureWFB(0); // per datasheet, have to set a certain bit to 0 to restart with stop on full
    // might need to write 23rd bit in STATUS0 to 0?

    Serial.println("Finished reading from ADE chip.");

    for (int i=0; i < WFB_ALL_SEGMENTS; ++i)
    {
        Serial.print(i);
        Serial.print("Ia, Va, Ib, Vb, Ic, Vc, In: ");
        Serial.print(fullResample->Ia[i]);
        Serial.print(fullResample->Va[i]);
        Serial.print(fullResample->Ib[i]);
        Serial.print(fullResample->Vb[i]);
        Serial.print(fullResample->Ic[i]);
        Serial.print(fullResample->Vc[i]);
        Serial.print(fullResample->In[i]);
        Serial.println();
    }
}
