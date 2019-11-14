#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "MCPDriver.h"
#include "CANDriver.h"
#include "SPIDriver.h"

#define BAUD 9600
#define MYUBBR 103 //TODO calculate FOSC/16/BAUD-1

#define DDR_SPI DDRB
#define DD_SS DDB2
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5


struct CANMessage receivedMessage;

/*
void UART_init() {
    //set baud rate
    UBRR0H = (unsigned char) (MYUBBR>>8);
    UBRR0L = (unsigned char) MYUBBR;

    // Enable receiver and transmitter
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0);

    // Set frame format: 8 data, 2 stop bit
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);

}
void UART_transmit ( unsigned char *data) {
    uint8_t loop_var=0;
    while(data[loop_var] != '\0') {
        while(!(UCSR0A & (1<<UDRE0)));

        UDR0 = data[loop_var];
        loop_var ++;
    }
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = '\r';
}
*/
void main(){
    cli();
    SPI_init();
    _delay_ms(20);
    MCP_init();
    _delay_ms(20);
    can_init();
    //TODO IO pins used to blink LED, for heartbeat and testing
    DDRC |= (1<<PC0)|(1<<PC3);
    DDRB |= (1<<PB0)|(1<<PB2);
    //char a = 0xAA;
    
    sei();
    while(1){
        //Heartbeat
        PORTC ^= (1<<PC0);
        //Transmit, but noting happens. SCK, MOSI pins don't change
        //SPI_transmit(a);
        //sprintf(data_str, "SPDR: %2x, SPCR: %2x, SPSR: %2x\n", SPDR, SPCR, SPSR);
        //UART_transmit(data_str);
        //a++;
        _delay_ms(1000);
        
    }
}
/*
ISR(SPI_STC_vect) {
    //sprintf(data_str, "Transmit completed", SPDR, SPCR, SPSR);
    //UART_transmit("data_str");
    PORTB |= (1<<DD_SS);
    PORTC ^= (1<<PC3);
}
*/

ISR(INT0_vect){
    PORTC ^= (1<<PC3);
    _delay_ms(100);
    
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
