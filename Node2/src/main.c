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



int main (void) {
  cli();
  // Set pin49 as output
  DDRL |= (1<<PL0);
  USART_Init();
  SPI_init();
  can_init();
  servoInit();
  IR_init();
  sei();

  struct CANMessage receivedMessage;
  uint8_t joystickval;
  int result;
  while(1) {

    //set high
    /*
    PORTL |= (1<<PL0);
    _delay_ms(1000);
    //set low
    PORTL &= ~(1<<PL0);
    _delay_ms(1000);
    */

    result = IR_detect_goal();

    if(result == 1) {
      printf("GOAAAAAL!\n\r");
    }
    else {
      //printf("No goal.\n\r");
    }
    //printf("\n\r");
    //receivedMessage = can_data_receive();
    //printf("Received data: %u", receivedMessage.data[0]);
    //printf(" Scaled value: %hu\n\r", getScaledSensorValue(receivedMessage.data[0]));
    //SERVO_SetDutyCycle(receivedMessage.data[0]);
    //ADCVal = IR_read();

    //printf("ADCVal : %u\n\r", ADCVal);
    /*
    uint8_t canstatInfo = (MCP_reads(MCP_CANSTAT)>>1) & 0b0000111;

    if(canstatInfo == )
    */

    _delay_ms(200);

  }

}
