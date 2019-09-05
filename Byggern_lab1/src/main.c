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

#define BASE_ADDRESS 0x1000

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
	_delay_ms(500);

	USART_Init();
	SRAM_init();

	SRAM_test();
	while(1) {
		_delay_ms(300);
	}
	/*
	unsigned char OLED = '0';
	unsigned char ADC = '1';
	unsigned char SRAM = '2';


	//SRAM_test();
	uint8_t data = 0xAB;
	volatile char *ext_dev = (char *) BASE_ADDRESS;

	uint16_t OLED_addr = 0x0000;
	uint16_t ADC_addr = 0x0400;
	uint16_t SRAM_addr = 0x0850;

	while(1) {

		unsigned char msg = USART_Receive();


		if(msg == OLED) {
			ext_dev[OLED_addr] = data;
		}
		else if(msg == ADC) {
			ext_dev[ADC_addr] = data;
		}
		else if(msg == SRAM) {
			ext_dev[SRAM_addr] = data;
		}


		_delay_ms(300);


	}
	*/

	/*
	DDRA =  0x01;

	while(1) {
		PORTA |= (1 << PA0);
		_delay_ms(500);
	}
	*/
}
