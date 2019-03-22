//Author Dinh Trung Nghia
//LoRa SX1278 (433 MHz UART) - Node 0
#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include "DHT.h"

#define AUX 2
#define M0 9
#define M1 8
SoftwareSerial mySerial(4, 5); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)
static boolean gotosleep = true;
const int DHTPIN = A3;
const int DHTTYPE = DHT22;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);
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
  if(mySerial.available() > 0){//Read from UM402 and send to serial monitor
    String input = mySerial.readString();
    Serial.println(input);  
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (input.indexOf("Data0") != -1) {
      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        mySerial.write(0x01);
        mySerial.write(0x25);
        mySerial.write(0x19);
        mySerial.println("Sensor node 0: Failed to read from DHT sensor!");
        delay(100);
      }
      else {
        mySerial.write(0x01);
        mySerial.write(0x25);
        mySerial.write(0x19);
        mySerial.println("Data0," + String(t) + "," + String(h));
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
