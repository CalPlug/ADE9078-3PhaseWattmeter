 /*Calibrates ADE9000*/
/*The calibration inputs are stored in the ADE9000CalibrationInputs.h file. The phase and parameter being calibrated is input through the serial console*/
/*Calbration constants are computed and stored in the EEPROM */
/*Caibration should be done with the end application settings. If any  parameters(GAIN,High pass corner,Integrator settings) are changed, the device should be recalibrated*/
/*This application assumues the PGA_GAIN among all current channels is same.Also, the PGA_GAIN among all voltage channels should be same*/

#include <SPI.h>
#include <ADE9000RegMap.h>
#include <ADE9000API.h>
#include <ADE9000CalibrationInputs.h>
#include <math.h>
#include <Wire.h>


/*Function declerations*/
void ADE9000_calibrate();
void ADE9000_iGain_calibrate(int32_t *,int32_t *,int32_t *,int32_t *, int);     //Current gain calibration function
void ADE9000_vGain_calibrate(int32_t *,int32_t *,int32_t *,int32_t *, int);     //Voltage gain calibration function
void ADE9000_pGain_calibrate(int32_t *,int32_t *,int32_t *,int32_t *, float);   //Power gain calibration function
void ADE9000_phase_calibrate(int32_t *,int32_t *,int32_t *,int32_t *, int);     //Phase calibration function
void calibrationEnergyRegisterSetup();                                          //Setup of Energy registers used in calibration. Donot Edit
void getPGA_gain();
int8_t isRegisterPositive(int32_t);
void storeCalConstToEEPROM();


#define IGAIN_CAL_REG_SIZE 4  
int32_t xIgain_registers[IGAIN_CAL_REG_SIZE];   //order [AIGAIN, BIGAIN, CIGAIN, NIGAIN]
int32_t xIgain_register_address[IGAIN_CAL_REG_SIZE]=
         {ADDR_AIGAIN, ADDR_BIGAIN, ADDR_CIGAIN, ADDR_NIGAIN};   //order [AIGAIN, BIGAIN, CIGAIN, NIGAIN]
int32_t xIrms_registers[IGAIN_CAL_REG_SIZE];
int32_t xIrms_registers_address[IGAIN_CAL_REG_SIZE]= {ADDR_AIRMS, ADDR_BIRMS, ADDR_CIRMS, ADDR_NIRMS};

#define VGAIN_CAL_REG_SIZE 3
int32_t xVgain_registers[VGAIN_CAL_REG_SIZE];   //order [AVGAIN, BVGAIN, CVGAIN]
int32_t xVgain_register_address[VGAIN_CAL_REG_SIZE]={ADDR_AVGAIN, ADDR_BVGAIN, ADDR_CVGAIN};   //order [AVGAIN, BVGAIN, CVGAIN]
int32_t xVrms_registers[VGAIN_CAL_REG_SIZE];
int32_t xVrms_registers_address[VGAIN_CAL_REG_SIZE]= {ADDR_AVRMS, ADDR_BVRMS, ADDR_CVRMS};

#define PHCAL_CAL_REG_SIZE 3
int32_t xPhcal_registers[PHCAL_CAL_REG_SIZE];   //order [APHCAL, BPHCAL, CPHCAL]
int32_t xPhcal_register_address[PHCAL_CAL_REG_SIZE]={ADDR_APHCAL0, ADDR_BPHCAL0, ADDR_CPHCAL0};   //order [APHCAL, BPHCAL, CPHCAL]
int32_t xWATTHRHI_registers[PHCAL_CAL_REG_SIZE];  //Active energy registers
int32_t xWATTHRHI_registers_address[PHCAL_CAL_REG_SIZE]= {ADDR_AWATTHR_HI, ADDR_BWATTHR_HI, ADDR_CWATTHR_HI};
int32_t xVARHRHI_registers[PHCAL_CAL_REG_SIZE];
int32_t xVARHRHI_registers_address[PHCAL_CAL_REG_SIZE]= {ADDR_AVARHR_HI, ADDR_BVARHR_HI, ADDR_CVARHR_HI};

