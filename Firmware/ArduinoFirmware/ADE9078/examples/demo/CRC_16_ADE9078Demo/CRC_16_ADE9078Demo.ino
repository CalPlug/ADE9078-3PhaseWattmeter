//Example ADE9078 CRC Check algorithm test code by Avinash Pai and Michael Klopfer with contributions cited.

void setup() {
  Serial.begin (9600);

  uint16_t CRCRETURN = 0; //Holder for the return from the CRC function

  //16 bit return example with the 16 bit CRC example
  uint16_t return1for16bit = 0x00; //first returned byte from SPI, the MSB value
  uint16_t return2for16bit = 0x80; //second returned byte from SPI, the LSB value

  uint16_t return1forCRC1 = 0x8C; //first returned byte from SPI, the MSB value
  uint16_t return2forCRC1 = 0x87; //second returned byte from SPI, the LSB value

  char feedarray16 [2];//holder for two values (a 16 bit input, then terminated with a null character)
  //char feedarray16 [4]; //holder for two values (a 16 bit input, then terminated with a null character), use with 4 for padding, if needed

  //Load the 16 bit return values into a CHAR array to process
  feedarray16 [0] = return1for16bit;
  feedarray16 [1] = return2for16bit;
  //feedarray16 [2] = 0x00; //optional padding  for 16 bit
  //feedarray16 [3] = 0x00; //optional padding for 16 bit
  
  CRCRETURN = crc16(feedarray16, sizeof(feedarray16)); // feed in a 16 bit number (two bytes) then calculate CRC

  Serial.print("Provided 16 bit CRC Checksum: ");
  uint16_t readinCRCholder = ((return1forCRC1 << 8) | (return2forCRC1)); //shift in MSB then add LSF to provide common value to print out
  Serial.println(readinCRCholder, HEX); 

  Serial.print("Calculated 16 bit CRC Output: ");
  Serial.println(CRCRETURN, HEX);

uint16_t return1forCRC1test16 = (CRCRETURN & 0b0000000011111111); //save the lower byte bit bitmasking to clear upper byte
uint16_t return2forCRC1test16 = (CRCRETURN >> 8); //save the upper byte by bitshifting down

if (return2forCRC1test16 == return1forCRC1)
{
//match found on upper CRC byte, tell the user something 
}

if (return1forCRC1test16 == return2forCRC1)
{
//match found on upper CRC byte, tell the user something 
}

  //32 bit return example with the 16 bit CRC example
  uint16_t return1for32bit = 0x00; //first returned byte from SPI, the MSB value
  uint16_t return2for32bit = 0x00; //first returned byte from SPI, the top middle value
  uint16_t return3for32bit = 0x00; //first returned byte from SPI, the lower middle value
  uint16_t return4for32bit = 0x00; //first returned byte from SPI, the LSB value

  uint16_t return1forCRC2 = 0x00; //first returned byte from SPI, the MSB value
  uint16_t return2forCRC2 = 0x00; //first returned byte from SPI, the LSB value

  char feedarray32 [4]; //holder for four values (a 32 bit input, then terminated with a null character)

  //Load the 32 bit return values into a CHAR array to process
  feedarray32 [0] = return1for32bit;
  feedarray32 [1] = return2for32bit;
  feedarray32 [2] = return3for32bit;
  feedarray32 [3] = return4for32bit;
  
  CRCRETURN = crc16(feedarray32, sizeof(feedarray32)); // feed in a 16 bit number (two bytes) then calculate CRC

  uint16_t return1forCRC1test32 = (CRCRETURN & 0b0000000011111111); //save the lower byte bit bitmasking to clear upper byte
  uint16_t return2forCRC1test32 = (CRCRETURN >> 8); //save the upper byte by bitshifting down

  Serial.print("Provided 16 bit CRC Checksum: ");
  readinCRCholder = ((return1forCRC1 << 8) | (return2forCRC1)); //shift in MSB then add LSF to provide common value to print out
  Serial.println(readinCRCholder, HEX); 

  Serial.print("Calculated 16 bit CRC Output: ");
  Serial.println(CRCRETURN, HEX);

  if (return2forCRC1test32 == return1forCRC2)
  {
  //match found on upper CRC byte, tell the user something 
  Serial.println("Lower CRC byte Mactch!");
  }
  
  if (return1forCRC1test32 == return2forCRC2)
  {
  //match found on upper CRC byte, tell the user something 
    Serial.println("Upper CRC byte Mactch!");
  }
   

}

uint16_t crc16(char* pData, int length) //https://gist.github.com/tijnkooijmans/10981093, CCITT:  CCITT-FALSE (poly=0x1021 init=0xffff refin=false refout=false xorout=0x0000 check=0x29b1)
{
    uint8_t i;
    uint16_t wCrc = 0xffff;
    while (length--) {
        wCrc ^= *(unsigned char *)pData++ << 8;
        for (i=0; i < 8; i++)
            wCrc = wCrc & 0x8000 ? (wCrc << 1) ^ 0x1021 : wCrc << 1;
    }
    return wCrc & 0xffff;
}

void loop() {
//Nothing to see here

}
