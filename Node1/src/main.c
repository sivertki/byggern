
#define F_CPU 4915200UL // Clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "SPIDriver.h"
#include "MCPDriver.h"
#include "UARTDriver.h"
#include "SRAMDriver.h"
#include "ADCDriver.h"
#include "OLEDDriver.h"
#include "MenuSystem.h"
#include "CANDriver.h"
#include "MCP2515.h"
#include "IO.h"

#define BASE_ADDRESS 0x1000



int main (void)
{
	cli();
	volatile char *ext_dev = (char *) BASE_ADDRESS;

	//----------INITIALIZATION------------//
	_delay_ms(500);
	USART_Init();
	printf("USART initialized\n\r");
	IO_init();
	printf("IO initialized\n\r");
	SRAM_init();
	printf("SRAM initialized\n\r");
	ADC_interrupt_enable();
	ADC_joystick_calibration();
	printf("ADC interrupts initialized\n\r");
	OLED_init();
	OLED_reset();
	MENU_home();
	printf("OLED initialized\n\r");
	SPI_init();
	printf("SPI Iiitialized\n\r");
	MCP_init();
	printf("MCP initialized\n\r");
	can_init();
	printf("CAN initialized\n\r");
	printf("\n\rAll inits complete\n\r\n\r");_delay_ms(1000);
	//------------INITIALIZATION COMPLETE-----------//

	struct CANMessage quadChannelMessage;
	quadChannelMessage.id = 1;
	quadChannelMessage.length = 4;
	struct QuadChannel qc;

	Direction dir;
	struct ButtonStruct butt;
	sei();
	while(1) {

		//Poll ADCs
		qc = ADC_get_adc_values();

		quadChannelMessage.data[0] = qc.chan1;
		quadChannelMessage.data[1] = qc.chan2;
		quadChannelMessage.data[2] = qc.chan3;
		quadChannelMessage.data[3] = qc.chan4;
		can_message_send(&quadChannelMessage);
		
		//Poll buttons
		//TODO
		dir = ADC_get_joystick_direction();
		butt = IO_get_button_values();

		//For controlling menu. Need to change setup of main, with states
		printf("direction: %d, button: %d\n\r", dir, butt.jb);
		MENU_nav(dir, butt);

		_delay_ms(200);
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

	bs = IO_get_button_values();
	buttonMessage.data[0] = (bs.lb << 2) | (bs.rb << 1) | (bs.jb << 0);
	can_message_send(&buttonMessage);
}

ISR(BADISR_vect){
  printf("BAD INTERRUPT!\n\r");
}

