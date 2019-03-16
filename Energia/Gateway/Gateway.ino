//Author: Dinh Trung Nghia
//LoRa SX 1278 433MHz - Address: 126 - Channel 26 - Fixed mode
//TivaC Gateway 
String inputString2 = ""; 
boolean stringComplete2 = false; // State Machine

void setup() {
  //Setup Serial
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial2.begin(19200);
  // declare 200 bytes for inputString2:
  inputString2.reserve(200);
  pinMode(6,OUTPUT);  //M0
  pinMode(5,OUTPUT);  //M1
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  Serial.println("Tiva C Gateway Start");
  delay(200);
}

void loop() {
  // print string when get new line
  if (stringComplete2) {
    Serial.print(inputString2);
    Serial1.print(inputString2);
    delay(200);
  // Empty string
    inputString2 = "";
    stringComplete2 = false;
  }
}

void serialEvent2(){  //Uart Interrupt
    while (Serial2.available()) {
    // Get new byte
      char inChar2 = (char)Serial2.read(); 
    // Add this byte to String
      inputString2 += inChar2;
    // Set flag
      if (inChar2 == '\n') {
        stringComplete2 = true;
      } 
   }
} 