#define PGAIN_CAL_REG_SIZE 3
int32_t xPgain_registers[PGAIN_CAL_REG_SIZE];   //order [APGAIN, BPGAIN, CPGAIN]
int32_t xPgain_register_address[PGAIN_CAL_REG_SIZE]={ADDR_APGAIN, ADDR_BPGAIN, ADDR_CPGAIN};   //order [AVGAIN, BVGAIN, CVGAIN, NVGAIN]
//The Power gain calibration reads active energy registers. The content and address arrays are defined in the PHCAL section above

//Global variables
#define EGY_REG_SIZE 3
int8_t calCurrentPGA_gain=0;
int8_t calVoltagePGA_gain=0;
int32_t accumulatedActiveEnergy_registers[EGY_REG_SIZE];
int32_t accumulatedReactiveEnergy_registers[EGY_REG_SIZE];
uint32_t calibrationDataToEEPROM[CALIBRATION_CONSTANTS_ARRAY_SIZE];

ADE9000Class ade9000;
#define SPI_SPEED 5000000
#define CS_PIN 8
#define PM_1 4
#define IRQ0_INTERRUPT_PIN 2
#define INT_MODE FALLING
#define ACCUMULATION_TIME 5                 //accumulation time in seconds when EGY_TIME=7999, accumulation mode= sample based
#define EGY_INTERRUPT_MASK0 0x00000001      //Enable EGYRDY interrupt

enum CAL_STATE
{
  CAL_START,
  CAL_VI_CALIBRATE,
  CAL_PHASE_CALIBRATE,
  CAL_PGAIN_CALIBRATE,
  CAL_STORE,
  CAL_STOP,
  CAL_RESTART,
  CAL_COMPLETE
};


CAL_STATE CUR_STATE = CAL_START;   //current state is start

void setup() {
  
  pinMode(PM_1, OUTPUT);    //Set PM1 select pin as output 
  digitalWrite(PM_1, LOW);   //Set PM1 select pin high 
  delay(1000);
  Serial.begin(115200);
  ade9000.SPI_Init(SPI_SPEED,CS_PIN);
  ade9000.SetupADE9000();       /*Setup ADE9000. The setup parameters such as 
                                GAIN should not be changed after calibration. Recalibrate if any configuration affecting the digital datapath changes.*/
  calibrationEnergyRegisterSetup();
  getPGA_gain();  
  Wire.begin(); 
  ade9000.writeByteToEeprom(ADDR_EEPROM_WRITTEN_BYTE,~(EEPROM_WRITTEN)); //clear calibration done status 
}

void loop()
{
  delay(1000);
  ADE9000_calibrate();
}

