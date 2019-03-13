//Author: Dinh Trung Nghia
//LoRa SX1278 (433 MHz UART)
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
    mySerial.write(0x01);
    mySerial.write(0x25);
    mySerial.write(0x19);
    mySerial.print("Temparature: ");
    mySerial.println(t);
    mySerial.print("Humidity: ");
    mySerial.println(h);
    Serial.println(t);     //Test on Serial sender
    Serial.println(h);    //Test on Serial Sender
    delay(500);
    senddata = false;
    Timer1.resume();
  }
}
