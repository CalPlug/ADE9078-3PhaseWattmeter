//set max frequencies to 10 in the processing 3 file
const int maxvalue = 100;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = random(maxvalue);
  int y = random(maxvalue);
  Serial.print("Av:0,");
  Serial.print(x);
  Serial.print(";0.1,10;0.2,20;0.3,30;0.4,40;0.5,0;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Bv:0,");
  Serial.print(y);
  Serial.print(";0.1,10;0.2,20;0.3,30;0.4,40;0.5,0;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Cv:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,0;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Ai:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,50;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Bi:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,50;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Ci:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,100;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Ap:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,50;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Bp:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,50;0.6,60;0.7,70;0.8,80;0.9,90$");
  Serial.print("Cp:0,1;0.1,10;0.2,20;0.3,30;0.4,40;0.5,0;0.6,60;0.7,70;0.8,80;0.9,90$");
}
