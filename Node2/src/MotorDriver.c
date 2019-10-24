#include "MotorDriver.h"
#include <avr/io.h>
#include <util/delay.h>
#define MOTOR_ADDRESS_WRITE 0b01010000
#define MOTOR_ADDRESS_READ 0b01010001

#define nRST PH6
#define nOE PH5
#define EN PH4
#define SEL PH3
#define DIR PH1

void MOTOR_initialize() {
  //sei();

  //set pins dor !RST, !OE, EN, SEL, DIR as output
  DDRH |= 1<<PH6 |1<<PH5 | 1<<PH4 | 1<<PH3 | 1<<PH1;

  //Enable Motor
  PORTH |= 1<<PH4;

  //set A8 to A15 as input
  DDRK &= ~(0xFF);

  //
  PORTH |= 1<<nRST;

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

void MOTOR_setMovement(uint8_t speed, motorDirection dir) {
  MOTOR_setDirection(dir);
  MOTOR_setSpeed(speed);
}

short int MOTOR_getEncoderValue() {
  uint8_t LSB;
  uint8_t MSB;
  short int encoder_value;
  //Set !OE low
  PORTH &= ~(1<<nOE);
  //Set SEL low
  PORTH &= ~(1<<SEL);
  //Wait 20 us
  _delay_us(250);
  //Read MSB
  MSB = PINK;
  //Set SEL high
  PORTH |= 1<<SEL;
  //Wait 20 us
  _delay_us(250);
  //READ LSB
  LSB = PINK;
  //Toggle !RST
  PORTH ^= 1<<nRST;
  _delay_us(200);
  PORTH ^= 1<<nRST;
  //Set !OE high
  PORTH |= 1<<nOE;

  //Glue together MSB LSB
  printf("MSB: %u, " , MSB);
  printf("LSB: %u, " , LSB);
  encoder_value = MSB<<8 | LSB;
  return encoder_value;
}

void MOTOR_setMovement(uint8_t joystickIn) {
  if(joystickIn < 125) {
    MOTOR_setDirection(MotorLeft);
    MOTOR_setSpeed(100);
  }
  else if(joystickIn > 150) {
    MOTOR_setDirection(MotorRight);
    MOTOR_setSpeed(100);
  }
  else {
    MOTOR_setSpeed(0);
  }
}
