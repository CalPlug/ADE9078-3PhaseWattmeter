//**************** Helper Functions *****************

bool checkBit(int data, int i) // return true if i'th bit is set, false otherwise
{
    // datasheet counts bits starting at 0. so the 2nd bit would be the 1 in 00100
    /* example: assume input.. data=5, i=2
    data = 5 ----> 00101
    00101 & 00100 ---> 00100 --> 4
    4 > 0, return true, the bit is set.
    */
    return ((data) & (1 << i)) > 0;
}

double decimalize(uint32_t input, double factor, double offset, bool absolutevalue) //This function converts to floating point with an optional linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
	#ifdef ADE9078_VERBOSE_DEBUG
	Serial.print(" ADE9078::calibration (decimalize) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	#ifdef ADE9078_Calibration
	Serial.print(" ADE9078::calibration (decimalize) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	//Warning, you can get overflows due to the printout of returned values in Arduino, See: http://forum.arduino.cc/index.php/topic,46931.0.html
	if(absolutevalue == 0){
	return (((double)input*factor)+offset); //standard y=mx+b calibration function applied to return
	}
	else{
		return (abs(((double)input*factor)+offset)); //standard y=mx+b calibration function applied to return
	}
}

double decimalizeSigned(int32_t input, double factor, double offset, bool absolutevalue) //This function converts to floating point with an optional linear calibration (y=mx+b) by providing input in the following way as arguments (rawinput, gain, offset)
{
	#ifdef ADE9078_VERBOSE_DEBUG
	Serial.print(" ADE9078::calibration (decimalize-signed) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
    #ifdef ADE9078_Calibration
	Serial.print(" ADE9078::calibration (decimalize-signed) and double type conversion function executed, RAW input: ");
	Serial.println(input);
	#endif
	//Warning, you can get overflows due to the printout of returned values in Arduino, See: http://forum.arduino.cc/index.php/topic,46931.0.html
	if(absolutevalue == 0){
	return (((double)input*factor)+offset); //standard y=mx+b calibration function applied to return
	}
	else{
		return (abs(((double)input*factor)+offset)); //standard y=mx+b calibration function applied to return
	}
}

//************************

// Crc found my michael. Apparently generated incorrect outputs- Comment by david, told by jacky
uint16_t crc16(unsigned char* data_p, uint16_t length){ //example CCITT 16 CRC function that returns unsigned 16 bit return given an array of input values and a length of the array.  Used  for checksum verification, borrowed Bob Felice, 2007 from example: http://www.drdobbs.com/implementing-the-ccitt-cyclical-redundan/199904926  ALSO  https://forum.arduino.cc/index.php?topic=123467.0
   unsigned char i;
   unsigned int data;
   unsigned int crc;
   #define POLY 0x8408 //deff. of the polynomial used for the calculation

   crc = 0xffff; //initial reset calculation value
	       if (length == 0)
              return (~crc);

       do {
              for (i = 0, data = (unsigned int)0xff & *data_p++; i < 8; i++, data >>= 1) //*data_p++ is often without ++ in other versions (this is an adjustment incrementer for the pointer in this example, based on how this algorithm is set up), see links above for details on this and implementation/usage
			  {
                    if ((crc & 0x0001) ^ (data & 0x0001))
                           crc = (crc >> 1) ^ POLY;
                    else
                           crc >>= 1;
              }
       } while (--length);

       crc = ~crc;

       data = crc;
       crc = (crc << 8) | (data >> 8 & 0xFF);

       return (crc);
}
/* New Algorithm From https://stackoverflow.com/questions/21252069/ccitt-crc-16-bit-start-value-0xffff/21263265#21263265
CRC Calculator: https://www.lammertbies.nl/comm/info/crc-calculation.html
Decimal to Hex Converter: https://cryptii.com/pipes/integer-encoder

uint16_t crc16(unsigned char* data_p, uint16_t length)
{
    unsigned char i;
    uint16_t data;
    uint16_t crc = 0xffff;

 if (length == 0)
    return crc;
while (length--) {
    crc ^= *(unsigned char *)data_p++ << 8;
    for (i=0; i < 8; i++)
        crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
}
return crc & 0xffff;
}
/*

// Crc algorithm supplied by jacky. Not compiling
/*
Crc source: http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html

uint16_t crc16(unsigned char* data_p)
{
    const uint16_t generator = 0x1021;
    uint16_t crc = 0;
    enum { maxbyteCount = sizeof data_p / sizeof data_p[0] };
    for (int j = 0; j<maxbyteCount; j++){
      crc ^= (uint16_t) (data_p[j] << 8);

    for (int i = 0; i < 8; i++)
    {
        if ((crc & 0x8000) != 0)
        {
            crc = (uint16_t)((crc << 1) ^ generator);
        }
        else
        {
            crc <<= 1;
        }
    }
    }

    return crc;
}
*/

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

//**************** End Helper Functions *****************
