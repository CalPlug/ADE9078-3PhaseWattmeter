//ADE9078 three phase bar graph visulization for fft
//Enoch Chau 2019

import processing.serial.*;

Serial myPort;

float maxFreq = 64;
float maxValue = 10000;
int sampleSize = 64;

float[]decimalAv = new float[2*sampleSize];
float[]decimalAi = new float[2*sampleSize];
float[]decimalBv = new float[2*sampleSize];
float[]decimalBi = new float[2*sampleSize];
float[]decimalCv = new float[2*sampleSize];
float[]decimalCi = new float[2*sampleSize];
float[]decimalNi = new float[2*sampleSize];
float[]decimalNv = new float[2*sampleSize];

int horiz = 4;
int vert = 2;

float errorThreshAv = 1000;
float errorThreshBv = 1000;
float errorThreshCv = 1000;
float errorThreshNv = 1000;
float errorThreshAi = 1000;
float errorThreshBi = 1000;
float errorThreshCi = 1000;
float errorThreshNi = 1000;

//make it look like 4x2
//Av(0,2) & Ai(1,2) ; Bv(2,2) & Bi(3,2)
//Cv(0,1) & Ci(1,1) ; Nv(2,1) & Ni(3,1)

//labels
void text_label(int placeX, int placeY, float rectWidth){
  fill(255);
  textSize(40);
  String label = "ERROR";
  if (placeX == 0 && placeY == 2){
    label = "Phase A - Voltage";
  }
  if (placeX == 1 && placeY == 2){
    label = "Phase A - Current";
  }
  if (placeX == 2 && placeY == 2){
    label = "Phase B - Voltage";
  }
  if (placeX == 3 && placeY == 2){
    label = "Phase B - Current";
  }
  if (placeX == 0 && placeY == 1){
    label = "Phase C - Voltage";
  }
  if (placeX == 1 && placeY == 1){
    label = "Phase C - Current";
  }
  if (placeX == 2 && placeY == 1){
    label = "Neutral Voltage";
  }
  if (placeX == 3 && placeY == 1){
    label = "Neutral Current";
  }
  if (placeY == 1){
    placeY = 2;
  }
  else if (placeY == 2){
    placeY = 1;
  }
  text(label, (maxFreq/2)*rectWidth+(placeX*width/horiz)-rectWidth*maxFreq/4, height - height/placeY+50);
}

void errorMap(float value, int placeX, int placeY ){
  float errorvalue = 0;
  if (placeX == 0 && placeY == 2){
    errorvalue = errorThreshAv;
  }
  if (placeX == 1 && placeY == 2){
    errorvalue = errorThreshAi;
  }
  if (placeX == 2 && placeY == 2){
    errorvalue = errorThreshBv;
  }
  if (placeX == 3 && placeY == 2){
    errorvalue = errorThreshBi;
  }
  if (placeX == 0 && placeY == 1){
    errorvalue = errorThreshCv;
  }
  if (placeX == 1 && placeY == 1){
    errorvalue = errorThreshCi;
  }
  if (placeX == 2 && placeY == 1){
    errorvalue = errorThreshNv;
  }
  if (placeX == 3 && placeY == 1){
    errorvalue = errorThreshNi;
  }
  if (value > errorvalue){
    fill(255,0,0);
  }
  else{
    fill(51,255,102);
  }
}
void mapping(float decimal[],float rectWidth, float rectHeight, int placeX, int placeY){
  int i;
  text_label(placeX,placeY,rectWidth);
  fill(51,255,102);//replace this with error detection function
  for(i=0; i<decimal.length;i+=2){
    if (i > 63){ //we only want to look at higher frequencies
      errorMap(decimal[i+1],placeX, placeY);
    }
    else{
      fill(51,255,102);
    }
    rect((i/2)*rectWidth + (placeX*width/horiz), height/placeY - decimal[i+1]*rectHeight, rectWidth , decimal[i+1]*rectHeight);
  }
}

void s2f_array(String header, String inString_parts[], float output_array[]){
    int i;
    if(header.equals(inString_parts[0]) == true ){
      for (i = 0; i<output_array.length; i++){
          output_array[i] = float(inString_parts[i+1]);
          print(output_array[i]);
          print(" ");
      }
      print("\n");
    }
}

//for processing Nv (neutral Voltage)
void array3Sum(float A_in[], float B_in[], float C_in[], float total_out[]){
  int i;
  //sum up total value
  for(i=1;i<=total_out.length;i+=2){
    total_out[i] = (A_in[i]+B_in[i]+C_in[i]);
  }
  //set up frequencies
  for (i=0;i<total_out.length;i+=2){
    total_out[i] = A_in[i];
  }
}

void zeroArray(float array[]){
  int i;
  for (i = 0; i < array.length; i++){
    array[i] = 0;
  }
}

void arraySetup(){
  zeroArray(decimalAv);
  zeroArray(decimalBv);
  zeroArray(decimalCv);
  zeroArray(decimalNv);
  
  zeroArray(decimalAi);
  zeroArray(decimalBi);
  zeroArray(decimalCi);
  zeroArray(decimalNi);
}

void setup(){
  size (3000,1600);
  String usingSerial = Serial.list()[0];
  myPort = new Serial(this, usingSerial, 115200);//this is the buad rate for ADE9078
  arraySetup();
  myPort.bufferUntil('$');
}

void draw(){
  float rectWidth = width/(maxFreq*horiz);
  float rectHeight = height/(maxValue*vert);
  background(128,128,128);
  stroke(0);
  fill(0);
  strokeWeight(1);
  mapping(decimalAv,rectWidth,rectHeight, 0,2);
  mapping(decimalAi,rectWidth,rectHeight, 1,2);
  
  mapping(decimalBv,rectWidth,rectHeight, 2,2);
  mapping(decimalBi,rectWidth,rectHeight, 3,2);
  
  mapping(decimalCv,rectWidth,rectHeight, 0,1);
  mapping(decimalCi,rectWidth,rectHeight, 1,1);
  
  mapping(decimalNv,rectWidth,rectHeight, 2,1);
  mapping(decimalNi,rectWidth,rectHeight, 3,1);
  
  strokeWeight(2);
  line(width/4,0,width/4,height);
  line(width/2,0,width/2,height);
  line(width*3/4,0,width*3/4,height);
  line(0,height/2, width, height/2);
}

void serialEvent(Serial myPort){
  int i;
    
  String inString = myPort.readStringUntil('$');
  println(inString);
  
  if (inString != null){
    String[] inStringParts = splitTokens(inString,":,;$\n\r");
    
    for(i=0; i<inStringParts.length; i++){
      print(inStringParts[i]);
      print(' ');
    }
    println();  
    s2f_array("Av", inStringParts, decimalAv);
    s2f_array("Ai", inStringParts, decimalAi);
    
    s2f_array("Bv", inStringParts, decimalBv);
    s2f_array("Bi", inStringParts, decimalBi);
    
    s2f_array("Cv", inStringParts, decimalCv);
    s2f_array("Ci", inStringParts, decimalCi);
    
    s2f_array("Ni", inStringParts, decimalNi);
    
    array3Sum(decimalAv, decimalBv, decimalCv, decimalNv);
    
    for (i=0; i<decimalAv.length; i++){
      print(decimalAv[i]);
      print(' ');
    }
  }
}
