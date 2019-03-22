//Author: Dinh Trung Nghia
//Config TivaC Centre Node
String inputString = ""; 
boolean stringComplete = false;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(19200);
   Serial2.begin(9600);
   pinMode(6,OUTPUT);  //M0
   pinMode(5,OUTPUT);  //M1
   digitalWrite(6,HIGH);
   digitalWrite(5,HIGH);
   Serial2.write(0xC0);
   Serial2.write(0x01);
   Serial2.write(0x25);
   Serial2.write(0x22);
   Serial2.write(0x19);
   Serial2.write(0xC4);
   Serial.println("Set Mode Successful");
   Serial2.write(0xC1);
   Serial2.write(0xC1);
   Serial2.write(0xC1);
}
void loop() {
   if(stringComplete) {
    Serial.print(inputString);
}
   while(Serial2.available()) {
   char a = (char)Serial2.read();
   inputString += a;
   stringComplete = true;
   }
}
