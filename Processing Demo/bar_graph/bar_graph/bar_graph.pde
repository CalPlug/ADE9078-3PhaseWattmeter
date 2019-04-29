//for use with ADE 9078 - 3phase watt meter
//bar graph visulization of fft
//Written by Enoch Chau - 2019
import processing.serial.*;
//If the program is getting serialEvent errors, just keep restarting it until it works. I think it has something to do with sending in corrupted data.
//**IMPORANT: make sure that max frequency and max values match with ADE9078 output or you will have error!
int maxfreq = 10; //assume frequencies can range from 0 to 1 in increments of 0.1
int maxvalue = 100;//assume values can range from 0 to 100 in increments of 1

//define the error thresholds
float errorThreshAv = 30;
float errorThreshBv = 40;
float errorThreshCv = 30;
float errorThreshVsum = 90;
float errorThreshAi = 30;
float errorThreshBi = 30;
float errorThreshCi = 30;
float errorThreshIsum = 90;
float errorThreshAp = 66;
float errorThreshBp = 35;
float errorThreshCp = 34;
float errorThreshPsum = 120;

//**if you change window dimension, make sure to change scale to make everything line up
float width_scale = 13.2;
float height_scale = 3;

Serial myPort;

//each frequency has a value associated with it so there are a total of 2*maxfreq values in the decimal array
float[]decimalAv = new float[maxfreq*2];
float[]decimalBv = new float[maxfreq*2];
float[]decimalCv = new float[maxfreq*2];
float[]decimalVsum = new float[maxfreq*2];

float[]decimalAi = new float[maxfreq*2];
float[]decimalBi = new float[maxfreq*2];
float[]decimalCi = new float[maxfreq*2];
float[]decimalIsum = new float[maxfreq*2];

float[]decimalAp = new float[maxfreq*2];
float[]decimalBp = new float[maxfreq*2];
float[]decimalCp = new float[maxfreq*2];
float[]decimalPsum = new float[maxfreq*2];


//vertical text
void vertText(String text, float x, float y){
  textAlign(CENTER,BOTTOM);

  pushMatrix();
  translate(x,y);
  rotate(-HALF_PI);
  text(text,0,0);
  popMatrix();
}

//check for errors, turn the bar red if there is an error
//returns errorvalue for further computations
float errorDetection(float value, int place){
  float errorvalue;  
  switch (place){
    case 0 : errorvalue = errorThreshAv;
      break;
    case 1 : errorvalue = errorThreshBv;
      break;
    case 2 : errorvalue = errorThreshCv;
      break;
    case 3 : errorvalue = errorThreshVsum;
      break;
    case 4 : errorvalue = errorThreshAi;
      break;
    case 5 : errorvalue = errorThreshBi;
      break;
    case 6 : errorvalue = errorThreshCi;
      break;
    case 7 : errorvalue = errorThreshIsum;
      break;
    case 8 : errorvalue = errorThreshAp;
      break;
    case 9 : errorvalue = errorThreshBp;
      break;
    case 10 : errorvalue = errorThreshCp;
      break;
    case 11 : errorvalue = errorThreshPsum;
      break;
    default: errorvalue = 0; //to avoid errors
      break;
  }
  if (value > errorvalue){
    fill(255,0,0);
  }
  else{
    fill(0,255,0);
  }
  return errorvalue;
}

