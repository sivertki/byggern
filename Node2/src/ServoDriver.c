#include <avr/io.h>
#include <stdio.h>
#include "ServoDriver.h"

uint16_t getScaledSensorValue(uint8_t controlIn);

//sets OC1A, pin 24 on Atmega2560, pin 11 on SHIELD, as pwm output
void SERVO_init(){
  // Set pin as output.
  DDRB |= 1<<PB5;
  // Set waveform generation to fast PWM
  TCCR1A |= 0b10;
  TCCR1B |= 0b11 << 3;
  // Set OC0B to non-inverting mode
  TCCR1A |= 0b10 << 6;
  // Set prescaler to 8
  TCCR1B |= 0b010;
  //set pwm frequenzy to 50Hz
  ICR1 = 0x9C40;
  //set duty cycle to 10%
  OCR1A = 0x0FA0;
}

void SERVO_setDutyCycle(uint8_t controlIn) {
  uint16_t scaledValue = getScaledSensorValue(controlIn);
  if((scaledValue <= 4200) && ( scaledValue >= 1800)) {
    OCR1A = scaledValue;
  }
}

//Scales from value read from ADC of joystick to value used in Duty Cycle
uint16_t getScaledSensorValue(uint8_t controlIn){
  uint16_t outCompare = controlIn*((4200 - 1800)/255) + 1800;
  return outCompare;

}
