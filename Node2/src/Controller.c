#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "Controller.h"
#include "MotorDriver.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * \brief An int containing the center of the joystick X-axis.
 */
static int xCenter = 130;

/**
 * \brief A float containing the coefficient for the integral part of the PID-regulator.
 */
static volatile float K_i;

/**
 * \brief A float containing the coefficient for the proportional part of the PID-regulator.
 */
static volatile float K_p;

/**
 * \brief A float containing the coefficient for the derivative part of the PID-regulator.
 */
static volatile float K_d;

/**
 * \brief A short int containing the sum of errors in the PID-regulator.
 */
static volatile short int error_sum;

/**
 * \brief A short int containing the last error calculated.
 */
static volatile short int last_error;

/**
 * \brief A short int containing the reference value that the PID-regulator is stearing towards.
 */
static volatile short int reference_value;

/**
 * \brief
 */
static volatile short int encoder_value;

/**
 * \brief
 */
static volatile short int encoder_max;

/**
 * \brief
 */
static volatile short int controller_output;

/**
 * \brief A short int containing the sum of the encoder values.
 * Since the encoder gets reset every time the encoder value is read, this
 * variable is needed to store the total distance.
 */
volatile short int encoder_sum;

//Implicit declarations, used in init
short int scaleJoystickSpeed(uint8_t joystickIn);
short int scaleSliderSpeed(uint8_t sliderIn);
short int CONTROLLER_getEncoderSum();
void CONTROLLER_setEncoderSum(short int encoderSum);
short int CONTROLLER_getEncoderMax();
void CONTROLLER_setEncoderMax(short int encoderMax);


void CONTROLLER_Init() {
  CONTROLLER_setControlTerms(0.25,0.00,0.35);
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

  //Calibrate the encoder max value
  short int ref = scaleJoystickSpeed(255);
  printf("Ref: %hi\n\r", ref);
  CONTROLLER_setReference(ref, JOYSTICK);
  _delay_ms(2500);
  MOTOR_resetEncoder();
  CONTROLLER_setEncoderSum(0);
  ref = scaleJoystickSpeed(0);
  printf("Ref: %hi\n\r", ref);
  CONTROLLER_setReference(ref, JOYSTICK);
  _delay_ms(2500);
  printf("Encoder Sum: %hi\n\r", CONTROLLER_getEncoderSum());
  CONTROLLER_setEncoderMax(CONTROLLER_getEncoderSum());

}

short int CONTROLLER_calculateError(short int  measured_value, Control controlType) {
  short int difference =  measured_value - reference_value;
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
  float output;
  if((controlType == JOYSTICK) || (controlType == INITIALIZE) ) { //PD
    output = -((K_p * (float)error) + ( K_i * ((float)error_sum)) + (K_d * ((float)error - (float)last_error)));
  }
  else { //PID
    output = (K_p * (float)error) + (K_i * ((float)error_sum)) + (K_d * ((float)error - (float)last_error));
  }

  last_error = error;
  return (short int)output;
}

void CONTROLLER_updateController(Control controlType) {
  encoder_value = MOTOR_getEncoderValue();
  short int error;
  if((controlType == JOYSTICK) || (controlType == INITIALIZE)) { //PD
    error = CONTROLLER_calculateError(encoder_value, controlType);
  }
  else {  //PID
    error = CONTROLLER_calculateError(encoder_sum, controlType);
  }

  controller_output = CONTROLLER_calculateOutput(error, controlType);

  MOTOR_setMovement(controller_output);
}

void CONTROLLER_setReference(uint8_t in, Control controlType){
  if(controlType == SLIDER) {
    reference_value = scaleSliderSpeed(in);
  }
  else if(controlType == JOYSTICK) {
    reference_value = scaleJoystickSpeed(in);
  }
}

void CONTROLLER_setEncoderMax(short int encoderMax) {
  encoder_max = encoderMax;
  printf("Encoder max set to: %hi\n\r", encoderMax);
}

void CONTROLLER_addEncoderSum(short int encoderTerm) {
  encoder_sum += encoderTerm;
}

short int scaleJoystickSpeed(uint8_t joystickIn) {
  if(joystickIn < xCenter *0.8) {
    float motorSpeed = 255 - 2*joystickIn;
    return (short int) (- motorSpeed);
  }
  else if(joystickIn > xCenter *1.2) {
    float motorSpeed = 40 + 2.5*(joystickIn-170);
    return  (short int) motorSpeed;
  }
  else {
    return 0;
  }
}

short int scaleSliderSpeed(uint8_t sliderIn) {
  float scaleConstant = CONTROLLER_getEncoderMax()/255;
  return (short int) sliderIn*scaleConstant;
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