//labels collumns
void text_label(int place,float rect_width){
    //text labels for each bar graph
  fill(255);
  textSize(26);
  String label;
  switch (place){
    case 0 : label = "Phase A - Voltage";
      break;
    case 1 : label = "Phase B - Voltage";
      break;
    case 2 : label = "Phase C - Voltage";
      break;
    case 3 : label = "Neutral Voltage";
      break;
    case 4 : label = "Phase A - Current";
      break;
    case 5 : label = "Phase B - Current";
      break;
    case 6 : label = "Phase C - Current";
      break;
    case 7 : label = "Neutral Current";
      break;
    case 8 : label = "Phase A - Power";
      break;
    case 9 : label = "Phase B - Power";
      break;
    case 10 : label = "Phase C - Power";
      break;
    case 11 : label = "Neutral Power";
      break;
    default: label = "place holder"; //to avoid errors
      break;
  }
  vertText(label,(place*width/width_scale) + (place*rect_width)+rect_width+2, 0.5*height);
}
//when mapping:
//we look at decimalAv[0] = frequncy to map to (x-coordinate)
//assuming that values come in order of frequency, we don't need to use the x-coordinate
//we then look at decimalAv[1] = value of frequnecy (y-coordinate)
//------------------------------------------------------------  
//inputs: decimal_array, placement on screen, rect_width, rect_height
//for place: Av = 0, Bv = 1, Cv = 2...
void mapping(float decimal[], int place,float rect_width, float rect_height){
  int i;
  float error_value = 0;
  for(i=0; i<decimal.length;i+=2){
    error_value = errorDetection(decimal[i+1],place);
    rect((decimal[i]*rect_width*maxfreq)+(place*width/width_scale)+(place*rect_width)+rect_width, height - decimal[i+1]*rect_height , rect_width , decimal[i+1]*rect_height);
  }
  //draw a black box at the end of each value for cleanliness
  fill(0);
  rect((place*width/width_scale) + (place*rect_width), 0, rect_width, height);
  //error line
  line((place*width/width_scale) + (place*rect_width)+rect_width, height - int(error_value)*rect_height , (place*width/width_scale) + (place*rect_width)+rect_width + rect_width*(maxfreq+1) , height - int(error_value)*rect_height);
  //label
  text_label(place,rect_width);
}


//The structure of a packet is:
//for example: finding A_Voltage
//inString_parts[0] = 'Av'
//inString_parts[1] = '0' (frequency)
//inString_parts[2] = '1' (value)
//-----------------------------------------------------
//checks the header of the input String
//removes the header using arrayCopy
//casts the string array to a float array
void s2f_array(String header, String inString_parts[], String sub_string[], float output_array[]){
    int i;
    if(header.equals(inString_parts[0]) == true ){
    arrayCopy(inString_parts , 1, sub_string, 0, sub_string.length);
    //for(i=0; i<Av_string.length; i++){
    //  print("Av_string:");
    //  println(i);
    //  println(Av_string[i]);
    //}
    for(i=0; i<sub_string.length; i++){
      output_array[i] = float(sub_string[i]);
      //print("decimalAv:");
      //println(i);
      //println(decimalAv[i]);
    }
  }
}

//create the total average value arrays
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

//initilize arrays to zero
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
  zeroArray(decimalVsum);
  
  zeroArray(decimalAi);
  zeroArray(decimalBi);
  zeroArray(decimalCi);
  zeroArray(decimalIsum);
  
  zeroArray(decimalAp);
  zeroArray(decimalBp);
  zeroArray(decimalCp);
  zeroArray(decimalPsum);
}

void setup(){
  //**if you change window dimension, make sure to change scale to make everything line up
  size(2990,1600); //make a window: each value (Av,Bv,Ai,Ap,Total voltage etc.) gets (width/13)pixels x-direction & (height/3[regular] or height[total])pixels y-direction
  background(0); //set initial background
  
  //list all serial ports
  println(Serial.list());
  
  //using serial port 1 (index 0)
  String usingSerial = Serial.list()[0];
  
  //initilize serial port
  myPort = new Serial(this,usingSerial,9600); //now looking at arduino serial port 1 at 9600Hz
  
  //set all arrays to zero
  arraySetup();
  
  //don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('$');
}

