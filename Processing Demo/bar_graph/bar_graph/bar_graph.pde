//Enoch Chau 2019
import processing.serial.*;

//**IMPORANT: make sure that max frequency and max values match with ADE9078 or you will have error!

int maxfreq = 10; //assume frequencies can range from 0 to 10 in increments of 0.1
int maxvalue = 100;//assume values can range from 0 to 100 in increments of 1
int errorvalue = 70;//if a frequncy has a value higher than this then there is something wrong with the power consumption

Serial myPort;

//each frequency has a value associated with it so there are a total of 2*maxfreq values in the decimal array
float[]decimalAv = new float[maxfreq*2];
float[]decimalBv = new float[maxfreq*2];
float[]decimalCv = new float[maxfreq*2];
float[]decimalAi = new float[maxfreq*2];
float[]decimalBi = new float[maxfreq*2];
float[]decimalCi = new float[maxfreq*2];
float[]decimalAp = new float[maxfreq*2];
float[]decimalBp = new float[maxfreq*2];
float[]decimalCp = new float[maxfreq*2];


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
void errorDetection(float value){
  if (value > errorvalue){
    fill(255,0,0);
  }
  else{
    fill(0,255,0);
  }
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
  for(i=0; i<maxfreq*2;i+=2){
    errorDetection(decimal[i+1]);
    rect((decimal[i]*rect_width*maxfreq)+(place*width/10)+(place*rect_width)+rect_width, height - decimal[i+1]*rect_height , rect_width , decimal[i+1]*rect_height);
    //print(decimal[i]*rect_width*maxfreq);
    //print(' ');
  }
  //println();
  //draw a black box at the end of each value for cleanliness
  fill(0);
  rect(rect_width*maxfreq + (place*width/10) + (place*rect_width)+rect_width, 0, rect_width, height);
  
  //text labels for each bar graph
  fill(255);
  textSize(32);
  String label;
  switch (place){
    case 0 : label = "A-Voltage";
      break;
    case 1 : label = "B-Voltage";
      break;
    case 2 : label = "C-Voltage";
      break;
    case 3 : label = "A-Current";
      break;
    case 4 : label = "B-Current";
      break;
    case 5 : label = "C-Current";
      break;
    case 6 : label = "A-Power";
      break;
    case 7 : label = "B-Power";
      break;
    case 8 : label = "C-Power";
      break;
    default: label = "place holder";
      break;
  }
  vertText(label,(place*width/10) + (place*rect_width)+rect_width, 0.5*height);
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

void setup(){
  size(3000,1000); //make a window: each value (Av,Bv,Ai,Ap etc.) gets (width/9)pixels x-direction & (height)pixels y-direction
  background(0); //set initial background
  
  //list all serial ports
  println(Serial.list());
  
  //using serial port 1 (index 0)
  String usingSerial = Serial.list()[0];
  
  //initilize serial port
  myPort = new Serial(this,usingSerial,9600); //now looking at arduino serial port 1 at 9600Hz
  //don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('$');
  background(128,128,128);
}

void draw(){
  stroke(0);
  strokeWeight(1);
  float rect_width = width/(10*maxfreq);
  float rect_height = height/maxvalue;
  //draw black box at the front of the window
  fill(0);
  rect(0, 0, rect_width, height);
  
  //mapping A-Voltage
  mapping(decimalAv,0,rect_width,rect_height);

  //mapping B-Voltage
  mapping(decimalBv,1,rect_width,rect_height);
  
  //mapping C-Voltage
  mapping(decimalCv,2,rect_width,rect_height);

  //mapping A-Current
  mapping(decimalAi,3,rect_width,rect_height);
  
  //mapping B-Current
  mapping(decimalBi ,4,rect_width,rect_height);
  
  //mapping C-Current
  mapping(decimalCi,5,rect_width,rect_height);
  
  //mapping A-Power
  mapping(decimalAp,6,rect_width,rect_height);
  
  //mapping B-Power
  mapping(decimalBp ,7,rect_width,rect_height);
  
  //mapping C-Power
  mapping(decimalCp,8,rect_width,rect_height);
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
  
  //check if there is something in the string
  if (inString != null){
    //println(inString);
    
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
    
    //A_current
    s2f_array("Ai", inString_parts, Ai_string, decimalAi);
    
    //B_current
    s2f_array("Bi", inString_parts, Bi_string, decimalBi);
    
    //C_current
    s2f_array("Ci", inString_parts, Ci_string, decimalCi);
    
    //A_Power
    s2f_array("Ap", inString_parts, Ap_string, decimalAp);
    
    //B_Power
    s2f_array("Bp", inString_parts, Bp_string, decimalBp);
    
    //C_Power
    s2f_array("Cp", inString_parts, Cp_string, decimalCp);
  }
}
