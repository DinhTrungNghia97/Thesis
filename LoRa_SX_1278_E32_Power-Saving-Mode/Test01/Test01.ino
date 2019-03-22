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


#include "driverlib/pin_map.h"
#include "driverlib/hibernate.h"

void setup() {
  // put your setup code here, to run once:
  SysCtlClockSet(SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_SYSDIV_5);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
  HibernateEnableExpClk(SysCtlClockGet());
  HibernateGPIORetentionEnable();
  delay(4000);
  HibernateWakeSet(HIBERNATE_WAKE_PIN);
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
  HibernateRequest();
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
