//Enoch Chau 2019
import processing.serial.*;

//**IMPORANT: make sure that max frequency and max values are inline with ADE9078 up or you will have error!

int maxfreq = 6; //assume frequencies can range from 0 to 10 in increments of 0.1
int maxvalue = 100;//assume values can range from 0 to 100 in increments of 1
int errorvalue = 50;//if a frequncy has a value higher than this then there is something wrong with the power consumption

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

void setup(){
  size(1800,900); //make a window that is 1800x900: each value (Av,Bv,Ai,Ap etc.) gets 200pixels x-co_ord & 900pixels y-co_ord
  background(0); //set initial background
  
  //list all serial ports
  println(Serial.list());
  
  //using serial port 1 (index 0)
  String usingSerial = Serial.list()[0];
  
  //initilize serial port
  myPort = new Serial(this,usingSerial,9600); //now looking at arduino serial port 1 at 9600Hz
  //don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('$');
  background(0);
}

void draw(){
  int i;
  stroke(0,255,0);
  fill(0,255,0);
  float rect_width = width/(9*maxfreq);
  
  //mapping A-Voltage
  //when mapping:
  //we look at decimalAv[0] = frequncy to map to (x-coordinate)
  //assuming that values come in order of frequency, we don't need to use the x-coordinate
  //we then look at decimalAv[1] = value of frequnecy (y-coordinate)
  for(i=0; i<maxfreq+1; i+=2){
    //check for errors, turn the bar red if there is an error
    //if (decimalAv[i+1] > errorvalue){
    //  fill(255,0,0); //red
    //}
    //else{
    //  fill(0,255,0);
    //}
    rect(i+rect_width , height - decimalAv[i+1]*(height/maxvalue) , rect_width , decimalAv[i+1]*(height/maxvalue));
    //print("rectangle: ");
    //println(decimalAv[i]);
  }

  //mapping B-Voltage
  for(i=0; i<maxfreq+1; i+=2){
    rect(i+rect_width+width/9 , height - decimalBv[i+1]*(height/maxvalue) , rect_width , decimalBv[i+1]*(height/maxvalue));
  }
  
  //mapping C-Voltage
  for(i=0; i<maxfreq+1; i+=2){
    rect(i+rect_width+(2*width)/9 , height - decimalCv[i+1]*(height/maxvalue) , rect_width , decimalCv[i+1]*(height/maxvalue));
  }
}

void serialEvent (Serial myPort) {  
  int i;
  String Av = "Av";
  String Bv = "Bv";
  String Cv = "Cv";
  String Ai = "Ai";
  String Bi = "Bi";
  String Ci = "Ci";
  String Ap = "Ap";
  String Bp = "Bp";
  String Cp = "Cp";
  
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
  
  //reads the serial port until a new line
  String inString = myPort.readStringUntil('$');
  
  //check if there is something in the string
  if (inString != null){
    println(inString);
    
    //break the string into parts dividing at : , ; $
    String[] inString_parts = splitTokens(inString, ":,;$");
    
    //print each part of the array for debugging
    for(i=0; i<inString_parts.length; i++){
      print(inString_parts[i]);
      print(' ');
    }
    println();   

    //for example: finding A_Voltage
    //inString_parts[0] = 'Av'
    //inString_parts[1] = '0' (frequency)
    //inString_parts[2] = '1' (value)

    
    //after checking the first index of inString_parts, use array copy to remove the first index of inString_parts
    //then copy that array to Av_string
    if(Av.equals(inString_parts[0]) == true ){
      arrayCopy(inString_parts , 1, Av_string, 0, Av_string.length);
      for(i=0; i<Av_string.length; i++){
        print("Av_string:");
        println(i);
        println(Av_string[i]);
      }
      for(i=0; i<Av_string.length; i++){
        decimalAv[i] = float(Av_string[i]);
        print("decimalAv:");
        println(i);
        println(decimalAv[i]);
      }
    }
    
    //B_voltage
    if(Bv.equals(inString_parts[0]) == true ){
      arrayCopy(inString_parts , 1, Bv_string, 0, Bv_string.length);
      //for(i=0; i<Bv_string.length; i++){
      //  print("Bv_string:");
      //  println(i);
      //  println(Bv_string[i]);
      //}
      for(i=0; i<Bv_string.length; i++){
        decimalBv[i] = float(Bv_string[i]);
        //print("decimalBv:");
        //println(i);
        //println(decimalBv[i]);
      }
    }
    
    //C_voltage
    if(Cv.equals(inString_parts[0]) == true ){
      arrayCopy(inString_parts , 1, Cv_string, 0, Cv_string.length);
      for(i=0; i<Cv_string.length; i++){
        decimalCv[i] = float(Cv_string[i]);
      }
    }
  }
}  
