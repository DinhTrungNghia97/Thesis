// Program to reading data (temperature and moisture) from DHT sensor
// Written by Trung Nghia Dinh
// Applying for Tiva™ C Series Microcontrollers

#include "DHT.h"

#define DHTPIN PD_0     // The DATA pin pairs with PD0

// Uncomment the sensor that you are using, if it is DHT11 then uncomment DHT11 and comment DHT22
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Table of pairing wires
// DHT       | TIVA C
//----------------
// VCC(1)    |  3.3V
// DATA(2)   |  PD0
// NC(3)     |  x
// GND(4)    |  GND

// Connects pin 1 of DHT to 3.3V
// Pin 2 connects to any pin of TIVA C
// Pin 4 connects to GND
// A resistance of 10k between pin 1 và pin 2

// Initiates the sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initiate serial baud 115200
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  Serial1.begin(115200);
  // Starting to read sensor
  dht.begin();
}

void loop() {
  // Waiting to transfer data in 2s
  delay(2000);

  float h = dht.readHumidity();
  // Read from sensor the temperature value in C degree (by default)
  float t = dht.readTemperature();
  // Read from sensor the temperature value in F (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Checks if the data is read successfully or not
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Calculate the Farenheit index F (by default)
  //  float hif = dht.computeHeatIndex(f, h);
  // Calculate the Celcius index (isFahreheit = false)
  //  float hic = dht.computeHeatIndex(t, h, false);

  // Print the data to the screen
  Serial.print("Moisture: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  //  Serial.print(f);
  //  Serial.print(" *F\t");
  //  Serial.print("Heat index: ");
  //  Serial.print(hic);
  //  Serial.print(" *C ");
  //  Serial.print(hif);
  //  Serial.println(" *F");
}
