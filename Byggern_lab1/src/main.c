/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
 
#define F_CPU 4915200 // Clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>
#include "UARTDriver.h"

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	
	unsigned char letter = 'e';
	
	USART_Init();
	
	while(1) {
		
		USART_transmit(letter);
		_delay_ms(100);
		
	}
	
	/*
	DDRA =  0x01;
	
	while(1) {
		PORTA |= (1 << PA0);
		_delay_ms(500);
	}
	*/
}
