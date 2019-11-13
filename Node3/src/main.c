#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>
#include "MCP2515.h"
//#include "MCPDriver.h"
//#include "CANDriver.h"
#include "SPIDriver.h"


void main(){
    //cli();
    SPI_init();

    //TODO IO pins used to blink LED, for heartbeat and testing
    DDRC |= (1<<PC0)|(1<<PC3);

    char a = 0xAA;
    //sei();
    while(1){
        //Heartbeat
        PORTC ^= (1<<PC3);

        //Transmit, but noting happens. SCK, MOSI pins don't change
        SPI_transmit(a);
        _delay_ms(1000);
    }
}

/*
ISR(INT0_vect){
    //PORTC |= (1<<PC3);
    
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
*/