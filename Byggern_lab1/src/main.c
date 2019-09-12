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
#include "ADCDriver.h"

#define BASE_ADDRESS 0x1000

int main (void)
{
	volatile char *ext_dev = (char *) BASE_ADDRESS;
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

	// Setting the pins PB0 & PB1 as INPUTS.
	DDRB &= ~(1<<PB0);
	DDRB &= ~(1<<PB1);

	_delay_ms(500);

	USART_Init();
	SRAM_init();

	// Running calibration function on the joystick.
	joy_cal();

	//SRAM_test();
	while(1) {



		_delay_ms(700);
		/*
		struct QuadChannel in;
		in = get_adc_values();
		printf("LS: %d , RS: %d, Y: %d, X: %d\n\r", in.chan1, in.chan2, in.chan3, in.chan4);
		*/


		struct ButtonStruct butt;
		butt = get_button_values();
		printf("LEFT BUTTON: %d, RIGHT BUTTON: %d\n\r", butt.lb, butt.rb);
		

		//struct Percentage per;
		//per = joy_pos();
		//printf("Y-POS: %d, X-POS: %d \n\r", per.yPercentage, per.xPercentage);

	}

}
