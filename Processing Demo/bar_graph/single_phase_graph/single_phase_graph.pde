//ADE9078 single phase bar graph visulization for fft
//Enoch Chau 2019

import processing.serial.*;

Serial myPort;

float maxFreq = 500;
float maxValue = 100000;
int maxFreqINT = 500;
int maxValueINT = 100000;

float[]decimalAv = new float[maxFreqINT*2];

void mapping(float decimal[],float rectWidth, float rectHeight){
  int i;
  for(i=0; i<decimal.length;i+=2){
    rect((decimal[i]*rectWidth*maxFreq)+(width)+(rectWidth)+rectWidth, height - decimal[i+1]*rectHeight , rectWidth , decimal[i+1]*rectHeight);
  }
  //draw a black box at the end of each value for cleanliness
  fill(0);
  rect(width + (rectWidth), 0, rectWidth, height);
}

void s2f_array(String header, String inString_parts[], String sub_string[], float output_array[]){
    int i;
    if(header.equals(inString_parts[0]) == true ){
    arrayCopy(inString_parts , 1, sub_string, 0, sub_string.length);
    for(i=0; i<sub_string.length; i++){
      output_array[i] = float(sub_string[i]);
    }
  }
}

void zeroArray(float array[]){
  int i;
  for (i = 0; i < array.length; i++){
    array[i] = 0;
  }
}

void setup(){
  size (1600,900);
  String usingSerial = Serial.list()[0];
  myPort = new Serial(this, usingSerial, 115200);
  
  zeroArray(decimalAv);
  
  myPort.bufferUntil('$');
}

void draw(){
  background(255);
  stroke(0);
  float rectWidth = width/maxFreq;
  float rectHeight = height/maxValue;
  fill(0, 191, 255);
  
  mapping(decimalAv,rectWidth,rectHeight);  
}

void serialEvent(Serial myPort){
  int i;
  
  String[] Av_string = new String[maxFreqINT*2];
  
  String inString = myPort.readStringUntil('$');
  println(inString);
  
  if (inString != null){
    String[] inStringParts = splitTokens(inString,":,;$\n\r");
    
    for(i=0; i<inStringParts.length; i++){
      print(inStringParts[i]);
      print(' ');
    }
    println();  
    s2f_array("Av", inStringParts, Av_string, decimalAv);
    
    for (i=0; i<decimalAv.length; i++){
      print(decimalAv[i]);
      print(' ');
    }
  }
}
