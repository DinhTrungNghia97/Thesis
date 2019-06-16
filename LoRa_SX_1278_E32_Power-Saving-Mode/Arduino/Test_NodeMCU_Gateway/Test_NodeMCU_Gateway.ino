#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Ticker.h>

//Firebase key
#define FIREBASE_HOST "thesis-lora-sx-1278-e32.firebaseio.com"
#define FIREBASE_AUTH "OqmEwG3C006aXWcBP0z5Z9Iy6GvCvwUQl5GN2gNi"

//WiFi ID & Password
#define WIFI_SSID "Naruto"
#define WIFI_PASSWORD "Ledinh96"


//Thingspeak key
//String apiKey = "ZYI5ACIQ39N39S1W";
//const char* server = "api.thingspeak.com";

SoftwareSerial mySerial(D1, D2);
String inputString = "";
boolean stringComplete = false;
boolean interrupt = true;
boolean allow_check = false;
String Humi1,Temp1,Temp2,Humi2,Temp3,Humi3 ;
int T1, H1, T2, H2, T3, H3, S;
static int Count=1; 
static int a = 0;
static int b = 0;
//WiFiClient client;
Ticker flipper;

void Check_Connection();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D5, OUTPUT); //M1
  pinMode(D6, OUTPUT); //M0
  pinMode(D7, INPUT); //test
  Serial.print(digitalRead(D7));
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  Serial.println("NodeMcu Gateway Start");
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
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (interrupt) {
    Serial.println("Vao set timmer");
    flipper.attach(30, Check_Connection);
    interrupt = false;   
  }
  while (mySerial.available()) {
    char inChar = (char)mySerial.read();    
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }    
  if (stringComplete) {
    flipper.detach();
    digitalWrite(LED_BUILTIN, LOW);
    int i = 0;
    int m = 0;
    int stringlength = inputString.length();

    if((inputString.indexOf("Data0") != -1) && (a == 0)) {
       a = 1;
       Serial.print("String length = "); Serial.println(stringlength);
       Serial.print(inputString);
       mySerial.write(0x01);
       mySerial.write(0x25);
       mySerial.write(0x18);
       mySerial.println("Stop Sending!");
       delay(100);
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
      Serial.println(Temp1 + " " + Humi1 + " " + Temp2 + " " + Humi2);
      
      //Set value
      delay(50);
      Firebase.setString("Temperature/0", Temp1);
      delay(50);
      Firebase.setString("Humidity/0", Humi1);
      delay(50);
      Firebase.setString("Temperature/1", Temp2);
      delay(50);
      Firebase.setString("Humidity/1", Humi2);
      delay(50);
   
/*
      if (client.connect(server, 80)) {
    String body = "&field1=" + Temp1 + "&field2=" + Humi1 + "&field3=" + Temp2 + "&field4=" + Humi2;

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

      }
      */
     }

     else if((inputString.indexOf("Data2") != -1) && (b == 0)) {
      b = 1;
       Serial.print("String length = "); Serial.println(stringlength);
       Serial.print(inputString);
       mySerial.write(0x01);
       mySerial.write(0x26);
       mySerial.write(0x18);
       mySerial.println("Stop Sending!");
       delay(100);
       for (; m < stringlength; m++) {
        if (inputString.charAt(m) == ',') {
          T3 = m; m++;
          for (; m < stringlength; m++) {
            if (inputString.charAt(m) == ',') {
              H3 = m; m = stringlength;
            }
          }
        }
       }
      Temp3 = inputString.substring(T3+1, H3);
      Humi3 = inputString.substring(H3+1, stringlength - 2);
      Serial.println(Temp3 + " " + Humi3);

      delay(50);
      Firebase.setString("Temperature/2", Temp3);
      delay(50);
      Firebase.setString("Humidity/2", Humi3);
      delay(50);
/*
      if (client.connect(server, 80)) {
        String body = "&field5=" + Temp3 + "&field6=" + Humi3 ;
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
      }
      */
     }
 
      inputString = "";
      stringComplete = false;
      interrupt = true;
      //Serial.println("Deep Sleep!");
      //ESP.deepSleep(0);
    }
    if ((a==1) && (b==1))
    {
    /*
    if (client.connect(server, 80)) {
    String body = "&field1=" + Temp1 + "&field2=" + Humi1 + "&field3=" + Temp2 + "&field4=" + Humi2 + "&field5=" + Temp3 + "&field6=" + Humi3;
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
      }
      //client.stop();
      
      mySerial.write(0x01);
      mySerial.write(0x25);
      mySerial.write(0x18);
      mySerial.println("Suspend!");
      delay(100);
      
      mySerial.write(0x01);
      mySerial.write(0x26);
      mySerial.write(0x18);
      mySerial.println("Suspend!");
      delay(100);
      */
      flipper.detach();
      
      if ((Temp1 != "NaN") && (Humi1 != "NaN") && (Temp2 != "NaN") && (Humi2 != "NaN") && (Temp3 != "NaN") && (Humi3 != "NaN")) {
        Firebase.setString("Alert", "0");
        Serial.println("Good Connection");
      }
      else if ((Temp1 == "NaN") && (Humi1 == "NaN") && (Temp2 == "NaN") && (Humi2 == "NaN") && (Temp3 == "NaN") && (Humi3 == "NaN")) {
        Firebase.setString("Alert", "1");
        Serial.println("All Abort");
      }
      else if ((Temp1 == "NaN") && (Humi1 == "NaN") && (Temp2 != "NaN") && (Humi2 != "NaN") && (Temp3 != "NaN") && (Humi3 != "NaN")) {
        Firebase.setString("Alert", "2");
        Serial.println("Node 1 Abort");
      }
      else if ((Temp1 != "NaN") && (Humi1 != "NaN") && (Temp2 == "NaN") && (Humi2 == "NaN") && (Temp3 != "NaN") && (Humi3 != "NaN")) {
        Firebase.setString("Alert", "3");
        Serial.println("Node 2 Abort");
      }
      else if ((Temp1 != "NaN") && (Humi1 != "NaN") && (Temp2 != "NaN") && (Humi2 != "NaN") && (Temp3 == "NaN") && (Humi3 == "NaN")) {
        Firebase.setString("Alert", "4");
        Serial.println("Node 3 Abort");
      }
      else if ((Temp1 == "NaN") && (Humi1 == "NaN") && (Temp2 == "NaN") && (Humi2 == "NaN") && (Temp3 != "NaN") && (Humi3 != "NaN")) {
        Firebase.setString("Alert", "5");
        Serial.println("Node 1&2 Abort");
      }
      else if ((Temp1 != "NaN") && (Humi1 != "NaN") && (Temp2 == "NaN") && (Humi2 == "NaN") && (Temp3 == "NaN") && (Humi3 == "NaN")) {
        Firebase.setString("Alert", "6");
        Serial.println("Node 2&3 Abort");
      }
      else if ((Temp1 == "NaN") && (Humi1 == "NaN") && (Temp2 != "NaN") && (Humi2 != "NaN") && (Temp3 == "NaN") && (Humi3 == "NaN")) {
        Firebase.setString("Alert", "7");
        Serial.println("Node 1&3 Abort");
      }
      delay(50);
      if ((Temp1 != "fail") && (Humi1 != "fail") && (Temp2 != "fail") && (Humi2 != "fail") && (Temp3 != "fail") && (Humi3 != "fail")) {
        Firebase.setString("Sensor", "0");
        Serial.println("All sensor collected");
      }
      else if ((Temp1 == "fail") && (Humi1 == "fail") && (Temp2 == "fail") && (Humi2 == "fail") && (Temp3 == "fail") && (Humi3 == "fail")) {
        Firebase.setString("Sensor", "1");
        Serial.println("All sensor fail");
      }
      else if ((Temp1 == "fail") && (Humi1 == "fail") && (Temp2 != "fail") && (Humi2 != "fail") && (Temp3 != "fail") && (Humi3 != "fail")) {
        Firebase.setString("Sensor", "2");
        Serial.println("Sensor node 1 fail");
      } 
      else if ((Temp1 != "fail") && (Humi1 != "fail") && (Temp2 == "fail") && (Humi2 == "fail") && (Temp3 != "fail") && (Humi3 != "fail")) {
        Firebase.setString("Sensor", "3");
        Serial.println("Sensor node 2 fail");
      }
      else if ((Temp1 != "fail") && (Humi1 != "fail") && (Temp2 != "fail") && (Humi2 != "fail") && (Temp3 == "fail") && (Humi3 == "fail")) {
        Firebase.setString("Sensor", "4");
        Serial.println("Sensor node 3 fail");
      }
      else if ((Temp1 == "fail") && (Humi1 == "fail") && (Temp2 == "fail") && (Humi2 == "fail") && (Temp3 != "fail") && (Humi3 != "fail")) {
        Firebase.setString("Sensor", "5");
        Serial.println("Sensor node 1 & 2 fail");
      }
      else if ((Temp1 != "fail") && (Humi1 != "fail") && (Temp2 == "fail") && (Humi2 == "fail") && (Temp3 == "fail") && (Humi3 == "fail")) {
        Firebase.setString("Sensor", "6");
        Serial.println("Sensor node 2 & 3 fail");
      } 
      else if ((Temp1 == "fail") && (Humi1 == "fail") && (Temp2 != "fail") && (Humi2 != "fail") && (Temp3 == "fail") && (Humi3 == "fail")) {
        Firebase.setString("Sensor", "7");
        Serial.println("Sensor node 1 & 3 fail");
      }     
      delay(50);
      Firebase.setFloat("Count", Count);
      delay(50);
      Count++;
      mySerial.write(0xFF);
      mySerial.write(0xFF);
      mySerial.write(0x18);
      mySerial.println("Suspend!");
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      a=0;
      b=0;
      interrupt = true;
    }
    if (allow_check) {
      allow_check = false;
      if ((a==0) && (b==0)) {
        Firebase.setString("Alert", "8");
        delay(50);
        Serial.println("Sink 1 & Sink 2 lost connection");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if ((a==0) && (b == 1)) {
        Firebase.setString("Alert", "9");
        Serial.println("Sink 1 lost connection");
        digitalWrite(LED_BUILTIN, HIGH);
        b = 0;
      }
      else if ((a == 1) && (b == 0)) {
        Firebase.setString("Alert", "10");
        Serial.println("Sink 2 lost connection");
        digitalWrite(LED_BUILTIN, HIGH);
        a = 0;
      }
    }
}

void Check_Connection() {
    Serial.println("Vao ngat");
    allow_check = true;   
}
