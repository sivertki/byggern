/**
 * \file MotorDriver.h
 * \brief A file that makes it possible to control the motor.
 */

#include "TWI_Master.h"
#include <stdio.h>

/**
 * \brief An enum that defines the two directions that the motor can move in.
 */
typedef enum {
  MotorLeft, MotorRight
} motorDirection;

/**
 * \brief A function that initilaizes the motor that moves the pingpong cart.
 * Enables the pins controlling the motor as well as the pins recieving information
 * from the motor. Also initilaizes the TWI communication.
 */
void MOTOR_initialize();

/**
 * \brief A function that sets the movement of the motor based on the parameter.
 * \param controllerOutput A short int containing the value calculated in the controller.
 */
void MOTOR_setMovement(short int controllerOutput);

/**
 * \brief A function that fetches the encoder value from the encoder.
 * \return A short int that contains the encoder value recieved from the encoder.
 */
short int MOTOR_getEncoderValue();

/**
 * A function that resets the value of the encoder register on the motor box.
 */
void MOTOR_resetEncoder();
