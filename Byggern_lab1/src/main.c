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
//#include <board.h>
//#include <asf.h>
//#include "ASF/common/boards/board.h"
#include "UARTDriver.h"
#include "SRAMDriver.h"

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	/*
	DDRA = 0xFF;
	//enable ting

	DDRE = 0x02;
	//PORTE &= ~(1 << PE1);
	//USART_Init();

	PORTA |= (1 << PA0) | (1 << PA1);

	//_delay_ms(300);
	PORTE |= (1 << PE1);

	//_delay_ms(300);

	PORTE &= ~(1 << PE1);
	*/
	_delay_ms(3000);
	USART_Init();
	_delay_ms(300);
	SRAM_init();
	_delay_ms(1000);
	SRAM_test();

	while(1) {


		_delay_ms(300);


	}

	/*
	DDRA =  0x01;

	while(1) {
		PORTA |= (1 << PA0);
		_delay_ms(500);
	}
	*/
}
