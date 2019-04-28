//set max frequencies to 6 in the processing 3 file

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("Av:0,2;0.1,2;0.2,100;0.3,43;0.4,51;0.5,44$");
  Serial.println("Bv:0,1;0.1,33;0.2,1;0.3,4;0.4,32;0.5,4$");
}
