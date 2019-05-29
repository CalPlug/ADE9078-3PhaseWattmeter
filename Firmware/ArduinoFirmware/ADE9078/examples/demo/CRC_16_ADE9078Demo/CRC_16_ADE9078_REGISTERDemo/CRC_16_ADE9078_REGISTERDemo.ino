//Example ADE9078 CRC Check algorithm test code reading from 16 and 32-bit registers by Avinash Pai and Michael Klopfer. 

#include <ADE9078.h>
#include <SPI.h>


#define local_SPI_freq 115200 //Set SPI_Freq at 1MHz  
#define local_SS 5 // esp32 define pin 5 as slave select

struct InitializationSettings* is = new InitializationSettings;
ADE9078 myADE9078(local_SS, local_SPI_freq, is);
uint16_t Address16 = 0x4FE; // 16-bit CRC register, read version number
uint16_t Address32 = 0x26A; // 32-bit CRC register, read version of metrology algorithms
bool CRCcheck16 = false; // Passed via reference for 16 bit CRC
bool CRCcheck32 = false; // Passed via reference for 32 bit CRC

void setup() {
  myADE9078.initialize(); // initalize ADE9078
  Serial.begin(115200);
  
  uint16_t value16 = myADE9078.spiRead16CRC(Address16, CRCcheck16); 
  Serial.println();
  Serial.println("Return value [HEX]: ");
  Serial.println(value16, HEX);
  Serial.print("CRCHECK 16-bit: ");
  Serial.println(CRCcheck16);
  Serial.println();

  uint16_t value32 = myADE9078.spiRead32CRC(Address32, CRCcheck32);
  Serial.println();
  Serial.println("Return value [HEX]: ");
  Serial.println(value32, HEX);
  Serial.print("CRCHECK 32-bit: ");
  Serial.println(CRCcheck32);

}

void loop() {
 // None
}
