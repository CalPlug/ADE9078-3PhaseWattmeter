// Basic Test Demonstration for ADE9078 to read and report values (ADE9078_TEST)
//California Plug Load Research Center - 2017


#include <ADE9078.hpp>
#include <SPI.h>

//Define ADE9078 object with hardware parameters specified
#define local_SPI_freq 1000000  //Set SPI_Freq at 1MHz (#define, (no = or ;) helps to save memory)
#define local_SS 10  //Set the SS pin for SPI communication as pin 10  (#define, (no = or ;) helps to save memory)
ADE9078 myADE9078(local_SS, local_SPI_freq); // Call the ADE9078 Object with hardware parameters specified, the "local" lets us use the same parameters for examples in this program as what is assigned to the ADE9078 object

void setup() {
  Serial.begin(115200);
  delay(200);
  SPI.begin();
  delay(200);

  myADE9078.initialize();   //The ADE9078 must be initialized once in setup.
}


void loop() {

  float AvRMS, BvRMS, CvRMS;
  float IrmsA, IrmsB, IrmsC;
  float apparentPowerA, apparentPowerB, apparentPowerC;
  float reactivePowerA, reactivePowerB, reactivePowerC;
  float activePowerA, activePowerB, activePowerC;

  Serial.print("Version_16: ");
  Serial.println(myADE9078.getVersion()); // PHNOLOAD_32
  delay(200);

  Serial.print("PHNOLOAD_32: ");
  Serial.println(myADE9078.getPHNOLOAD()); // PHNOLOAD_32
  delay(200);

  AvRMS = myADE9078.getAVrms();
  Serial.print("AVrms (V): ");
  Serial.println(AvRMS);
  delay(200);

  BvRMS = myADE9078.getBVrms();
  Serial.print("BVrms (V): ");
  Serial.println(BvRMS);
  delay(200);

  CvRMS = myADE9078.getCVrms();
  Serial.print("BVrms (V): ");
  Serial.println(BvRMS);
  delay(200);


  IrmsA = myADE9078.getIrmsA();
  Serial.print("IrmsA (mA): ");
  Serial.println(IrmsA);
  delay(200);

  IrmsB = myADE9078.getIrmsB();
  Serial.print("IrmsB (mA): ");
  Serial.println(IrmsB);
  delay(200);

  IrmsC = myADE9078.getIrmsC();
  Serial.print("IrmsA (mA): ");
  Serial.println(IrmsC);
  delay(200);

  apparentPowerA = myADE9078.getInstApparentPowerA();
  Serial.print("Apparent Power A (mW): ");
  Serial.println(apparentPowerA);
  delay(200);

  apparentPowerB = myADE9078.getInstApparentPowerB();
  Serial.print("Apparent Power B (mW): ");
  Serial.println(apparentPowerB);
  delay(200);

  apparentPowerC = myADE9078.getInstApparentPowerC();
  Serial.print("Apparent Power C (mW): ");
  Serial.println(apparentPowerC);
  delay(200);

  activePowerA = myADE9078.getInstActivePowerA();
  Serial.print("Active Power A (mW): ");
  Serial.println(activePowerA);
  delay(200);

  activePowerB = myADE9078.getInstActivePowerB();
  Serial.print("Active Power B (mW): ");
  Serial.println(activePowerB);
  delay(200);

  activePowerC = myADE9078.getInstActivePowerC();
  Serial.print("Active Power C (mW): ");
  Serial.println(activePowerC);
  delay(200);

  reactivePowerA = myADE9078.getInstReactivePowerA();
  Serial.print("Rective Power A (mW): ");
  Serial.println(reactivePowerA);
  delay(200);

  reactivePowerB = myADE9078.getInstReactivePowerB();
  Serial.print("Rective Power B (mW): ");
  Serial.println(reactivePowerA);
  delay(200);

  reactivePowerC = myADE9078.getInstReactivePowerC();
  Serial.print("Rective Power C (mW): ");
  Serial.println(reactivePowerA);
  delay(200);



}
