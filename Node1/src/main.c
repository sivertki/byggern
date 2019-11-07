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
#include "SPIDriver.h"
#include "MCPDriver.h"
#include "UARTDriver.h"
#include "SRAMDriver.h"
#include "ADCDriver.h"
#include "OLEDDriver.h"
#include "MenuSystem.h"
#include <avr/pgmspace.h>
#include "CANDriver.h"
#include "MCP2515.h"
#include <avr/interrupt.h>


#define BASE_ADDRESS 0x1000



int main (void)
{
	cli();
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
	ADC_interrupt_enable();



	// Running calibration function on the joystick.
	//joy_cal();

	//const char charactera PROGMEM = 'A';
	//const char characterb[] PROGMEM = "heisann og hoppsann og fallerallera, paa julekvelden da skal alle sammen vaere glad";
	//const char characterf PROGMEM = "F";

	//_delay_ms(200);
	/*
	printf("Initializing OLED\n\r");
	OLED_init();
	printf("OLED initilaized\n\r");
	OLED_reset();
	_delay_ms(200);
	//SRAM_test();
	_delay_ms(200);
	//OLED_printf(characterb);
	menu_home();
	*/
	printf("Init starting...\n\r");
	SPI_init();
	printf("Init complete.\n\r");
	PORTB |= (1<<DD_SS);

	MCP_init();

  /*
	PORTB &= ~(1<<DD_SS);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_RXF0SIDH);
	SPI_transmit(0b10101010);
	PORTB |= (1<<DD_SS);

	printf("Setting SS low\n\r");
	PORTB &= ~(1<<DD_SS);
	printf("Starting transmit...\n\r");
	SPI_transmit(MCP_READ);
	printf("Instruction sent.\n\r");
	SPI_transmit(MCP_RXF0SIDH);
	printf("Init address sent.\n\r");
	SPI_transmit(0xFF);
	printf("Innhold i CANSTAT: %d\n\r", SPI_receive());
	PORTB |= (1<<DD_SS);
	*/

	//printf("Innhold i CANSTAT: %d\n\r", MCP_reads(MCP_RXF0SIDH));

	can_init();

	struct CANMessage quadChannelMessage;
	quadChannelMessage.id = 1;
	quadChannelMessage.length = 4;
	struct QuadChannel qc;

	sei();
	while(1) {

		//Poll ADCs
		qc = ADC_get_adc_values();

		quadChannelMessage.data[0] = qc.chan1;
		quadChannelMessage.data[1] = qc.chan2;
		quadChannelMessage.data[2] = qc.chan3;
		quadChannelMessage.data[3] = qc.chan4;
		can_message_send(&quadChannelMessage);

		//receiveMessage = can_data_receive();
		_delay_ms(50);
		//Poll buttons


		//printf("%u\n\r", receiveMessage.data[0]);
		//printf("%u\n\r", receiveMessage.data[1]);

		/*
		struct QuadChannel in;
		in = get_adc_valueget_adc_valuess();
		struct ButtonStruct butt;
		butt = get_button_values();
		*/

		//OLED_printf(characterb);
		//_delay_ms(2000);
		//printf("LEFT BUTTON: %d, RIGHT BUTTON: %d, JOY BUTTON:%d, LS: %d , RS: %d, Y: %d, X: %d \n\r", butt.lb, butt.rb, butt.jb, in.chan1, in.chan2, in.chan3, in.chan4);
		//OLED_reset();
		//Direction dir = joy_dir();
		//struct ButtonStruct butt = get_button_values();
		//printf("direction: %d, button: %d\n\r", dir, butt.jb);
		//menu_nav(dir, butt);
		//joy_dir();

		//_delay_ms(200);

	}

}

ISR(INT0_vect) {
  printf("Message interrupt!!!\n\r");

  uint8_t int_flags = MCP_reads(MCP_CANINTF);

  uint8_t bufferZero = int_flags & 0b01;
  uint8_t bufferOne = int_flags & 0b10;

  if(bufferZero) {
    //TODO
  } else if(bufferOne) {
    //TODO
  }

  //clear interrupt flag
  GIFR &= ~(1<<3);
}



ISR(INT2_vect) {
	printf("Button interrupt!\n\r");
	struct CANMessage buttonMessage;
	buttonMessage.id = 2;
	buttonMessage.length = 1;
	struct  ButtonStruct bs;

	bs = ADC_get_button_values();
	buttonMessage.data[0] = (bs.lb << 2) | (bs.rb << 1) | (bs.jb << 0);
	can_message_send(&buttonMessage);
}

ISR(BADISR_vect){
  printf("BAD INTERRUPT!\n\r");
}