void ADE9000_calibrate()
{
  float calPf ;  
  int16_t temp;
  char serialReadData;
  static int8_t calChannel = 0; //the channel being calibrated
  static int8_t channelCalLength = 1; //the length

  switch(CUR_STATE)
  {
      case CAL_START:       //Start
      Serial.println("Starting calibration process. Select one of the following {Start (Y/y) OR Abort(Q/q) OR Restart (R/r)}:");
      while (!Serial.available());  //wait for serial data to be available
      serialReadData = Serial.read();
      if(serialReadData == 'Y' || serialReadData == 'y')
        { 
           Serial.println("Enter the Phase being calibrated:{Phase A(A/a) OR Phase B(B/b) OR Phase C(C/c) OR Neutral(N/n) OR All Phases(D/d)}:");
           while(Serial.read()>=0);     //Flush any extra characters
           while (!Serial.available());  //wait for serial data to be available
           serialReadData = Serial.read(); 
           if(serialReadData == 'A' || serialReadData == 'a') 
              {
                Serial.println("Calibrating Phase A:");
                calChannel=0; 
                channelCalLength=1;
              }
           else if(serialReadData == 'B' || serialReadData == 'b') 
              {
                Serial.println("Calibrating Phase B:");
                calChannel=1;
                channelCalLength=1;
              } 
           else if(serialReadData == 'C' || serialReadData == 'c') 
              {
                Serial.println("Calibrating Phase C:");
                calChannel=2;
                channelCalLength=1;
              }
           else if(serialReadData == 'N' || serialReadData == 'n') 
              {
               // calChannel=0;
              //  channelCalLength=1;                    
              }
           else if(serialReadData == 'D' || serialReadData == 'd') 
              {
                Serial.println("Calibrating all phases:");
                calChannel=0; //Start from channel A
                channelCalLength=3;                    
              }
           else 
              {
                Serial.println("Wrong input");
                while(Serial.read()>=0)
                 {
                   temp = Serial.read();  //Read till the buffer is empty
                 }
                serialReadData=' ';
                break;                                             
              }
           
           CUR_STATE=CAL_VI_CALIBRATE;
           Serial.print("Starting calibration with ");
           Serial.print(NOMINAL_INPUT_VOLTAGE);
           Serial.print(" Vrms and ");
           Serial.print(NOMINAL_INPUT_CURRENT);
           Serial.println(" Arms");
           while(Serial.read()>=0)
             {
                temp = Serial.read();  //Read till the buffer is empty
             }
           serialReadData=' ';
           break;
        }
      else
        {
           if(serialReadData == 'Q' || serialReadData == 'q')
              {
                CUR_STATE=CAL_STOP;
                Serial.println("Aborting calibration");
                while(Serial.read()>=0)
                  {
                    temp = Serial.read();  //Read till the buffer is empty
                  }                
               serialReadData=' ';
               break;
              }
            else if(serialReadData == 'R' || serialReadData == 'r')
              {
                 CUR_STATE=CAL_RESTART;
                 while(Serial.read()>=0)
                  {
                    temp = Serial.read();  //Read till the buffer is empty
                  }
                  serialReadData=' ';
                  break;
              }
           else 
             {
                Serial.println("Wrong input");
                while(Serial.read()>=0)
                 {
                    temp = Serial.read();  //Read till the buffer is empty
                 }
                serialReadData=' ';
                break;
             }
        }

      break;
    
      case CAL_VI_CALIBRATE:   //Calibrate
      ADE9000_iGain_calibrate(&xIgain_registers[calChannel],&xIgain_register_address[calChannel], &xIrms_registers[calChannel], &xIrms_registers_address[calChannel], channelCalLength);       //Calculate xIGAIN
      ADE9000_vGain_calibrate(&xVgain_registers[calChannel], &xVgain_register_address[calChannel], &xVrms_registers[calChannel], &xVrms_registers_address[calChannel], channelCalLength);       //Calculate xVGAIN
      Serial.println("Current gain calibration completed");
      Serial.println("Voltage gain calibration completed");
      CUR_STATE=CAL_PHASE_CALIBRATE;
      break;
      
      case CAL_PHASE_CALIBRATE:
      Serial.println("Perform Phase calibration: Yes(Y/y) OR No (N/n): ");
      while(Serial.read()>=0);     //Flush any extra characters
      while (!Serial.available());  //wait for serial data to be available
      serialReadData = Serial.read();
      if(serialReadData == 'Y' || serialReadData == 'y')
        {
            Serial.println("Ensure Power factor is 0.5 lagging such that Active and Reactive energies are positive: Continue: Yes(Y/y) OR Restart (R/r): ");
            while(Serial.read()>=0);     //Flush any extra characters
            while(!Serial.available());  //Wait for new input
            serialReadData =Serial.read();
            if(serialReadData == 'Y' || serialReadData == 'y')
              {
               while(Serial.read()>=0); //Flush any extra characters            
                ADE9000_Phase_calibrate(&xPhcal_registers[calChannel],&xPhcal_register_address[calChannel], &accumulatedActiveEnergy_registers[calChannel], &accumulatedReactiveEnergy_registers[calChannel], channelCalLength);     //Calculate xPHCAL
               Serial.println("Phase calibration completed");
              }
            else 
              {
                if(serialReadData == 'R' || serialReadData == 'r')
                  {
                    CUR_STATE=CAL_RESTART;
                    while(Serial.read()>=0);     //Flush any extra characters               
                    break;
                  }
                  else 
                  {
                    while(Serial.read()>=0);     //Flush any extra characters                               
                    Serial.println("Wrong Input");
                    break;
                  }
              }           
          }
      else
        {
          if(serialReadData == 'N' || serialReadData == 'n')
            {
                while(Serial.read()>=0);     //Flush any extra characters                                               
                Serial.println("Skipping phase calibration ");
            }
          else 
            {                   

              while(Serial.read()>=0);     //Flush any extra characters                                               
              Serial.println("Wrong input");
              break;
             }
        }
      CUR_STATE = CAL_PGAIN_CALIBRATE;      
      break;       
      
      case CAL_PGAIN_CALIBRATE:   
      Serial.println("Starting Power Gain calibration");  
      Serial.println("Enter the Power Factor of inputs for xPGAIN calculation: 1(1) OR CalibratingAnglePF(0): ");
      while(Serial.read()>=0);
      while (!Serial.available());  //wait for serial data to be available
      serialReadData = Serial.read();
      if(serialReadData == '1')
        {
           while(Serial.read()>=0);
           calPf=1; 
        }
      else
        {
          if(serialReadData == '0')
            {
              while(Serial.read()>=0);
              calPf=CAL_ANGLE_RADIANS(CALIBRATION_ANGLE_DEGREES);
            }
          else
          {
             while(Serial.read()>=0);        
             Serial.println("Wrong input");
             break;
          }
  
        }      
      ADE9000_pGain_calibrate(&xPgain_registers[calChannel],&xPgain_register_address[calChannel],&accumulatedActiveEnergy_registers[calChannel],channelCalLength, calPf);
      Serial.println("Power gain calibration completed ");
      Serial.println("Calibration completed. Storing calibration constants to EEPROM ");
      CUR_STATE = CAL_STORE;      
      break; 
    
      case CAL_STORE:     //Store Constants to EEPROM
      storeCalConstToEEPROM();
      Serial.println("Calibration constants successfully stored in EEPROM. Exit Application");
      CUR_STATE = CAL_COMPLETE; 
      break;
    
      case CAL_STOP:    //Stop calibration
      Serial.println("Calibration stopped. Restart Arduino to recalibrate");
      CUR_STATE = CAL_COMPLETE; 
      break;
    
      case CAL_RESTART:    //restart
      Serial.println("Restarting calibration");
      CUR_STATE = CAL_START; 
      break;

      case CAL_COMPLETE:
      break;
      
      default:
      break;
      
  }
  
}


