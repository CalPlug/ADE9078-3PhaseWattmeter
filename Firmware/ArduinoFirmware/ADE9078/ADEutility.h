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
