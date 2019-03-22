#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#define M0 6
#define M1 5
static int a=0;
static int b=0;
static int c=1;
static int d=0;
String data0, data1;
String datasend = "";
String inputString2 = ""; 
boolean stringComplete2 = false; // State Machine
boolean GoToSuspend = true;
void Timer0IntHandler();
void Timer1IntHandler();
void serialEvent2();
void setup()
{
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  Serial.begin(19200);
  Serial2.begin(19200);
  Serial.println("Tiva C Centre Node Start!");
  Serial.flush();
  pinMode(M0,OUTPUT);  //M0
  pinMode(M1,OUTPUT);  //M1
  digitalWrite(M0, LOW);
  digitalWrite(M1, HIGH);
  int ms = MAP_SysCtlClockGet()/1000;
  
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);  
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  
  MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  
  MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, 100*ms);  //3s
  MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, 5000*ms);
  
  TimerIntRegister(TIMER0_BASE, TIMER_A, &Timer0IntHandler);
  TimerIntRegister(TIMER1_BASE, TIMER_A, &Timer1IntHandler);
  
  //MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  //IntEnable(INT_TIMER0A);
  //IntMasterEnable(); 
  //MAP_TimerEnable(TIMER0_BASE, TIMER_A);
  
}

void loop()
{
  if (stringComplete2) {
    Serial.print(inputString2);
    if(inputString2.indexOf("Data0") != -1) {
      data0 = inputString2;
      a = 1;
    }
    else if(inputString2.indexOf("Data1") != -1) {
      data1 = inputString2;
      b = 1;
    }
    else if(inputString2.indexOf("Gateway") != -1) {
      MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
      MAP_TimerIntDisable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
      MAP_TimerDisable(TIMER1_BASE, TIMER_A);
      GoToSuspend = true;
      d = 1;
    }
    inputString2 = "";
    stringComplete2 = false;
  }
  
  if((a==1) && (b==1) && (c == 1)) {
    data0 = data0.substring(0, data0.length()-1);
    datasend = data0 + "," + data1;
    //delay(100);
    Serial2.write(0x01);
    Serial2.write(0x26);
    Serial2.write(0x1A);
    Serial2.print(datasend);
    Serial2.flush();
    Serial.print(datasend);
    c = 0;
   }
  if (d == 1) {
    a = 0;
    b = 0;
    c = 1;
    d = 0;
  }

  if(GoToSuspend){
     digitalWrite(RED_LED, LOW);
     MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
     MAP_TimerEnable(TIMER0_BASE, TIMER_A);
     digitalWrite(M0, LOW);
     digitalWrite(M1, HIGH);
     Serial.println("Suspend!");
     Serial.flush();
     suspend();
  }
}

void serialEvent2(){  //Uart Interrupt
    while (Serial2.available()) {
    // Get new byte
    char inChar2 = (char)Serial2.read(); 
    // Add this byte to String
    inputString2 += inChar2;
    // Set flag
    if (inChar2 == '\n') {
    stringComplete2 = true;
    } 
    }
}

void Timer0IntHandler() {
  wakeup();
  delay(100);
  MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  MAP_TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  MAP_TimerDisable(TIMER0_BASE, TIMER_A);
  MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  MAP_TimerEnable(TIMER1_BASE, TIMER_A);
  digitalWrite(M0, HIGH);
  digitalWrite(M1, LOW);
  delay(200);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Wake up!");
  Serial.flush();
  //Send request to Node 0
  Serial2.write(0x01);
  Serial2.write(0x23);
  Serial2.write(0x17);
  Serial2.println("Data0");
  Serial2.flush();
  delay(100);
  //Send request to Node 1
  Serial2.write(0x01);
  Serial2.write(0x24);
  Serial2.write(0x18);
  Serial2.println("Data1");
  Serial2.flush();
  GoToSuspend = false;
}

void Timer1IntHandler() {
  MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  if (a == 0) {
    Serial2.write(0x01);
    Serial2.write(0x23);
    Serial2.write(0x17);
    Serial2.println("Data0");
    Serial2.flush();
  }
  if (b == 0) {
    Serial2.write(0x01);
    Serial2.write(0x24);
    Serial2.write(0x18);
    Serial2.println("Data1");
    Serial2.flush();
  }
  if (c == 0) {
    Serial.println(datasend);
    Serial2.write(0x01);
    Serial2.write(0x26);
    Serial2.write(0x1A);
    Serial2.print(datasend);
    Serial2.flush();
  }
}
