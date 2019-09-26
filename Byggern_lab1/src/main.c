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

#define F_CPU 4915200UL // Clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
//#include <board.h>
//#include <asf.h>
//#include "ASF/common/boards/board.h"
#include "UARTDriver.h"
#include "SRAMDriver.h"
#include "ADCDriver.h"
#include "OLEDDriver.h"
#include "MenuSystem.h"
#include <avr/pgmspace.h>



#define BASE_ADDRESS 0x1000

int main (void)
{
	volatile char *ext_dev = (char *) BASE_ADDRESS;
	// Insert system clock initialization code here (sysclk_init()).

	// Setting the pins PB0 & PB1 as INPUTS.
	DDRB &= ~(1<<PB0);
	DDRB &= ~(1<<PB1);

	//setting pin PB2 as INPUT
	DDRB &= ~(1<<PB2);
	//setting up pull-up resistor for PB2
	PORTB |= (1<<PB2);

	_delay_ms(500);

	USART_Init();
	SRAM_init();


	// Running calibration function on the joystick.
	joy_cal();

	const char charactera PROGMEM = 'A';
	const char characterb[] PROGMEM = "heisann og hoppsann og fallerallera, paa julekvelden da skal alle sammen vaere glad";
	//const char characterf PROGMEM = "F";

	_delay_ms(200);
	printf("Initializing OLED\n\r");
	OLED_init();
	printf("OLED initilaized\n\r");
	OLED_reset();
	_delay_ms(200);
	SRAM_test();
	_delay_ms(200);
	//OLED_printf(characterb);
	menu_home();
	while(1) {

		/*
		struct QuadChannel in;
		in = get_adc_values();
		struct ButtonStruct butt;
		butt = get_button_values();
		*/

		//OLED_printf(characterb);
		//_delay_ms(2000);
		//printf("LEFT BUTTON: %d, RIGHT BUTTON: %d, JOY BUTTON:%d, LS: %d , RS: %d, Y: %d, X: %d \n\r", butt.lb, butt.rb, butt.jb, in.chan1, in.chan2, in.chan3, in.chan4);
		//OLED_reset();
		Direction dir = joy_dir();
		struct ButtonStruct butt = get_button_values();
		//printf("direction: %d, button: %d\n\r", dir, butt.jb);
		menu_nav(dir, butt);
		//joy_dir();


	}

}
