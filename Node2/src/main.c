#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SPIDriver2.h"
#include "MCPDriver2.h"
#include "CANDriver.h"
#include "UARTDriver2.h"
#include "ServoDriver.h"
#include "avr/interrupt.h"


int main (void) {
  // Set pin49 as output
  DDRL |= (1<<PL0);

  USART_Init();
  SPI_init();
  can_init();
  servoInit();
  sei();
  struct CANMessage receivedMessage;
  uint8_t joystickval;
  while(1) {

    //set high
    /*
    PORTL |= (1<<PL0);
    _delay_ms(1000);
    //set low
    PORTL &= ~(1<<PL0);
    _delay_ms(1000);
    */

    receivedMessage = can_data_receive();
    printf("Received data: %u", receivedMessage.data[0]);
    printf(" Scaled value: %hu\n\r", getScaledSensorValue(receivedMessage.data[0]));
    SERVO_SetDutyCycle(receivedMessage.data[0]);
    /*
    uint8_t canstatInfo = (MCP_reads(MCP_CANSTAT)>>1) & 0b0000111;

    if(canstatInfo == )
    */

    _delay_ms(200);

  }

}
