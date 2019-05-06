//remember to put these functions into the header file under the ADE9078 class

//**********************SET BIT FUNCTIONS**************************************/
// set a specific bit of a register to 1 for 16 bit register
void setBit1_16(uint16_t address, int bitPlace){
  uint16_t addressContent = spiRead16(address);

  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("The ");
  Serial.print(bitPlace);
  Serial.print("bit of ");
  Serial.print(address);
  Serial.println("will be set to 1");
  Serial.print("Original Register Value: ");
  Serial.println(addressContent);
  #endif

  addressContent = (addressContent | (0b1 << bitPlace));
  spiWrite16(address, addressContent);

  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("New Register Value: ");
  Serial.println(addressContent);
  #endif
}

//set a specific bit of a register to 0 for 16 bit register
void setBit0_16(uint16_t address, int bitPlace){
    uint16_t addressContent = spiRead16(address);

    #ifdef ADE9078_VERBOSE_DEBUG
    Serial.print("The ");
    Serial.print(bitPlace);
    Serial.print("bit of ");
    Serial.print(address);
    Serial.println("will be set to 0");
    Serial.print("Original Register Value: ");
    Serial.println(addressContent);
    #endif

    addressContent = (addressContent & ~(0b1<<bitPlace));
    spiWrite16(address, addressContent);

    #ifdef ADE9078_VERBOSE_DEBUG
    Serial.print("New Register Value: ");
    Serial.println(addressContent);
    #endif
}

//set a specific bit of a register to 1 for 32 bit register
void setBit1_32(uint16_t address, int bitPlace){
  uint32_t addressContent = spiRead32(address);
  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("The ");
  Serial.print(bitPlace);
  Serial.print("bit of ");
  Serial.print(address);
  Serial.println("will be set to 1");
  Serial.print("Original Register Value: ");
  Serial.println(addressContent);
  #endif

  addressContent = (addressContent | (0b1 << bitPlace));
  spiWrite32(address, addressContent);

  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("New Register Value: ");
  Serial.println(addressContent);
  #enfif
}

//set a specific bit of a register to 0 for 32 bit register
void setBit0_32(uint16_t address, int bitPlace){
  uint32_t addressContent = spiRead32(address);

  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("The ");
  Serial.print(bitPlace);
  Serial.print("bit of ");
  Serial.print(address);
  Serial.println("will be set to 0");
  Serial.print("Original Register Value: ");
  Serial.println(addressContent);
  #enfif

  addressContent = (addressContent & ~(0b1<<bitPlace));
  spiWrite32(address, addressContent);
  Serial.print(addressContent);

  #ifdef ADE9078_VERBOSE_DEBUG
  Serial.print("New Register Value: ");
  Serial.println(addressContent);
  #enfif
}
/******************************************************************************/
/********************************WFB FUNCTIONS*********************************/
/******************************************************************************/

//Setting up the WFB
//0. readOutWFBSPI() - set WF_IN_EN to 1 to read out through SPI
//1. stopFillingBuffer - this writes WFB_CAP_EN to 0
//2. choose what type of data you want to output
//3. select the mode you want the WFB in
//4. choose what channels you want to read from

//startFillingBuffer - this writes WFB_CAP_EN to 1


void ADE9078::readOutWFBSPI(){
  setBit1_16(WFB_CFG_16, 12);
  Serial.println("reading out of WFB using SPI");
}

//Start the WFB
void ADE9078::startFillingBuffer(){
  setBit1_16(WFB_CFG_16, 4);//set WF_CAP_EN bit to 1 in the WFB_CFG register to start filling the buffer from Address 0x800.
  Serial.println("filling WFB from address 0x800 (first register of page 1)");
}
// Stop the WFB
void ADE9078::stopFillingBuffer(){
  setBit0_16(WFB_CFG_16, 4);//set WF_CAP_EN bit to 0 in the WFB_CFG register
  Serial.println("waveform buffer is stopped");
  Serial.print("last page to be filled was: ")
  whichPageIsFull();
}
//see p.67 of datasheet
//fill WFB with data from Sinc4
void ADE9078::sinc4Ouput(){
  setBit0_16(WFB_CFG_16, 8);//WF_SRC bit to 00
  setBit0_16(WFB_CFG_16, 9);
}

//fill WFB with data from Sinc4+IIR LPF
void ADE9078::sinc4_IIR_LPFOutput(){
  setBit0_16(WFB_CFG_16,8);//WF_SRC bit to 10
  setBit1_16(WFB_CFG_16,9);
}

//fill WFB with data from Waveforms processed by DSP
void ADE9078::DSPwaveformOutput(){
  setBit1_16(WFB_CFG_16, 8);//WF_SRC bit to 11
  setBit1_16(WFB_CFG_16, 9);
}

//STOP WHEN BUFFER IS FULL MODE
//mode 0
void ADE9078::stopWhenBufferIsFull(){
  setBit1_16(WFB_CFG_16, 5); //WF_CAP_SEL = 1
  setBit0_16(WFB_CFG_16, 6); //WF_MODE bits = 00
  setBit0_16(WFB_CFG_16, 7);
  Serial.println("Mode 0: stop when buffer is full, notification given when buffer is full");
  isPageFull(15);
}


