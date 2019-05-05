//remember to put these functions into the header file under the ADE9078 class


//Waveform Buffer Filling Indication—Fixed Data Rate Samples p.68
//set bits in WFG_PG_IRQEN to get a notification when a page is full
void ADE9078::isPageFull(int page){
  uint16_t hex_page = 0;
  hex_page = hex_page | (1<<page);
  spiWrite16(WFB_PG_IRQEN_16, hex_page);
  Serial.print("You will be notified when this page is full: ");
  Serial.print(page);
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

//STOP WHEN BUFFER IS FULL MODE
//mode 0
void ADE9078::stopWhenBufferIsFull(){
  spiWrite16(WFB_CFG_16, (spiRead16(WFB_CFG_16) | 0x0020) & ~(0x00C0)); //WF_CAP_SEL = 1 and the WF_MODE bits = 00
  Serial.println("Mode 0: stop when buffer is full, notification given when buffer is full");
  isPageFull(15);
}

void ADE9078::startFillingBuffer(){
  spiWrite16(WFB_CFG_16, spiRead16(WFB_CFG_16) | 0x0010);//set WF_CAP_EN bit to 1 in the WFB_CFG register to start filling the buffer from Address 0x800.
  Serial.println("filling WFB from address 0x800");
}

//perform next fill for mode 0, restart fill for mode 1,2,3
void ADE9078::restartFill(){
  spiWrite16(WFB_CFG_16, spiRead16(WFB_CFG_16) & ~(0x0010);//set WF_CAP_EN bit to 0 in the WFB_CFG register
  Serial.print("last page to be filled was: ")
  whichPageIsFull();
  Serial.println("buffer is being reset");
  startFillingBuffer();
}

//CONTINUOUS FILL MODE
//mode 1: stop filling on trigger
//It is recommended to use this mode to analyze the ADC samples leading up to an event of interest.
void ADE9078::stopFillingOnTrigger(){
  spiWrite16(WFB_CFG_16, ((spiRead(WFB_CFG_16) | 0x0020) | 0x0040) & ~(0x0080)); //WF_CAP_SEL = 1 and the WF_MODE bits = 01
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
  switch(event){
    case 3 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0008);
      Serial.println("Trigger Event 3 ZXIA ZX event in Phase A current ENABLED");
      break;
    case 4 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0010);
      Serial.println("Trigger Event 4 ZXIB ZX event in Phase B current ENABLED");
      break;
    case 5 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0020);
      Serial.println("Trigger Event 5 ZXIC ZX event in Phase C current ENABLED");
      break;
    case 6 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0040);
      Serial.println("Trigger Event 6 ZXVA ZX event in Phase A voltage ENABLED");
      break;
    case 7 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0080);
      Serial.println("Trigger Event 7 ZXVB ZX event in Phase B voltage ENABLED");
      break;
    case 8 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0100);
      Serial.println("Trigger Event 8 ZXVC ZX event in Phase C voltage ENABLED");
      break;
    case 9 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0200);
      Serial.println("Trigger Event 9 ZXCOMB ZX on combined signal from VA, VB, VC ENABLED");
      break;
    case 10: spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) | 0x0400);
      Serial.println("Trigger Event 10, WFB has been stopped");
      break;
    default: Serial.println("invalid trigger event");
  }
}

//reset all trigger events
void ADE9078::triggeredEventResetAll(){
  spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x07F8) );//reset bits [3:10] in WFB_TRG_CFG_16
  Serial.print("All WFB trigger events have been reset");
}

//reset specific trigger events
void ADE9078::resetTriggeredEvent(){
  switch(event){
    case 3 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0008));
      Serial.println("Trigger Event 3 ZXIA ZX event in Phase A current DISABLED");
      break;
    case 4 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0010);
      Serial.println("Trigger Event 4 ZXIB ZX event in Phase B current DISABLED");
      break;
    case 5 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0020);
      Serial.println("Trigger Event 5 ZXIC ZX event in Phase C current DISABLED");
      break;
    case 6 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0040);
      Serial.println("Trigger Event 6 ZXVA ZX event in Phase A voltage DISABLED");
      break;
    case 7 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0080);
      Serial.println("Trigger Event 7 ZXVB ZX event in Phase B voltage DISABLED");
      break;
    case 8 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0100);
      Serial.println("Trigger Event 8 ZXVC ZX event in Phase C voltage DISABLED");
      break;
    case 9 : spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0200);
      Serial.println("Trigger Event 9 ZXCOMB ZX on combined signal from VA, VB, VC DISABLED");
      break;
    case 10: spiWrite16(WFB_TRG_CFG_16, spiRead16(WFB_TRG_CFG_16) & ~(0x0400);
      Serial.println("Trigger Event 10, WFB has been started");
      break;
    default: Serial.println("invalid trigger event");
  }
}

//checks WFB_TRIG (bit 22 of STATUS0) and does an inturrupt event
void ADE9078::triggeredEventInturrupt(){}//IMPLEMENT THIS**

//we are now at the bottom of left collumn of page 69
