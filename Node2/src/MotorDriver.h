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
 * \brief A function that sets the movement of the motor based on the parameter.
 * \param controllerOutput a output value from the *JOYSTICK* [0, 255].
 */
void MOTOR_setMovement(short int controllerOutput);

//void MOTOR_setMovementJoystick(uint8_t joystickIn);

/**
 * \brief A function that initilaizes the motor.
 */
void MOTOR_initialize();

/**
 * \brief A function that fetches the encoder value from the encoder.
 * \return A short int that contains the encoder value recieved from the encoder.
 */
short int MOTOR_getEncoderValue();

//void MOTOR_setSpeed(uint8_t joystickIn);
