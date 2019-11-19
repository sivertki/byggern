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

/**
 * \brief A function that sets the control terms for the PID controller.
 * \param p a float that sets the control term for the p part of the PID.
 * \param i a float that sets the control term for the i part of the PID.
 * \param d a float that sets the control term for the d part of the PID.
*/
void CONTROLLER_setControlTerms(float p, float i, float d);

/**
 * \brief A function that updates the controller by sending the controller output to the MOTOR_setMovement function.
*/
void CONTROLLER_updateController(Control controlType);

/**
 * \brief A function that sets the reference that the controller is supposed to stear towards.
*/
void CONTROLLER_setReference(uint8_t in, Control controlType);

/**
 * \brief A function that returns the encoder_sum to other files that might need it.
 * \return Returns the encoder_sum value.
 */
short int CONTROLLER_getEncoderSum();

/**
 * \brief A function that sets the encoder_sum value from outside files.
 */
void CONTROLLER_setEncoderSum(short int es);

/**
 * \brief A function that returns the encoder_max to other files that might need it.
 * \return Returns the encoder_max value.
 */
short int CONTROLLER_getEncoderMax();
