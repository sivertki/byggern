#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SPIDriver2.h"
#include "MCPDriver2.h"
#include "CANDriver.h"
#include "UARTDriver2.h"
#include "ServoDriver.h"
#include "avr/interrupt.h"
#include "IRDriver.h"
#include "MotorDriver.h"
#include "Controller.h"
#include "MCP2515.h"
#include "SolenoidDriver.h"

void joy_cal();
short int scaleJoystickSpeed(uint8_t joystickIn);

static int xCenter = 0;
static int yCenter = 0;

static int K_p;
static int K_d;
static int K_i;

int main (void) {
  cli();
  // Set pin49 as output
  DDRL |= (1<<PL0);
  USART_Init();
  SPI_init();
  can_init();
  servoInit();
  IR_init();
  MOTOR_initialize();
  CONTROLLER_Init();
  MCP_init();
  SOLENOID_init();
  joy_cal();
  //TODO tune dis sjiiiit
  CONTROLLER_setControlTerms(1.0,0.01,1.0);
  K_p = getTerm(1);
  K_i = getTerm(2);
  K_d = getTerm(3);
  printf("K_p: %i, K_i: %i, K_d: %i\n\r", K_p, K_i, K_d);
  printf("Node 2 initialized!\n\r");
  _delay_ms(1000);
  sei();
  while(1) {

    //set high
    /*
    PORTL |= (1<<PL0);
    _delay_ms(1000);
    //set low
    PORTL &= ~(1<<PL0);
    _delay_ms(1000);
    */
    /*
    result = IR_detect_goal();

    if(result == 1) {
      printf("GOAAAAAL!\n\r");
    }
    else {
      //printf("No goal.\n\r");
    }
    */
    //printf("\n\r");
    /*
    receivedMessage = can_data_receive();
    printf("Received data: %u\r\n", receivedMessage.data[0]);
    joystickval = receivedMessage.data[0];
    //printf(" Scaled value: %hu\n\r", getScaledSensorValue(receivedMessage.data[0]));
    //SERVO_SetDutyCycle(receivedMessage.data[0]);
    //MOTOR_setMovement(receivedMessage.data[1]);

    encoder_value = MOTOR_getEncoderValue();
    scaledJoystickValue = scaleJoystickSpeed(joystickval);
    printf("Scaled joystick valu(ue: %hi\n\r", scaledJoystickValue);
    error = CONTROLLER_calculateError(scaledJoystickValue, encoder_value);
    u = CONTROLLER_calculateOutput(error);
    printf("Controller output: %hi\n\r", u);
    //MOTOR_setMovement(u);

    */
    //printf("Encoder value: %hi\n\r", encoder_value);

    //ADCVal = IR_read();

    //printf("ADCVal : %u\n\r", ADCVal);
    /*
    uint8_t canstatInfo = (MCP_reads(MCP_CANSTAT)>>1) & 0b0000111;

    if(canstatInfo == )
    */
    printf("Loop-idi-doop!\n\r");
    _delay_ms(2000);

  }
}



void joy_cal() {
     struct CANMessage receivedMessage;
     receivedMessage = can_data_receive();

     yCenter = receivedMessage.data[0];
     xCenter = receivedMessage.data[1];

     printf("Calibration complete. Center Y = %d & Center X = %d\n\r", yCenter, xCenter);

     //_delay_ms(500);
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

static struct CANMessage receivedMessage;
static uint8_t joystickval;
static short int new_refrerence;
ISR(INT4_vect) {
  //printf("Message interrupt!!!\n\r");

  uint8_t int_flags = MCP_reads(MCP_CANINTF);

  //clear interrupt flags in CAN controller
  MCP_writes(MCP_CANINTF, 0x00);

  uint8_t bufferZero = int_flags & 0b01;
  uint8_t bufferOne = int_flags & 0b10;

  //short int scaledJoystickValue;


  if(bufferZero) {
    //TODO
    receivedMessage = can_data_receive();

    switch (receivedMessage.id) {
      case 1: //Quad message, contains all ADC values
        joystickval = receivedMessage.data[3];
        new_refrerence = scaleJoystickSpeed(joystickval);
        CONTROLLER_setReference(new_refrerence);
        break;
      case 2: //Button message, contains all buttons
        //check if joystick button is pressed
        if(receivedMessage.data[0] & 0b1) {
          SOLENOID_fire();
        }
        break;
    }
    //printf("Received data: %u\r\n", receivedMessage.data[0]);

    //printf(" Scaled value: %hu\n\r", getScaledSensorValue(receivedMessage.data[0]));
    //SERVO_SetDutyCycle(receivedMessage.data[0]);
    //MOTOR_setMovement(receivedMessage.data[1]);


  } else if(bufferOne) {
    //TODO
  }

  //clear interrupt flag
  EIFR &= ~(1<<4);
}

ISR(TIMER3_OVF_vect) {
   CONTROLLER_updateController();
 }

ISR(BADISR_vect){
  printf("BAD INTERRUPT!\n\r");
}
