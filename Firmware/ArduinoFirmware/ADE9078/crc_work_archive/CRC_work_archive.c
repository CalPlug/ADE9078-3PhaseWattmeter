CRC-XMODEM (MSB First)
Source: http://reveng.sourceforge.net/crc-catalogue/16.htm#crc.cat.crc-16-xmodem
Implementation Code From https://stackoverflow.com/questions/21252069/ccitt-crc-16-bit-start-value-0xffff/21263265#21263265
CRC Calculator: https://www.lammertbies.nl/comm/info/crc-calculation.html
Decimal to Hex Converter: https://cryptii.com/pipes/integer-encoder

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
