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
    printf("Received data: %s\n\r");
    receivedMessage = can_data_receive();
    _delay_ms(100);
    printf("%u\n\r", receivedMessage.data[0]);
    */
    /*
    uint8_t canstatInfo = (MCP_reads(MCP_CANSTAT)>>1) & 0b0000111;

    if(canstatInfo == )
    */
    _delay_ms(1000);
    printf("%d\n\r", TCNT1);
  }

}
