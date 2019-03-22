#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "thesis-lora-sx-1278-e32.firebaseio.com"
#define FIREBASE_AUTH "OqmEwG3C006aXWcBP0z5Z9Iy6GvCvwUQl5GN2gNi"
#define WIFI_SSID "Naruto"
#define WIFI_PASSWORD "Ledinh96"

SoftwareSerial mySerial(D1, D2);
String inputString = "";
boolean stringComplete = false;
String Humi,Temp;
int T, H;

void setup() {
  //Start serial
  Serial.begin(19200);
  mySerial.begin(19200);
  Serial.println("NodeMcu Gateway Start");
  //Connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  //Start firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if (stringComplete) {
    Serial.print(inputString);
    if(inputString.indexOf("Data0") != -1) {
      for (int i = 0; i < inputString.length(); i++) {
        if (inputString.charAt(i) == ',') {
          T = i;
          for (T; i < inputString.length(); i++) {
            if (inputString.charAt(i) == ',') {
              H = i;
            }
          }
        }
      }
      Temp = inputString.substring(T+1, H);
      Humi = inputString.substring(H+1, inputString.length() - 1);
      Serial.print(Temp + " " + Humi + '\n');
      //Set value
      Firebase.setString("Temparature 0", Temp);
      Firebase.setString("Humidity 0", Humi);
      /*//Handle error
      if (Firebase.failed()) {
        Serial.print("setting string failed:");
        Serial.println(Firebase.error());  
      }*/
    }
    else if(inputString.indexOf("Data1") != -1) {
      for (int i = 0; i < inputString.length(); i++) {
        if (inputString.charAt(i) == ',') {
          T = i;
          for (T; i < inputString.length(); i++) {
            if (inputString.charAt(i) == ',') {
              H = i;
            }
          }
        }
      }
      Temp = inputString.substring(T+1, H);
      Humi = inputString.substring(H+1, inputString.length() - 1);
      Serial.print(Temp + " " + Humi + '\n');
      //Set value
      Firebase.setString("Temparature 1", Temp);
      Firebase.setString("Humidity 1", Humi);
      /*//Handle error
      if (Firebase.failed()) {
        Serial.print("setting string failed:");
        Serial.println(Firebase.error());  
      }*/
    }
   inputString = "";
   stringComplete = false;
   }
  while (mySerial.available()) {
    char inChar = (char)mySerial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
