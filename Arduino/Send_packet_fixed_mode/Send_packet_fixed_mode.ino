//Woon Jun Shen
//UM402 (433 MHz UART)
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //TX, RX
// gnd SET_A and SET_B for Normal Mode (Send and Receive)

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

void loop() {
  delay(3000);
  senddata();
}

void senddata()
{
  mySerial.write(0x01);
  mySerial.write(0x25);
  mySerial.write(0x19);
  mySerial.write("Anh nho em\n");
  mySerial.write("What the fuck\n");
}