void draw(){
  background(128,128,128);
  stroke(0);
  strokeWeight(1);
  float rect_width = width/(width_scale*maxfreq);
  float rect_height = height/(maxvalue*height_scale);
  //draw black box at the front of the window
  fill(0);
  //rect(0, 0, rect_width, height);
  
  //mapping A-Voltage
  mapping(decimalAv,0,rect_width,rect_height);

  //mapping B-Voltage
  mapping(decimalBv,1,rect_width,rect_height);
  
  //mapping C-Voltage
  mapping(decimalCv,2,rect_width,rect_height);
  
  //mapping total voltage
  mapping(decimalVsum,3,rect_width,rect_height);
  
  //mapping A-Current
  mapping(decimalAi,4,rect_width,rect_height);
  
  //mapping B-Current
  mapping(decimalBi ,5,rect_width,rect_height);
  
  //mapping C-Current
  mapping(decimalCi,6,rect_width,rect_height);
  
  //mapping Total current
  mapping(decimalIsum,7,rect_width,rect_height);
  
  //mapping A-Power
  mapping(decimalAp,8,rect_width,rect_height);
  
  //mapping B-Power
  mapping(decimalBp ,9,rect_width,rect_height);
  
  //mapping C-Power
  mapping(decimalCp,10,rect_width,rect_height);
  
  //mapping Total Power
  mapping(decimalPsum, 11, rect_width,rect_height);
}

void serialEvent (Serial myPort) {  
  int i;

  String[] Av_string = new String[maxfreq*2];
  String[] Bv_string = new String[maxfreq*2];
  String[] Cv_string = new String[maxfreq*2];  
  String[] Ai_string = new String[maxfreq*2];
  String[] Bi_string = new String[maxfreq*2];
  String[] Ci_string = new String[maxfreq*2];
  String[] Ap_string = new String[maxfreq*2];
  String[] Bp_string = new String[maxfreq*2];
  String[] Cp_string = new String[maxfreq*2];

  //data input as a string, comes in format: 
  //Ai:0,1;0.1,0;0.2,1;.....1,10.0$  (let's say up to 10 (so that's 100 points).. the end of the line is $)
  //(frequency,value) for 100 frequencies
  //let's assume Ai,Bi,Ci,Av,Bv,Cv,Ap,Bp,Cp
  //i = current; v = voltage; p = power
  
  //reads the serial port until $ (end of packet)
  String inString = myPort.readStringUntil('$');
  println(inString);
  //check if there is something in the string
  //some of the checks don't always work so they are commented out
  if (inString != null){ //&& (inString.charAt(0) == 'A' || inString.charAt(0) == 'B' || inString.charAt(0) == 'C')*/ && inString.charAt(inString.length()) == '$'){ 
    
    //break the string into parts dividing at : , ; $ \n \r
    //at the same time it removes those characters from the new string array
    String[] inString_parts = splitTokens(inString, ":,;$\n\r");
    
    //print each part of the array for debugging
    for(i=0; i<inString_parts.length; i++){
      print(inString_parts[i]);
      print(' ');
    }
    println();       

    //A_voltage
    s2f_array("Av", inString_parts, Av_string, decimalAv);
    
    //B_voltage
    s2f_array("Bv", inString_parts, Bv_string, decimalBv);
    
    //C_voltage
    s2f_array("Cv", inString_parts, Cv_string, decimalCv);
    
    //total voltage
    array3Sum(decimalAv, decimalBv, decimalCv, decimalVsum);
    
    //A_current
    s2f_array("Ai", inString_parts, Ai_string, decimalAi);
    
    //B_current
    s2f_array("Bi", inString_parts, Bi_string, decimalBi);
    
    //C_current
    s2f_array("Ci", inString_parts, Ci_string, decimalCi);
    
    //total current
    array3Sum(decimalAi, decimalBi, decimalCi, decimalIsum);
    
    //A_Power
    s2f_array("Ap", inString_parts, Ap_string, decimalAp);
    
    //B_Power
    s2f_array("Bp", inString_parts, Bp_string, decimalBp);
    
    //C_Power
    s2f_array("Cp", inString_parts, Cp_string, decimalCp);
    
    //total power
    array3Sum(decimalAp, decimalBp, decimalCp, decimalPsum);
  }
}
