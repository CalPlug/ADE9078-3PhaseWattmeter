
#include <SPI.h>
#include  <ADE9000RegMap.h>
#include <ADE9000API.h>

/*Basic initializations*/
ADE9000Class ade9000;
#define SPI_SPEED 5000000     //SPI Speed
#define CS_PIN 8 //8-->Arduino Zero. 16-->ESP8266 
#define ADE9000_RESET_PIN 5 //Reset Pin on HW
#define PM_1 4              //PM1 Pin: 4-->Arduino Zero. 15-->ESP8266 

/*Structure decleration */
struct ActivePowerRegs powerRegs;     // Declare powerRegs of type ActivePowerRegs to store Active Power Register data
struct CurrentRMSRegs curntRMSRegs;   //Current RMS
struct VoltageRMSRegs vltgRMSRegs;    //Voltage RMS
struct VoltageTHDRegs voltageTHDRegsnValues; //Voltage THD
struct ResampledWfbData resampledData; // Resampled Data

/*Function Decleration*/
void readRegisterData(void);
void readResampledData(void);
void resetADE9000(void);

void setup() 
{
  Serial.begin(115200);
  pinMode(PM_1, OUTPUT);    //Set PM1 pin as output 
  digitalWrite(PM_1, LOW);   //Set PM1 select pin low for PSM0 mode
  pinMode(ADE9000_RESET_PIN, OUTPUT);
  digitalWrite(ADE9000_RESET_PIN, HIGH); 
  void resetADE9000(); 
  delay(1000);
  ade9000.SPI_Init(SPI_SPEED,CS_PIN); //Initialize SPI
  ade9000.SetupADE9000();             //Initialize ADE9000 registers according to values in ADE9000API.h
  //ade9000.SPI_Write_16(ADDR_RUN,0x1); //Set RUN=1 to turn on DSP. Uncomment if SetupADE9000 function is not used
  Serial.print("RUN Register: ");
  Serial.println(ade9000.SPI_Read_16(ADDR_RUN),HEX);
}

void loop() {
  readRegisterData();
  readResampledData();
  delay(10000);
}

void readRegisterData()
{
 /*Read and Print Specific Register using ADE9000 SPI Library */
  Serial.print("AIRMS: "); 
  Serial.println(ade9000.SPI_Read_32(ADDR_AIRMS),HEX); // AIRMS

 /*Read and Print RMS & WATT Register using ADE9000 Read Library*/
  ade9000.ReadVoltageRMSRegs(&vltgRMSRegs);    //Template to read Power registers from ADE9000 and store data in Arduino MCU
  ade9000.ReadActivePowerRegs(&powerRegs);
  Serial.print("AVRMS:");        
  Serial.println(vltgRMSRegs.VoltageRMSReg_A); //Print AVRMS register
  Serial.print("AWATT:");        
  Serial.println(powerRegs.ActivePowerReg_A); //Print AWATT register
}

void readResampledData()
{
  uint32_t temp;
/*Read and Print Resampled data*/
  /*Start the Resampling engine to acquire 4 cycles of resampled data*/
  ade9000.SPI_Write_16(ADDR_WFB_CFG,0x1000);
  ade9000.SPI_Write_16(ADDR_WFB_CFG,0x1010);
  delay(100); //approximate time to fill the waveform buffer with 4 line cycles  
  /*Read Resampled data into Arduino Memory*/
  ade9000.SPI_Burst_Read_Resampled_Wfb(0x800,WFB_ELEMENT_ARRAY_SIZE,&resampledData);   // Burst read function
  
  for(temp=0;temp<WFB_ELEMENT_ARRAY_SIZE;temp++)
    {
      Serial.print("VA: ");
      Serial.println(resampledData.VA_Resampled[temp],HEX);
      Serial.print("IA: ");
      Serial.println(resampledData.IA_Resampled[temp],HEX);
      Serial.print("VB: ");
      Serial.println(resampledData.VB_Resampled[temp],HEX);
      Serial.print("IB: ");
      Serial.println(resampledData.IB_Resampled[temp],HEX);
      Serial.print("VC: ");
      Serial.println(resampledData.VC_Resampled[temp],HEX);
      Serial.print("IC: ");
      Serial.println(resampledData.IC_Resampled[temp],HEX);
      Serial.print("IN: ");
      Serial.println(resampledData.IN_Resampled[temp],HEX);
   } 

}

void resetADE9000(void)
{
 digitalWrite(ADE9000_RESET_PIN, LOW);
 delay(50);
 digitalWrite(ADE9000_RESET_PIN, HIGH);
 delay(1000);
 Serial.println("Reset Done");
}




