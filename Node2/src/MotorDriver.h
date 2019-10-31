#include "TWI_Master.h"
#include <stdio.h>

typedef enum {
  MotorLeft, MotorRight
} motorDirection;

void MOTOR_setMovement(short int controllerOutput);
//void MOTOR_setMovementJoystick(uint8_t joystickIn);
void MOTOR_initialize();
short int MOTOR_getEncoderValue();
//void MOTOR_setSpeed(uint8_t joystickIn);
