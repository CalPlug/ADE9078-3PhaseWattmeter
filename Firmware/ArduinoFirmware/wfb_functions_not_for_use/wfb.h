//copy this stuff into ADE9078.h
void ADE9078::readOutWFBSPI();
void ADE9078::startFillingBuffer();
void ADE9078::stopFillingBuffer();
void ADE9078::sinc4Ouput();
void ADE9078::sinc4_IIR_LPFOutput();
void ADE9078::DSPwaveformOutput();

void ADE9078::stopWhenBufferIsFull();
void ADE9078::isPageFull(int);
void ADE9078::whichPageIsFull();
void ADE9078::stopFillingOnTrigger();

void ADE9078::readFixedRateData();
void ADE9078::readResampledData();
void ADE9078::burstAllChannels();
