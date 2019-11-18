/**
 * \file Controller.h
 * \brief A file containing the
 */

#define PID_P 1
#define PID_I 1
#define PID_D 1

#include <stdio.h>

typedef enum Control {SLIDER, JOYSTICK, INITIALIZE, NONE} Control;

/**
 * \brief A function initializing the controller functionality.
 * Initializes the controller terms and sets up the timer interrupt that makes
 * sure that the regulator has a constant time step.
 */
void CONTROLLER_Init();

//short int CONTORLLER_calculateError(short int  measured_value);
//short int CONTROLLER_calculateOutput(short int error);

/**
 * \brief A function that sets the control terms for the PID controller.
 * \param p a float that sets the control term for the p part of the PID.
 * \param i a float that sets the control term for the i part of the PID.
 * \param d a float that sets the control term for the d part of the PID.
*/
void CONTROLLER_setControlTerms(float p, float i, float d);

/**
 * \brief A function that sets the reference that the controller is supposed to stear towards.
*/
void CONTROLLER_setReference(short int in);

/**
 * \brief A function that updates the controller by sending the controller output to the MOTOR_setMovement function.
*/
void CONTROLLER_updateController(Control controlType);

void CONTROLLER_setEncoderMax(short int encoderMax);

short int CONTROLLER_getEncoderSum();

void CONTROLLER_setEncoderSum(short int encoderSum);

void CONTROLLER_setControlType(Control ControlType);

short int CONTROLLER_getEncoderMax();

//ISR(TIMER3_OVF_vect);

// The get functions are supposed to be removed (?)
short int getErrorSum();

short int getError();

short int getOutput();
