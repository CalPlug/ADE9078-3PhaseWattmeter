 import processing.serial.*;

  Serial myPort;        // The serial port
  int xPos = 1;         // horizontal position of the graph
  float inByte = 0;
  int lastxPos = 1;
  int lastheight = 0;
  float[]decimal = new float [100];
  void settings(){
   size(900,900);
  }
  
  void setup () {
    // set the window size:
    //size(400, 300);
    
    // List all the available serial ports
    println(Serial.list());

   
    // Open  port connected to arduino. somehow port 3 wont work but 1 does???
    myPort = new Serial(this, Serial.list()[0 ], 9600);

    // don't generate a serialEvent() unless you get a newline character:
    myPort.bufferUntil('\n');

    // set initial background:
    background(0);
  }

  void draw () {
    // drawing the line:
    stroke(0,255,0);  //set color to green(R,G,B)
    strokeWeight(1);
    for(int a=2; a<=6; a=a+2){
    line(xPos, decimal[a], lastxPos, height - decimal[a]);
   
    lastxPos=xPos;
    lastheight=int(height-inByte);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
  }
  }
  void serialEvent (Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
 /*     // trim off any whitespace:
      print(inString);
      inString = trim(inString);
      // convert to an int and map to the screen height:
      inByte = float(inString);
     // println(inByte);
      inByte = map(inByte, 0, 1023, 0, height);
      */
      
      println(inString);
      //split function 
      
     // println(inString);
     // String[] string1 = split(inString, ":"); //splits instsring into an array until every ':'
     //println(string1[1]); //print from first number to end
     
     // String string2 = string1[1].substring(0,3); //capture only the first dataset
     // println(string2); //print the first dataset
     // char[]a = string2.toCharArray(); //convert to character array
     // println(a[0],a[2]);
      
     // //char gets the ascii so subtract by 48 to get the int part...i think
     // float x1 = a[0]-48;
     // float y1 = a[2]-48;
     // println(x1,y1);
      
      
      String parts[] = splitTokens(inString, ":|,|;");
      for(int i=0; i<8; i++){
       println(parts[i]); 
      
      }
       decimal = float(parts);
      println("here comes the float array");
      for(int j=1; j<7; j++){
        println(decimal[j]);
      }
      
      
      //println(string1[1]);
     // String result = Integer(string1[0]);
    //  println(result);
      
    }
  }
