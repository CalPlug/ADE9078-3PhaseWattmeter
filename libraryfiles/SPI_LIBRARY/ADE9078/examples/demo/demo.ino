// Basic Test Demonstration for ADE9078 to read and report values (ADE9078_TEST)
//California Plug Load Research Center - 2019


#include <ADE9078.h>
#include <SPI.h>

//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 1000000  //Set SPI_Freq at 1MHz (#define, (no = or ;) helps to save memory)
#define local_SS 10  //Set the SS pin for SPI communication as pin 10, typical on Arduino Uno and similar boards

//Architecture Control:
//Make sure you select in the ADE9078.h file the proper board architecture, either Arduino/AVR/ESP8266 or ESP32
//REMINDER: ONLY SELECT THE SINGLE OPTION FOR THE BOARD TYPE YOU ARE USING!

struct InitializationSettings* is = new InitializationSettings; //define structure for initialized values

ADE9078 myADE9078(local_SS, local_SPI_freq, is); // Call the ADE9078 Object with hardware parameters specified, local variables are copied to private variables inside the class when object is created.

void setup() {

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
  
  
  
	//4 Wire Wye configuration - non blondel compliant
	is->vConsel=0;
	is->iConsel=0;
	
	//Delta, blondell
	is->vConsel=4; //byte value of 100,
	is->iConsel=0;
	

  SPI.begin();
  delay(200);

  myADE9078.initialize(); //Call mode 0 for 4 wire Wye, blondel configuration
}


void loop() {

  double AvRMS, BvRMS, CvRMS;
  double IrmsA, IrmsB, IrmsC;
  double wattHoursA;
  double apparentPowerA, apparentPowerB, apparentPowerC;
  double reactivePowerA, reactivePowerB, reactivePowerC;
  double activePowerA, activePowerB, activePowerC;

  Serial.print("Version_16: ");
  Serial.println(myADE9078.getVersion()); // PHNOLOAD_32
  delay(20);

  Serial.print("PHNOLOAD_32: ");
  Serial.println(myADE9078.getPHNOLOAD()); // PHNOLOAD_32
  delay(20);

  AvRMS = myADE9078.getAVrms();
  Serial.print("AVrms (V): ");
  Serial.println(AvRMS);
  delay(10);

  BvRMS = myADE9078.getBVrms();
  Serial.print("BVrms (V): ");
  Serial.println(BvRMS);
  delay(10);

  CvRMS = myADE9078.getCVrms();
  Serial.print("BVrms (V): ");
  Serial.println(BvRMS);
  delay(10);

  IrmsA = myADE9078.getIrmsA();
  Serial.print("IrmsA (mA): ");
  Serial.println(IrmsA);
  delay(10);

  IrmsB = myADE9078.getIrmsB();
  Serial.print("IrmsB (mA): ");
  Serial.println(IrmsB);
  delay(10);

  IrmsC = myADE9078.getIrmsC();
  Serial.print("IrmsA (mA): ");
  Serial.println(IrmsC);
  delay(10);

  wattHoursA = myADE9078.readWattHoursA();
  Serial.print("WattHoursA: ");
  Serial.println(wattHoursA);
  delay(10);

  apparentPowerA = myADE9078.getInstApparentPowerA();
  Serial.print("Apparent Power A (mW): ");
  Serial.println(apparentPowerA);
  delay(10);

  apparentPowerB = myADE9078.getInstApparentPowerB();
  Serial.print("Apparent Power B (mW): ");
  Serial.println(apparentPowerB);
  delay(10);

  apparentPowerC = myADE9078.getInstApparentPowerC();
  Serial.print("Apparent Power C (mW): ");
  Serial.println(apparentPowerC);
  delay(10);

  activePowerA = myADE9078.getInstActivePowerA();
  Serial.print("Active Power A (mW): ");
  Serial.println(activePowerA);
  delay(10);

  activePowerB = myADE9078.getInstActivePowerB();
  Serial.print("Active Power B (mW): ");
  Serial.println(activePowerB);
  delay(10);

  activePowerC = myADE9078.getInstActivePowerC();
  Serial.print("Active Power C (mW): ");
  Serial.println(activePowerC);
  delay(10);

  reactivePowerA = myADE9078.getInstReactivePowerA();
  Serial.print("Rective Power A (mW): ");
  Serial.println(reactivePowerA);
  delay(10);

  reactivePowerB = myADE9078.getInstReactivePowerB();
  Serial.print("Rective Power B (mW): ");
  Serial.println(reactivePowerA);
  delay(10);

  reactivePowerC = myADE9078.getInstReactivePowerC();
  Serial.print("Rective Power C (mW): ");
  Serial.println(reactivePowerA);
  delay(10);

  delay(1000); //Delay before repeating the loop
}
