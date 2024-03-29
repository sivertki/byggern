#include "SolenoidDriver.h"
#include <avr/io.h>
#include <util/delay.h>

void SOLENOID_init() {
  // Sets up output port to control solenoid.
  DDRA |= (1<<PA1);
  // Set standard high
  PORTA |= (1<<PA1);
}

void SOLENOID_fire() {
  PORTA &= ~(1<<PA1);
  _delay_ms(200);
  PORTA |= (1<<PA1);
}