void ADE9000_iGain_calibrate(int32_t *igainReg, int32_t *igainRegAddress, int32_t *iRmsReg, int32_t *iRmsRegAddress, int arraySize)
{
  float temp;
  int32_t actualCodes;
  int32_t expectedCodes;
  int32_t registerReading;
  int32_t aigain;
  int i;

  temp=ADE9000_RMS_FULL_SCALE_CODES*CURRENT_TRANSFER_FUNCTION*calCurrentPGA_gain*NOMINAL_INPUT_CURRENT *sqrt(2); 
  expectedCodes= (int32_t) temp;  //Round off 
  Serial.print("Expected IRMS Code: "); 
  Serial.println(expectedCodes,HEX);
  for (i=0; i < arraySize ;i++)
    {
      actualCodes = ade9000.SPI_Read_32(iRmsRegAddress[i]);
      temp= (((float)expectedCodes/(float)actualCodes)-1)* 134217728;  //calculate the gain.
      igainReg[i] = (int32_t) temp; //Round off
      Serial.print("Channel ");
      Serial.print(i+1);
      Serial.print(" actual IRMS Code: "); 
      Serial.println(actualCodes,HEX);      
      Serial.print("Current Gain Register: "); 
      Serial.println(igainReg[i],HEX);
    }
}

