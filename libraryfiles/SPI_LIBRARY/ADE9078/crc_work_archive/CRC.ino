void setup() {
  Serial.begin(9600);
}
void loop() {
  unsigned char data_p[] = {"0000000100000010"};
  Serial.println(crc16(data_p,sizeof(data_p)-1));
}
uint16_t crc16(unsigned char* data_p, uint16_t length)
{
    unsigned char i;
    uint16_t data;
    uint16_t crc = 0;     //change 0 to 0xffff for implementation of CRC-CCITT-False Algorithm (more info on sourceforge)

 if (length == 0)
    return crc;
while (length--) {
    crc ^= *(unsigned char *)data_p++ << 8;
    for (i=0; i < 8; i++)
        crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
}
return crc;             //change crc to crc & 0xffff for implementation of CRC-CCITT-False Algorithm (more info on sourceforge)

}

uint16_t ADE9078::spiRead16CRC(uint16_t address, bool &ValidCRC) { //This is the algorithm that reads from a register in the ADE9078. The arguments are the MSB and LSB of the address of the register respectively. The values of the arguments are obtained from the list of functions above.
//This function provides CRC checking for registers that allow this functionality in non-burst mode. The validity of the return will be passed by a reference argument, Call with address and a valid response check, call as: value = object.spiRead16CRC(Address, CRCcheck);
    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16-CRC function started ");
    #endif
   //Prepare the 12 bit command header from the inbound address provided to the function
   uint16_t temp_address, readval_unsigned, CRC_Value;
   uint16_t returnedCRC = 0;
   static unsigned char CRCCheckInput[2]; //define the holder for the input to the CRC check function, unsigned char array used for holding input and arranging bit order
   temp_address = (((address << 4) & 0xFFF0)+8); //shift address  to align with cmd packet, convert the 16 bit address into the 12 bit command header. + 8 for isRead versus write
   byte commandHeader1 = functionBitVal(temp_address, 1); //lookup and return first byte (MSB) of the 12 bit command header, sent first
   byte commandHeader2 = functionBitVal(temp_address, 0); //lookup and return second byte (LSB) of the 12 bit command header, sent second

    byte one, two; //holders for the read values from the SPI Transfer
  byte crcOne, crcTwo; //holders for returned CRC values

  #ifdef ESP32ARCH  //example SPI routine for the ESP32
    spy = spiStartBus(VSPI, SPI_CLOCK_DIV16, SPI_MODE0, SPI_MSBFIRST); //Setup ESP32 SPI bus
    spiAttachSCK(spy, -1);
      spiAttachMOSI(spy, -1);
      spiAttachMISO(spy, -1);
      digitalWrite(_SS, LOW); //Bring SS LOW (Active)
      spiTransferByte(spy, commandHeader1); //Send MSB
      spiTransferByte(spy, commandHeader2);  //Send LSB
      one = spiTransferByte(spy, WRITE);  //dummy write MSB, read out MSB
      two = spiTransferByte(spy, WRITE);  //dummy write LSB, read out LSB
    crcOne = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC MSB
    crcTwo = spiTransferByte(spy, WRITE);  //dummy write LSB, read out CRC LSB
      digitalWrite(_SS, HIGH);  //Bring SS HIGH (inactive)
      spiStopBus(spy);
  #endif

  #ifdef AVRESP8266 //Arduino SPI Routine
    // beginTransaction is first
    SPI.beginTransaction(defaultSPISettings);  // Clock is high when inactive. Read at rising edge: SPIMODE3.
    digitalWrite(_SS, LOW);  //Enable data transfer by bringing SS line LOW
    SPI.transfer(commandHeader1);  //Transfer first byte (MSB), command
    SPI.transfer(commandHeader2);  ;//Transfer second byte (LSB), command
    //Read in values sequentially and bitshift for a 32 bit entry
    one = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    two = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
  crcOne = SPI.transfer(dummyWrite);  //MSB Byte 1  (Read in data on dummy write (null MOSI signal))
    crcTwo = SPI.transfer(dummyWrite);  //LSB Byte 2  (Read in data on dummy write (null MOSI signal))
    digitalWrite(_SS, HIGH);  //End data transfer by bringing SS line HIGH
    SPI.endTransaction();      // end SPI Transaction
  #endif

    #ifdef ADE9078_VERBOSE_DEBUG
     Serial.print(" ADE9078::spiRead16-CRC function details: ");
     Serial.print(" Command Header: ");
     Serial.print(commandHeader1, BIN);
     Serial.print(commandHeader2, BIN);
     Serial.print(" Address Byte 1(MSB)[HEX]: ");
     Serial.print(" Returned bytes (1(MSB) and 2) [HEX]: ");
     Serial.print(one, HEX); //print MSB
     Serial.print(" ");
     Serial.print(two, HEX);  //print LSB
     Serial.println(" ADE9078::spiRead16-CRC function completed ");
    #endif

  readval_unsigned = (one << 8);  //Process MSB  (Alternate bitshift algorithm)
    readval_unsigned = readval_unsigned + two;  //Process LSB
  CRC_Value = (crcOne << 8); //Push in first CRC value into the 16bit holder
  CRC_Value = CRC_Value + crcTwo;  //Process LSB for CRC
  //Load in forward into the CRC check - double check byte order!
  CRCCheckInput[0] = one; //load first value into the array
  CRCCheckInput[1] = two; //load second value into the array
  CRCCheckInput[2] = 0; //load terminal value into the array  (previously: CRCCheckInput[2] = NULL;)

  //Check the CRC value to see if the return and the CRC match on the received side, pad into a 32 bit return as part of a 32 bit character, MSB is first fed into the CRC algorithm, per page 64 of the datasheet, assume padding to 32 bits with 0's per algorithm approach
  returnedCRC = crc16(CRCCheckInput, (short)3); // enter CRC value into the check algorithm MSB first, the length is 2 bytes (16 bit), this is specified

  if (returnedCRC == CRC_Value) //check the returned CRC value to see if it matches the input CRC value
  {
  ValidCRC = 1; //value matches, return a 1 to indicate a match has taken place and the returned data is valid
  }
  else
  {
    ValidCRC = 0; //value does not match, return a 0 to indicate a match has not taken place and the returned data is invalid
  }

   #ifdef ADE9078_CRC_Output
   Serial.print(" Read 16-bit value fed into the CRC Check function[HEX]: ");
   Serial.print(readval_unsigned, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 1[HEX]: ");
   Serial.print(crcOne, BIN);
   Serial.print(" ADE9087 Read CRC Value Byte 2[HEX]: ");
   Serial.print(crcTwo, BIN);
   Serial.print(" ADE9087 Read CRC Value Combined[HEX]: ");
   Serial.print(CRC_Value, BIN);
   Serial.print(" Value returned from the 16 BIT CCITT CRC check function[HEX]: ");
   Serial.print(returnedCRC, BIN);
   Serial.print(" Determined to be a match?: ");
   Serial.println(ValidCRC, DEC);
   #endif

  return readval_unsigned;
}

byte functionBitVal(uint16_t addr, uint8_t byteVal)
{
//Returns as integer an address of a specified byte - basically a byte controlled shift register with "byteVal" controlling the byte that is read and returned
  uint16_t x = ((addr >> (8*byteVal)) & 0xff);

  #ifdef ADE9078_VERBOSE_DEBUG
   Serial.print(" ADE9078::functionBitVal function (separates high and low command bytes of provided addresses) details: ");
   Serial.print(" Address input (dec): ");
   Serial.print(addr, DEC);
   Serial.print(" Byte requested (dec): ");
   Serial.print(byteVal, DEC);
   Serial.print(" Returned Value (dec): ");
   Serial.print(x, DEC);
   Serial.print(" Returned Value (HEX): ");
   Serial.print(x, HEX);
   Serial.println(" ADE9078::functionBitVal function completed ");
  #endif

  return x;
}
