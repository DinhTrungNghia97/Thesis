//Woon Jun Shen
//UM402 (433 MHz UART)
#include <SoftwareSerial.h>
#include <TimerOne.h>

SoftwareSerial mySerial(2, 3); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)
static bool senddata = false;

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
  Timer1.initialize(3000000);
  Timer1.attachInterrupt(timerISR);
}

void timerISR() {
  senddata = true;
}

void loop() { 
  if(senddata == true){
    Timer1.stop();
    mySerial.write(0x01);
    mySerial.write(0x25);
    mySerial.write(0x19);
    mySerial.write("Test Ticker\n");
    delay(500);
    senddata = false;
    Timer1.resume();
  }
}
