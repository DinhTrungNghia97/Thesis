//Author Dinh Trung Nghia
//LoRa SX1278 (433 MHz UART) - Node 1
#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include "DHT.h"

#define AUX 2
#define M0 6
#define M1 5
SoftwareSerial mySerial(3, 4); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)
static boolean gotosleep = true;
const int DHTPIN = A3;
const int DHTTYPE = DHT22;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(AUX, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(M0,OUTPUT);  
  pinMode(M1,OUTPUT);  
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  dht.begin();
  delay(1000);
}

void loop() {
  if((digitalRead(AUX) == 1) && (gotosleep == true)) {
    Going_To_Sleep();
  }
  if(mySerial.available() > 0){
    String input = mySerial.readString();
    Serial.println(input);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (input.indexOf("Data") != -1) {
      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        mySerial.write(0x01);
        mySerial.write(0x25);
        mySerial.write(0x18);
        mySerial.println("Sensor node 1: Failed to read from DHT sensor!");
        delay(100);
        while(digitalRead(AUX) == 0) {}
        gotosleep = true;
      }
      else {
        mySerial.write(0x01);
        mySerial.write(0x25);
        mySerial.write(0x18);
        mySerial.println("Node1," + String(t) + "," + String(h));
        Serial.println(String(t) + " " + String(h));
        while(digitalRead(AUX) == 0) {}
        gotosleep = true;
      }
    }
  }
}

void Going_To_Sleep() {
  sleep_enable();
  attachInterrupt(0, WakeUp, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  Serial.println("Sleep!");
  Serial.flush();
  sleep_cpu();
  Serial.println("Just woke up!");
  Serial.flush();
  digitalWrite(LED_BUILTIN, HIGH);
}
void WakeUp() {
  Serial.println("Interrupt Fire");
  sleep_disable();
  detachInterrupt(0);
  gotosleep = false;
  digitalWrite(M0,HIGH);
  digitalWrite(M1,LOW);
}