//Waveform Buffer Filling Indication—Fixed Data Rate Samples p.68
//set bits in WFB_PG_IRQEN to get a notification when a page is full
void ADE9078::isPageFull(int page){
  setBit1_16(WFB_PG_IRQEN_16, page);
  Serial.print("You will be notified when this page is full: ");
  Serial.println(page);
}

void ADE9078::whichPageIsFull(){
  uint16_t whichPage = spiRead16(WFB_TRG_STAT_16);
  whichPage = whichPage & 0xF000; //make all other bits 0 except Bits[15:12]
  whichPage >> 12;
  Serial.print("this page is full: ");
  Serial.println(whichPage);
}



//checks PAGE_FULL (bit 17 of STATUS0) and does an inturrupt event
void ADE9078::pageFullInturrupt(){} //** IMPLEMENT THIS!!!



//CONTINUOUS FILL MODE
//mode 1: stop filling on trigger
//It is recommended to use this mode to analyze the ADC samples leading up to an event of interest.
void ADE9078::stopFillingOnTrigger(){
  setBit1_16(WFB_CFG_16, 5); //WF_CAP_SEL = 1
  setBit1_16(WFB_CFG_16, 6); //WF_MODE bits = 01
  setBit0_16(WFB_CFG_16, 7);
  Serial.println("Mode 1: stop filling on trigger");
}

/*10 TRIG_FORCE Set this bit to trigger an event to stop
the waveform buffer filling
9 ZXCOMB ZX on combined signal from VA, VB, VC
8 ZXVC ZX event in Phase C voltage
7 ZXVB ZX event in Phase B voltage
6 ZXVA ZX event in Phase A voltage
5 ZXIC ZX event in Phase C current
4 ZXIB ZX event in Phase B current
3 ZXIA ZX event in Phase A current*/
void ADE9078::setTriggerEvent(int event){
  //setBit1_16(WFB_TRG_CFG_16, event);
  switch(event){
    case 3 : Serial.println("Trigger Event 3 ZXIA ZX event in Phase A current ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 4 : Serial.println("Trigger Event 4 ZXIB ZX event in Phase B current ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 5 : Serial.println("Trigger Event 5 ZXIC ZX event in Phase C current ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 6 : Serial.println("Trigger Event 6 ZXVA ZX event in Phase A voltage ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 7 : Serial.println("Trigger Event 7 ZXVB ZX event in Phase B voltage ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 8 : Serial.println("Trigger Event 8 ZXVC ZX event in Phase C voltage ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 9 : Serial.println("Trigger Event 9 ZXCOMB ZX on combined signal from VA, VB, VC ENABLED");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    case 10: Serial.println("Trigger Event 10, WFB has been stopped");
      setBit1_16(WFB_TRG_CFG_16, event);
      break;
    default: Serial.println("invalid trigger event");
  }
}

//reset all trigger events
void ADE9078::triggeredEventResetAll(){
  int i;
  for (i = 3, i == 10; i++){
      setBit0_16(WFB_TRG_CFG_16, i);
  }
  Serial.print("All WFB trigger events have been reset");
}

//reset specific trigger events
void ADE9078::resetTriggeredEvent(int event){
  //setBit0_16(WFB_TRG_CFG_16, event);
  switch(event){
    case 3 : Serial.println("Trigger Event 3 ZXIA ZX event in Phase A current DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 4 : Serial.println("Trigger Event 4 ZXIB ZX event in Phase B current DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 5 : Serial.println("Trigger Event 5 ZXIC ZX event in Phase C current DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 6 : Serial.println("Trigger Event 6 ZXVA ZX event in Phase A voltage DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 7 : Serial.println("Trigger Event 7 ZXVB ZX event in Phase B voltage DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 8 : Serial.println("Trigger Event 8 ZXVC ZX event in Phase C voltage DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 9 : Serial.println("Trigger Event 9 ZXCOMB ZX on combined signal from VA, VB, VC DISABLED");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    case 10: Serial.println("Trigger Event 10, WFB has been started");
      setBit0_16(WFB_TRG_CFG_16, event);
      break;
    default: Serial.println("invalid trigger event");
  }
}

//checks WFB_TRIG (bit 22 of STATUS0) and does an inturrupt event
void ADE9078::triggeredEventInturrupt(){}//IMPLEMENT THIS**

//we are now at the bottom of left collumn of page 69 - still have to implement the rest of mode 1
//still have to implement rest of mode 2 & 3 but i don't think we need it for now.

/*****************SPI BURST READ FOR WFB***************************************/
//read fixed Samples
void ADE9078::readFixedRateData(){
  setBit1_16(WFB_CFG_16, 5);
  Serial.println("reading fixed rate data");
}

//read resampled data
void ADE9078::readResampledData(){
  setBit0_16(WFB_CFG_16, 5);
  Serial.println("reading resampled data");
}

//see p.71
void ADE9078::burstAllChannels(){
  uint16_t writeValue = spiRead16(WFB_CFG_16);
  for (i = 0, i == 3, i++){
    writeValue = writeValue & ~(0b1<<i);
  }
  spiWrite16(WFB_CFG_16, writeValue);
  Serial.println("burst read all channels");
}
//implement the rest of the burst options