void ADE9000_vGain_calibrate(int32_t *vgainReg, int32_t *vgainRegAddress, int32_t *vRmsReg, int32_t *vRmsRegAddress, int arraySize)
{
  float temp;
  int32_t actualCodes;
  int32_t expectedCodes;
  int32_t registerReading;
  int i;
  
  temp=ADE9000_RMS_FULL_SCALE_CODES*VOLTAGE_TRANSFER_FUNCTION*calVoltagePGA_gain*NOMINAL_INPUT_VOLTAGE*sqrt(2); 
  expectedCodes= (int32_t) temp;  //Round off
  Serial.print("Expected VRMS Code: "); 
  Serial.println(expectedCodes,HEX);  
  for (i=0; i < arraySize ;i++)
    {
      actualCodes = ade9000.SPI_Read_32(vRmsRegAddress[i]);
      temp= (((float)expectedCodes/(float)actualCodes)-1)* 134217728;  //calculate the gain.
      vgainReg[i] = (int32_t) temp; //Round off  
      Serial.print("Channel ");
      Serial.print(i+1);
      Serial.print(" actual VRMS Code: "); 
      Serial.println(actualCodes,HEX);       
      Serial.print("Voltage Gain Register: "); 
      Serial.println(vgainReg[i],HEX);
    }
}

void ADE9000_Phase_calibrate(int32_t *phcalReg,int32_t *phcalRegAddress,int32_t *accActiveEgyReg,int32_t *accReactiveEgyReg, int arraySize)
{
  Serial.println("Computing phase calibration registers..."); 
  delay((ACCUMULATION_TIME+1)*1000); //delay to ensure the energy registers are accumulated for defined interval
  float errorAngle;
  float errorAngleDeg;
  float omega;
  double temp;
  double temp1;
  double temp2;
  int32_t actualActiveEnergyCode;
  int32_t actualReactiveEnergyCode; 
  int32_t phcalREG;
  int i;
  omega = (float)2 *(float)3.14159*(float) INPUT_FREQUENCY /(float)ADE90xx_FDSP;
  

  for (i=0; i < arraySize ;i++)
    {
        actualActiveEnergyCode = accActiveEgyReg[i];
        actualReactiveEnergyCode = accReactiveEgyReg[i];
        errorAngle = (double)-1 * atan( ((double)actualActiveEnergyCode*(double)sin(CAL_ANGLE_RADIANS(CALIBRATION_ANGLE_DEGREES))-(double)actualReactiveEnergyCode*(double)cos(CAL_ANGLE_RADIANS(CALIBRATION_ANGLE_DEGREES)))/((double)actualActiveEnergyCode*(double)cos(CAL_ANGLE_RADIANS(CALIBRATION_ANGLE_DEGREES))+(double)actualReactiveEnergyCode*(double)sin(CAL_ANGLE_RADIANS(CALIBRATION_ANGLE_DEGREES))));
        temp = (((double)sin((double)errorAngle-(double)omega)+(double)sin((double)omega))/((double)sin(2*(double)omega-(double)errorAngle)))*134217728;
        phcalReg[i]= (int32_t)temp;
        errorAngleDeg = (float)errorAngle*180/3.14159;
        Serial.print("Channel ");
        Serial.print(i+1);        
        Serial.print(" actual Active Energy Register: "); 
        Serial.println(actualActiveEnergyCode,HEX);
        Serial.print("Channel ");
        Serial.print(i+1);                 
        Serial.print(" actual Reactive Energy Register: "); 
        Serial.println(actualReactiveEnergyCode,HEX);              
        Serial.print("Phase Correction (degrees): "); 
        Serial.println(errorAngleDeg,5);       
        Serial.print("Phase Register: "); 
        Serial.println(phcalReg[i],HEX);        
    }



}

