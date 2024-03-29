#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SPIDriver.h"
#include "MCPDriver.h"
#include "CANDriver.h"
#include "UARTDriver.h"
#include "ServoDriver.h"
#include "avr/interrupt.h"
#include "IRDriver.h"
#include "MotorDriver.h"
#include "Controller.h"
#include "MCP2515.h"
#include "SolenoidDriver.h"

/**
 * \brief An uint8_t used to contain the score of the current game being played.
 */
static uint8_t gameScore = 0;

/**
 * \brief A Control struct used to hold the current control type.
 * Can be in these states: [SLIDER, JOYSTICK, INITIALIZE, NONE]
 */
Control control_type = JOYSTICK;

/**
 * \brief An enum that contains the two states of counting that can occur.
 */
typedef enum IsCounting {yesCounting, noCounting} IsCounting;

/**
 * \brief An IsCounting that keeps track of the current state of counting.
 */
IsCounting counting_state = noCounting;

/**
* \brief An int that is used to keep track of the game state.
* When this no longer is zero (but one) the game enters its fail state.
*/
int result = 0;


int main (void) {
  cli();
  USART_Init();
  SPI_init();
  can_init();
  SERVO_init();
  IR_init();
  MOTOR_initialize();
  SOLENOID_init();
  control_type = INITIALIZE;
  sei();
  CONTROLLER_Init();

  control_type = NONE;
  MCP_init();
  printf("Node 2 initialized!\n\r");

  while(1) {

    result += IR_detect_goal();

    if(result == 1) {
      printf("FAIL! GAME OVER!\n\r");
      struct CANMessage lossMessage;
      lossMessage.id = 3;
      lossMessage.length = 1;
      lossMessage.data[0] = gameScore;
      counting_state = noCounting;
      can_message_send(&lossMessage);
      result++;
      gameScore = 0;
    }

    _delay_ms(500);
  }
}

/**
 * \brief The interrupt generated by recieving a CAN message.
 * This interrupt will trigger when recieving a CAN message from the other nodes
 * and will make Node 2 read the appropriate registers containing the CAN message.
 */
ISR(INT4_vect) {

  // A CANMessage that is used for storing the last recieved CAN message.
  struct CANMessage receivedMessage;

  uint8_t joystickVal;
  uint8_t leftsliderVal;
  short int new_reference;
  uint8_t servoVal;

  uint8_t int_flags = MCP_reads(MCP_CANINTF);

  //clear interrupt flags in CAN controller
  MCP_writes(MCP_CANINTF, 0x00);

  uint8_t bufferZero = int_flags & 0b01;
  uint8_t bufferOne = int_flags & 0b10;

  if(control_type == INITIALIZE) {
    return;
  }


  if(bufferOne) {
      receivedMessage = can_data_receive(BufferOne);

  } else if(bufferZero) {
      receivedMessage = can_data_receive(BufferZero);
  }


  switch (receivedMessage.id) {
    case 0: //All ADC values in Slider mode

      // Position-control
      leftsliderVal = 255 - receivedMessage.data[0];
      CONTROLLER_setReference(leftsliderVal, SLIDER);

      // Servo-control
      servoVal = receivedMessage.data[1];
      SERVO_setDutyCycle(255 - servoVal); //To invert direction

      break;
    case 1: //All ADC values in Joystick mode

      // Speed-control
      joystickVal = receivedMessage.data[3];
      CONTROLLER_setReference(joystickVal, JOYSTICK);

      // Servo-control
      servoVal = receivedMessage.data[1];
      SERVO_setDutyCycle(255 - servoVal); //To invert direction

      break;
    case 2: //Button message, contains all buttons
      //check if joystick button is pressed
      if(receivedMessage.data[0] & 0b1) {
        SOLENOID_fire();
      }
      break;
    case 3:
      break;
    case 4:
      printf("GAME STARTING!!!\n\r");
      gameScore = 0;
      result = 0;
      counting_state = yesCounting;

      if(!receivedMessage.data[0]) {
        CONTROLLER_setControlTerms(0.15,0.00,0.35);
        control_type = JOYSTICK;
      }
      else if(receivedMessage.data[0]) {
        CONTROLLER_setControlTerms(2,0.005,0.2);
        control_type = SLIDER;
      }
      break;

  }

  //clear interrupt flag
  EIFR &= ~(1<<4);
}

/**
 * \brief An int used to make sure that the score doesnt increase too fast.
 */
int scoreIterator = 0;

/**
 * \brief This interrupt is generated by a timer.
 * This interrupt is responsible for updating the controller, which entails calculation
 * of the next controller output and clearing the encoder.
 */
ISR(TIMER3_OVF_vect) {
  if(control_type != NONE) {
    CONTROLLER_updateController(control_type);
  }

  if(counting_state == yesCounting) {
    scoreIterator++;

    if(scoreIterator == 100) {
      gameScore++;
      scoreIterator = 0;
      printf("gameScore %u, Node2 state: %d\n\r", gameScore, control_type);
    }
  }
 }

/**
 * \brief This interrupt is triggered when no other interrupt can be reached.
 * This interrupt will be triggered when there is an error with interrupts and
 * the correct interrupt does not exist or cannot be reached.
 */
ISR(BADISR_vect){
  printf("BAD INTERRUPT!\n\r");
}
