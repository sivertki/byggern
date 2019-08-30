#include <avr/io.h>
#include <stdio.h>
#include "UARTDriver.h"


void USART_Init (void) {
	// Set baud rate
	UBRR0H = (unsigned char) (MYUBRR >> 8);
	UBRR0L = (unsigned char) MYUBRR;

	// enable receiver and transmitter
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0);

	// set frame format: 8 data, 2 stop bit
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);

	// Enable IO-stream
	fdevopen(USART_transmit, USART_Receive);
}


void USART_transmit(unsigned char data){
	// Wait for empty transmit buffer
	while ( !(UCSR0A & (1<<UDRE0)) );

	// Put data into buffer, sends the data
	UDR0 = data;
}


unsigned char USART_Receive(void){
	//Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)) );

	//Get and return received data from buffer
	return UDR0;
}
