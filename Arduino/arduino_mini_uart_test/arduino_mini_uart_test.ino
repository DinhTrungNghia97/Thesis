//Woon Jun Shen
//UM402 (433 MHz UART)
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}

void loop() {
  Serial.println(digitalRead(6));
  delay(1000);
  if(Serial.available() > 0){//Read from serial monitor and send over UM402
    String input = Serial.readString();
    mySerial.println(input);    
  }
 
  if(mySerial.available() > 1){//Read from UM402 and send to serial monitor
    String input = mySerial.readString();
    Serial.println(input);    
  }
  delay(20);
}