void ADE9000_pGain_calibrate(int32_t *pgainReg, int32_t *pgainRegAddress, int32_t *accActiveEgyReg, int arraySize, float pGaincalPF)
{
  Serial.println("Computing power gain calibration registers...");
  delay((ACCUMULATION_TIME+1)*1000); //delay to ensure the energy registers are accumulated for defined interval
  int32_t expectedActiveEnergyCode;
  int32_t actualActiveEnergyCode;
  int i;
  float temp;
  temp = ((float)ADE90xx_FDSP * (float)NOMINAL_INPUT_VOLTAGE * (float)NOMINAL_INPUT_CURRENT * (float)CALIBRATION_ACC_TIME * (float)CURRENT_TRANSFER_FUNCTION *(float)calCurrentPGA_gain* (float)VOLTAGE_TRANSFER_FUNCTION *(float)calVoltagePGA_gain* (float)ADE9000_WATT_FULL_SCALE_CODES * 2 * (float)(pGaincalPF))/(float)(8192);
  expectedActiveEnergyCode = (int32_t)temp;
  Serial.print("Expected Active Energy Code: "); 
  Serial.println(expectedActiveEnergyCode,HEX);    
  
  for (i=0; i < arraySize ;i++)
    {
      actualActiveEnergyCode = accActiveEgyReg[i];

      temp= (((float)expectedActiveEnergyCode/(float)actualActiveEnergyCode)-1)* 134217728;  //calculate the gain.
      pgainReg[i] = (int32_t) temp; //Round off  
      Serial.print("Channel ");
      Serial.print(i+1); 
      Serial.print("Actual Active Energy Code: "); 
      Serial.println(actualActiveEnergyCode,HEX);       
      Serial.print("Power Gain Register: "); 
      Serial.println(pgainReg[i],HEX);      
    }
}

void calibrationEnergyRegisterSetup()
{
  uint16_t epcfgRegister;
  ade9000.SPI_Write_32(ADDR_MASK0,EGY_INTERRUPT_MASK0);   //Enable EGYRDY interrupt
  ade9000.SPI_Write_16(ADDR_EGY_TIME,EGYACCTIME);   //accumulate EGY_TIME+1 samples (8000 = 1sec)
  epcfgRegister =  ade9000.SPI_Read_16(ADDR_EP_CFG);   //Read EP_CFG register
  epcfgRegister |= CALIBRATION_EGY_CFG;                //Write the settings and enable accumulation
  ade9000.SPI_Write_16(ADDR_EP_CFG,epcfgRegister);
  delay(2000); 
  ade9000.SPI_Write_32(ADDR_STATUS0,0xFFFFFFFF);
  attachInterrupt(digitalPinToInterrupt(IRQ0_INTERRUPT_PIN),updateEnergyRegisterFromInterrupt,INT_MODE);   
}


void getPGA_gain()
{
  int16_t pgaGainRegister;
  int16_t temp;  
  pgaGainRegister = ade9000.SPI_Read_16(ADDR_PGA_GAIN);  //Ensure PGA_GAIN is set correctly in SetupADE9000 function.
  Serial.print("PGA Gain Register is: ");
  Serial.println(pgaGainRegister,HEX);
  temp =    pgaGainRegister & (0x0003);  //extract gain of current channel
  if (temp == 0)  // 00-->Gain 1: 01-->Gain 2: 10/11-->Gain 4
      {
        calCurrentPGA_gain =1; 
      }
  else
      {
        if(temp==1)
        {
         calCurrentPGA_gain =2;  
        }
        else
        {
         calCurrentPGA_gain =4;  
        }
      }
  temp =    (pgaGainRegister>>8) & (0x0003); //extract gain of voltage channel
  if (temp == 0)
      {
        calVoltagePGA_gain =1; 
      }
  else
      {
        if(temp==1)
        {
         calVoltagePGA_gain =2;  
        }
        else
        {
         calVoltagePGA_gain =4;  
        }
      }  
}


