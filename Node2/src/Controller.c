#include "Controller.h"
#include "MotorDriver.h"
#include <avr/io.h>

/**
 * \brief A float containing the coefficient for the integral part of the PID-regulator.
 */
volatile float K_i;

/**
 * \brief A float containing the coefficient for the proportional part of the PID-regulator.
 */
volatile float K_p;

/**
 * \brief A float containing the coefficient for the derivative part of the PID-regulator.
 */
volatile float K_d;

/**
 * \brief A float containing the coefficient for the time step of the PID-regulator.
 */
volatile float T_PID;

/**
 * \brief A short int containing the sum of errors in the PID-regulator.
 */
volatile short int error_sum;

/**
 * \brief A short int containing the last error calculated.
 */
volatile short int last_error;

/**
 * \brief A short int containing the reference value that the PID-regulator is stearing towards.
 */
volatile short int reference_value;

/**
 * \brief
 */
volatile short int encoder_value;

/**
 * \brief
 */
volatile short int encoder_max;

/**
 * \brief
 */
volatile short int error;

/**
 * \brief
 */
volatile short int u;

/**
 * \brief
 */
volatile short int GLOBAL_output;

/**
 * \brief
 */
volatile float output;

/**
 * \brief
 */
volatile short int difference;

/**
 * \brief A short int containing the sum of the encoder values.
 * Since the encoder gets reset every time the encoder value is read, this
 * variable is needed to store the total distance.
 */
volatile short int encoder_sum;

//volatile Control control_type; REMOVE?

void CONTROLLER_Init() {
  CONTROLLER_setControlTerms(0.25,0.00,0.35);
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

short int CONTROLLER_calculateError(short int  measured_value, Control controlType) {
  difference =  measured_value - reference_value;
  //printf("Difference %hi\n\r", difference);
  //printf("measured_value: %hi , reference_value: %hi\n\r", measured_value, reference_value);
  if(controlType) {
    if(difference < 100 && difference > -100) {
      return 0;
    }
    else {
      return difference;
    }
  }
  else {
    if(difference < 1000 && difference > -1000) {
      return 0;
    }
    else {
      return difference;
    }
  }
 }

void CONTROLLER_setControlTerms(float p, float i, float d) {
  K_p = p;
  K_i = i;
  K_d = d;
}

short int CONTROLLER_calculateOutput(short int error, Control controlType) {
  error_sum += error;
  //printf("PID values: %f, %f, %f \n\r", K_p, K_i, K_d);
  //float output;
  if((controlType == JOYSTICK) || (controlType == INITIALIZE) ) { //PD
    output = -((K_p * (float)error) + (T_PID * K_i * ((float)error_sum)) + ((K_d/T_PID) * ((float)error - (float)last_error)));
  }
  else { //PID
    output = (K_p * (float)error) + (T_PID * K_i * ((float)error_sum)) + ((K_d/T_PID) * ((float)error - (float)last_error));
  }


  //printf("float output: %f\n\r", output);

  last_error = error;
  GLOBAL_output = (short int)output;
  return (short int)output;
}

void CONTROLLER_updateController(Control controlType) {
  //PORTL ^= (1<<PL6);
  encoder_value = MOTOR_getEncoderValue();

  if((controlType == JOYSTICK) || (controlType == INITIALIZE)) { //PD
    //scaledJoystickValue = scaleJoystickSpeed(joystickval);
    //printf("Scaled joystick value: %hi , ", scaledJoystickValue);
    error = CONTROLLER_calculateError(encoder_value, controlType);
    //printf("Error: %hi, ", error);
  }
  else {  //PID
    error = CONTROLLER_calculateError(encoder_sum, controlType);
  }

  u = CONTROLLER_calculateOutput(error, controlType);

  MOTOR_setMovement(u);
}


void CONTROLLER_setReference(short int in){
  reference_value = in;
}

void CONTROLLER_setEncoderMax(short int encoderMax) {
  encoder_max = encoderMax;
  //encoder_max = encoderMax;
  printf("Encoder max set to: %hi\n\r", encoderMax);
}

void CONTROLLER_addEncoderSum(short int encoderTerm) {
  encoder_sum += encoderTerm;
}

short int CONTROLLER_getEncoderSum() {
  return encoder_sum;
}

void CONTROLLER_setEncoderSum(short int es) {
  encoder_sum = es;
}

short int CONTROLLER_getEncoderMax() {
  return encoder_max;
}

/* REMOVE?
void CONTROLLER_setControlType(Control ControlType) {
  control_type = ControlType;
}
*/

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
