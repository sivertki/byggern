#include "Controller.h"
#include "MotorDriver.h"
#include <avr/io.h>

/**
 * A float containing the coefficient for the integral part of the PID-regulator.
 */
volatile float K_i;
/**
 * A float containing the coefficient for the proportional part of the PID-regulator.
 */
volatile float K_p;
/**
 * A float containing the coefficient for the derivative part of the PID-regulator.
 */
volatile float K_d;
/**
 * A float containing the coefficient for the time step of the PID-regulator.
 */
volatile float T_PID;
/**
 * A float containing the sum of errors in the PID-regulator.
 */
volatile short int error_sum;
/**
 * A float containing the last error calculated.
 */
volatile short int last_error;
/**
 * A float containing the reference value that the PID-regulator is stearing towards.
 */
volatile short int reference_value;

volatile short int encoder_value;
volatile short int error;
volatile short int u;

volatile short int GLOBAL_output;
volatile float output;

volatile short int difference;

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
  //DDRL |= (1<<PL6);
}

short int CONTROLLER_calculateError(short int  measured_value) {
   difference = reference_value - measured_value;
  if(difference < 28 && difference > -28) {
    return 0;
  }
  else {
    return difference;
  }

 }

void CONTROLLER_setControlTerms(float p, float i, float d) {
  K_p = p;
  K_i = i;
  K_d = d;
}

short int CONTROLLER_calculateOutput(short int error) {
  error_sum += error;
  //printf("PID values: %f, %f, %f \n\r", K_p, K_i, K_d);
  //float output;
  output = (K_p * (float)error) + (T_PID * K_i * ((float)error_sum)) + ((K_d/T_PID) * ((float)error - (float)last_error));

  //printf("float output: %f\n\r", output);

  last_error = error;
  GLOBAL_output = (short int)output;
  return (short int)output;
}

void CONTROLLER_updateController() {
  //PORTL ^= (1<<PL6);
  encoder_value = MOTOR_getEncoderValue();
  //scaledJoystickValue = scaleJoystickSpeed(joystickval);
  //printf("Scaled joystick value: %hi , ", scaledJoystickValue);
  error = CONTROLLER_calculateError(encoder_value);
  //printf("Error: %hi, ", error);
  u = CONTROLLER_calculateOutput(error);

  MOTOR_setMovement(u);
}


void CONTROLLER_setReference(short int in){
  reference_value = in;
}

//TODO remove this ugly shit
short int getErrorSum() {
  return error_sum;
}
//TODO remove
short int getError() {
  return error;
}

//TODO remove
short int getOutput() {
  return GLOBAL_output;
}
