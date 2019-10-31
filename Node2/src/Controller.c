#include "Controller.h"
#include "MotorDriver.h"
volatile float K_i;
volatile float K_p;
volatile float K_d;
volatile float T_PID;
volatile short int error_sum;
volatile short int last_error;
volatile short int reference_value;
#include <avr/io.h>

void CONTROLLER_Init() {
  CONTROLLER_setControlTerms(1,1,1);
  T_PID = 1;
  error_sum = 0;

  //set up timer
  //reset when reaching of OCR3A
  TCCR3A |= (1 << WGM32);
  // Set prescaler to 8
  TCCR3B |= 0b010;
  //set timer frequency to 100 Hz
  OCR3A = 0x4E20;
  //Enable compare match interrupt
  TIMSK3 |= (1<<0);

  //TODO remove::
  DDRL |= (1<<PL6);
}

short int CONTROLLER_calculateError(short int reference_value, short int  measured_value) {
   return reference_value - measured_value;
 }

void CONTROLLER_setControlTerms(float p, float i, float d) {
  K_p = p;
  K_i = i;
  K_d = d;
}

short int CONTROLLER_calculateOutput(short int error) {
  error_sum += error;
  //printf("PID values: %f, %f, %f \n\r", K_p, K_i, K_d);
  float output;
  output = (K_p * (float)error) + (T_PID * K_i * (float)error_sum) + ((K_d/T_PID) * ((float)error - (float)last_error));

  //printf("float output: %f\n\r", output);

  last_error = error;
  return (short int)output;
}

int getTerm(int n) {
  if(n == 1) {
    return (int) K_p;
  }
  else if(n == 2) {
    return (int) K_i;
  }
  else if(n == 3) {
    return (int) K_d;
  }
}
