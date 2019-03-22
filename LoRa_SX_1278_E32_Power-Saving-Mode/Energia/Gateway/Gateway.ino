#define AUX 11
#define M0 6
#define M1 5
#define WakeESP 38
static boolean gotosuspend = true;
String inputString2 = ""; 
boolean stringComplete2 = false; // State Machine
void Going_To_Sleep();
void serialEvent2();
void WakeUp();

void setup()
{
  //Start serial port
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial2.begin(19200);

  //Declare 200 bytes for inputString2
  inputString2.reserve(200);

  //Config led status and gpio
  pinMode(RED_LED, OUTPUT);                 
  pinMode(AUX, INPUT_PULLUP);              
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(WakeESP, OUTPUT);
  digitalWrite(WakeESP, HIGH);
  digitalWrite(RED_LED, HIGH);

  //Set LoRa mode 2
  digitalWrite(M0, LOW);
  digitalWrite(M1, HIGH);
  delay(1000);
}

void loop()
{
  if((digitalRead(AUX) == 1) && (gotosuspend == true)) {  //Check suspend mode
    Going_To_Sleep();
  }
  
  if (stringComplete2) {   //Store data received and send back ACK 
    Serial.print(inputString2);
    if(inputString2.indexOf("Data0") != -1) {
       Serial2.write(0x01);
       Serial2.write(0x25);
       Serial2.write(0x19);
       Serial2.println("Gateway receive!");
       while(digitalRead(AUX) == 0) {}
       Serial1.print(inputString2);
       Serial1.flush();
       gotosuspend = true;
    }   
  //Empty string
    inputString2 = "";
    stringComplete2 = false;
  }   
}

void serialEvent2() {  //Uart Interrupt
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

void Going_To_Sleep() {   //Suspend function
  attachInterrupt(digitalPinToInterrupt(AUX), WakeUp, LOW); // Attach ISR to AUX
  digitalWrite(RED_LED, LOW);
  //Set LoRa mode 2
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  Serial.println("Suspend!");
  Serial.flush();
  suspend();
}
void WakeUp() {    //Wake up function
  wakeup();        // wake up if AUX is LOW
  detachInterrupt(digitalPinToInterrupt(AUX));
  //Set LoRa mode 1
  digitalWrite(M0, HIGH);
  digitalWrite(M1, LOW);
  delay(200);
  digitalWrite(WakeESP, LOW);    //Wake ESP
  delay(100);
  digitalWrite(WakeESP, HIGH);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Woke up!");
  Serial.flush();
  gotosuspend = false;
}
