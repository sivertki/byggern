#include "TWI_Master.h"
#include <stdio.h>

typedef enum {
  MotorLeft, MotorRight
} motorDirection;

void MOTOR_setMovement(uint8_t joystickIn);
void MOTOR_initialize();
//void MOTOR_setSpeed(uint8_t joystickIn);
