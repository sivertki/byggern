#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "MCPDriver.h"
#include "CANDriver.h"

volatile struct CANMessage receivedMessage;

void main(){
    cli();
    can_init(); //TODO name protocol
    MCP_init();
    //SPI_init(); //is this needed? Needs to be included if so.

    //TODO set in IO driver if to be used
    DDRC |= (1<<0);


    sei();
    while(1){
        _delay_ms(2000);
        //PORTC ^= (1<<0);
    }
}

ISR(INT0_vect){
    PORTC ^= ~(1<<0);
    uint8_t int_flags = MCP_reads(MCP_CANINTF);

    //clear interrupt flags in CAN controller
    MCP_writes(MCP_CANINTF, 0x00);

    uint8_t bufferZero = int_flags & 0b01;
    uint8_t bufferOne = int_flags & 0b10;

    if(bufferZero) {
        //TODO
        receivedMessage = can_data_receive();
        //TODO check id of message, and act upon it

    } else if(bufferOne) {
        //TODO. Maybe do the same as with buffer zero? just run an external function
    }

    //clear interrupt flag
    EIFR &= ~(1<<0);
}
