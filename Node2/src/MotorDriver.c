#include "MotorDriver.h"
#include <avr/io.h>
#define MOTOR_ADDRESS_WRITE 0b01010000
#define MOTOR_ADDRESS_READ 0b01010001

void MOTOR_initialize() {
  //sei();
  //Enable Motor
  DDRH |= 1<<PH4;
  PORTH |= 1<<PH4;

  //Define Motor direction bit as output
  DDRH |= 1<<PH1;

  TWI_Master_Initialise();
}

void MOTOR_setSpeed(uint8_t speed) {
  unsigned char I2CMessage[3];
  I2CMessage[0] = MOTOR_ADDRESS_WRITE;
  I2CMessage[1] = 0x00;
  I2CMessage[2] = speed;

  TWI_Start_Transceiver_With_Data(I2CMessage, 3);
}

void MOTOR_setDirection(motorDirection dir) {
  if(dir == MotorLeft) {
    PORTH &= ~(1<<PH1);
  }
  else if(dir == MotorRight) {
    PORTH |= 1<<PH1;
  }
}

void MOTOR_setMovement(uint8_t joystickIn) {
  if(joystickIn < 125) {
    MOTOR_setDirection(MotorLeft);
    MOTOR_setSpeed(255 - 2*joystickIn);
  }
  else if(joystickIn > 150) {
    MOTOR_setDirection(MotorRight);
    MOTOR_setSpeed((joystickIn - 150)*2);
  }
  else {
    MOTOR_setSpeed(0);
  }
}
