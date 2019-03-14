//Author: Dinh Trung Nghia
//LoRa SX1278 (433 MHz UART) - Address 123 - Channel 23 - Fixed mode
//End_Node_0: Arduino Uno R3
#include <SoftwareSerial.h>
#include <TimerOne.h>
#include "DHT.h"

SoftwareSerial mySerial(2, 3); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)
static bool senddata = false;
const int DHTPIN = A3;
const int DHTTYPE = DHT22;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
  pinMode(8,OUTPUT);  //M1
  pinMode(9,OUTPUT);  //M0
  pinMode(10,INPUT);  //AUX
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  dht.begin();
  Timer1.initialize(3000000);   //3s interrupt
  Timer1.attachInterrupt(timerISR); //Interrupt function
}

void timerISR() {
  senddata = true;
}

void loop() { 
  if(senddata == true){
    Timer1.stop();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      mySerial.write(0x01);
      mySerial.write(0x25);
      mySerial.write(0x19);
      mySerial.print("Failed to read from DHT sensor!\n");
      delay(500);
      senddata = false;
      Timer1.resume();
      return;
    }
    mySerial.write(0x01);
    mySerial.write(0x25);
    mySerial.write(0x19);
    mySerial.print("Temparature and Humidity node 0: " + String(t) + " " + String(h) + "\n");
    Serial.println(t);     //Test on Serial sender
    Serial.println(h);    //Test on Serial Sender
    delay(500);
    senddata = false;
    Timer1.resume();
  }
}