void storeCalConstToEEPROM()
{
  //Arrange the data as formatted in 'ADE9000_Eeprom_CalibrationRegAddress' array.
  int8_t i;
  uint32_t temp;
  uint32_t checksum=0; //  adds all the gain and phase calibration registers. The truncated 32 bit data is stored as checksum in EEPROM.
  
  for(i=0;i<IGAIN_CAL_REG_SIZE;i++) //arrange current gain calibration registers
     {
       calibrationDataToEEPROM[i]=xIgain_registers[i];

     }
  for(i=0;i<VGAIN_CAL_REG_SIZE;i++) //arrange voltage gain calibration registers
     {
       calibrationDataToEEPROM[i+IGAIN_CAL_REG_SIZE]=xVgain_registers[i];

     }
  for(i=0;i<PHCAL_CAL_REG_SIZE;i++) //arrange phase calibration registers
     {
       calibrationDataToEEPROM[i+IGAIN_CAL_REG_SIZE+VGAIN_CAL_REG_SIZE]=xPhcal_registers[i];
     }     
  for(i=0;i<PGAIN_CAL_REG_SIZE;i++) //arrange phase calibration registers
     {
       calibrationDataToEEPROM[i+IGAIN_CAL_REG_SIZE+VGAIN_CAL_REG_SIZE+PHCAL_CAL_REG_SIZE]=xPgain_registers[i];
     }

  for(i=0;i<CALIBRATION_CONSTANTS_ARRAY_SIZE;i++)    
     {
       checksum +=calibrationDataToEEPROM[i];  
     }
     


     
  for(i=0;i<CALIBRATION_CONSTANTS_ARRAY_SIZE;i++)
     {
       ade9000.writeWordToEeprom(ADE9000_Eeprom_CalibrationRegAddress[i],calibrationDataToEEPROM[i]);
       delay(10);         
     }
  for(i=0;i<CALIBRATION_CONSTANTS_ARRAY_SIZE;i++)
     {
       temp= ade9000.readWordFromEeprom(ADE9000_Eeprom_CalibrationRegAddress[i]);
       delay(10);
       Serial.println(temp,HEX);         
     }      
  ade9000.writeWordToEeprom(ADDR_CHECKSUM_EEPROM,checksum);           //Save checksum to EEPROM
  ade9000.writeByteToEeprom(ADDR_EEPROM_WRITTEN_BYTE,EEPROM_WRITTEN); //Save calibration status in EEPROM      

             
}

int8_t isRegisterPositive(int32_t registerValue)
{
  if ((int32_t)registerValue <0) 
  return 1;
  else return 0;
}

void updateEnergyRegisterFromInterrupt()
{
  int8_t i;
  static int8_t count=0;
  static int32_t intermediateActiveEgy_Reg[EGY_REG_SIZE]={0};
  static int32_t intermediateReactiveEgy_Reg[EGY_REG_SIZE]={0};
  uint32_t temp;
  temp = ade9000.SPI_Read_32(ADDR_STATUS0);
  temp&=EGY_INTERRUPT_MASK0;
  if (temp==EGY_INTERRUPT_MASK0)
  {
      ade9000.SPI_Write_32(ADDR_STATUS0,0xFFFFFFFF);
      for(i=0;i<EGY_REG_SIZE;i++)
      {
        intermediateActiveEgy_Reg[i]+=ade9000.SPI_Read_32(xWATTHRHI_registers_address[i]);  //accumulate the registers
        intermediateReactiveEgy_Reg[i]+=ade9000.SPI_Read_32(xVARHRHI_registers_address[i]);   //accumulate the registers
      }
    
      if (count == (ACCUMULATION_TIME-1))  //if the accumulation time is reached, update the final values to registers
        {
          for(i=0;i<EGY_REG_SIZE;i++)
              {
                accumulatedActiveEnergy_registers[i] = intermediateActiveEgy_Reg[i];
                accumulatedReactiveEnergy_registers[i] = intermediateReactiveEgy_Reg[i];
                intermediateActiveEgy_Reg[i]=0;  // Reset the intermediate registers
                intermediateReactiveEgy_Reg[i]=0;   //Reset the intermediate registers
              }
          count=0;   //Reset counter
          return;   //exit function
        }
     count++;
     return;
  }


}



