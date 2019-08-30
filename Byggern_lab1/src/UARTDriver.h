#include <avr/io.h>

#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR 31 //FOSC/16/BAUD - 1

void USART_Init(void);
void USART_transmit(unsigned char data);
unsigned char USART_Receive(void);
