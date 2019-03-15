//Author: Dinh Trung Nghia
//LoRa SX 1278 433MHz - Address: 125 - Channel 25 - Transparent mode
//TivaC Centre Node
String inputString2 = ""; 
boolean stringComplete2 = false; // State Machine

void setup() {
  //Setup Serial
  Serial.begin(19200);
  Serial2.begin(19200);
  // declare 200 bytes for inputString2:
  inputString2.reserve(200);
  pinMode(6,OUTPUT);  //M0
  pinMode(5,OUTPUT);  //M1
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  Serial.println("Tiva C Centre Node Start");
  delay(200);
}

void loop() {
  // print string when get new line
  if (stringComplete2) {
    Serial.println(inputString2); 
  // Empty string
    Serial2.write(0x01);
    Serial2.write(0x26);
    Serial2.write(0x1A);
    Serial2.print(inputString2);
    Serial2.println("Already Send!");
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
