#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Firebase key
#define FIREBASE_HOST "thesis-lora-sx-1278-e32.firebaseio.com"
#define FIREBASE_AUTH "OqmEwG3C006aXWcBP0z5Z9Iy6GvCvwUQl5GN2gNi"

//WiFi ID & Password
#define WIFI_SSID "Naruto"
#define WIFI_PASSWORD "Ledinh96"


//Thingspeak key
String apiKey = "ZYI5ACIQ39N39S1W";
const char* server = "api.thingspeak.com";

SoftwareSerial mySerial(D1, D2);
String inputString = "";
boolean stringComplete = false;
String Humi1,Temp1,Temp2,Humi2;
int T1, H1, T2, H2, S; 
WiFiClient client;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  WiFi.mode(WIFI_STA);
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
    int i = 0;
    int stringlength = inputString.length();
    Serial.print("String length = "); Serial.println(stringlength);
    Serial.print(inputString);
    if(inputString.indexOf("Data0") != -1) {
      for (; i < stringlength; i++) {
        if (inputString.charAt(i) == ',') {
          T1 = i; i++;
          for (; i < stringlength; i++) {
            if (inputString.charAt(i) == ',') {
              H1 = i; i++;
              for (; i < stringlength; i++) {
                if (inputString.charAt(i) == ',') {
                  S = i; i++;
                  for (; i < stringlength; i++) {
                    if (inputString.charAt(i) == ',') {
                      T2 = i; i++;
                      for (; i < stringlength; i++) {
                        if (inputString.charAt(i) == ',') {
                          H2 = i;
                          i = stringlength;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      Temp1 = inputString.substring(T1+1, H1);
      Humi1 = inputString.substring(H1+1, S - 1);
      Temp2 = inputString.substring(T2+1, H2);
      Humi2 = inputString.substring(H2+1, stringlength - 2);

      //Set value
      delay(50);
      Firebase.setString("Temparature 0", Temp1);
      delay(50);
      Firebase.setString("Humidity 0", Humi1);
      delay(50);
      Firebase.setString("Temparature 1", Temp2);
      delay(50);
      Firebase.setString("Humidity 1", Humi2);
      delay(50);
      Firebase.setString("Temparature 0", Temp1);    
    
      /*//Handle error
      if (Firebase.failed()) {
        Serial.print("setting string failed:");
        Serial.println(Firebase.error());  
      }*/
      if (client.connect(server, 80)) {
    String body = "field1=" + Temp1 + "&field2=" + Humi1 + "&field3=" + Temp2 + "&field4=" + Humi2;

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");
    mySerial.println("Suspend! Suspend!");  
    delay(100);
   }
   client.stop();
    }
   inputString = "";
   stringComplete = false; 
   Serial.println("Deep Sleep!");
   ESP.deepSleep(0); 
   }
  while (mySerial.available()) {
    char inChar = (char)mySerial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
