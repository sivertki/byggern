
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
#include "IODriver.h"
#include "DEFINITIONS.h"

#define BASE_ADDRESS 0x1000

static volatile currentState;

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

	//Message struct used to send
	struct CANMessage ADCCANMessage;
	ADCCANMessage.id;
	ADCCANMessage.length = 4;
	struct QuadADCChannels qc;

	currentState = MENU;
	static volatile Direction dir;
	static volatile struct ButtonStruct butt;

	sei();
	while(1) {
		printf("Current state: %d\n\r", currentState);
		switch (currentState)
		{
			case PINGPONGJOY:
				//Poll ADCs and send it over CAN
				qc = ADC_get_adc_values();
				ADCCANMessage.data[0] = qc.chan1;
				ADCCANMessage.data[1] = qc.chan2;
				ADCCANMessage.data[2] = qc.chan3;
				ADCCANMessage.data[3] = qc.chan4;
				ADCCANMessage.id = 1;
				can_message_send(&ADCCANMessage);

				//Check if both touch buttons are pressed. If so, exit and print menu again
				butt = IO_get_button_values();
				if((butt.lb == 1) && (butt.rb == 1)) {
					currentState = MENU;
					MENU_home();
				}
				
				//printf("ADC VALUES: %u, %u, %u, %u\n\r", qc.chan1, qc.chan2, qc.chan3, qc.chan4);
				//TODO a way to exit pingping
				_delay_ms(200);
				break;
			case PINGPONGSLIDE:
				//TODO
				qc = ADC_get_adc_values();
				ADCCANMessage.data[0] = qc.chan1;
				ADCCANMessage.data[1] = qc.chan2;
				ADCCANMessage.data[2] = qc.chan3;
				ADCCANMessage.data[3] = qc.chan4;
				ADCCANMessage.id = 0;
				can_message_send(&ADCCANMessage);
				//Check if both touch buttons are pressed. If so, exit and print menu again
				butt = IO_get_button_values();
				if((butt.lb == 1) && (butt.rb == 1)) {
					currentState = MENU;
					MENU_home();
				}
				break;
			default: //MENU, CREDITS
				//Poll buttons
				dir = ADC_get_joystick_direction();
				butt = IO_get_button_values();
				//printf("Dir %d, butt %d \n\r", dir, butt);
				currentState = MENU_nav(dir, butt, currentState);
				//printf("Current state: %d\n\r", currentState);
				_delay_ms(200);
		}
	}
	
}

//Interrupt generated by received message on the CAN bus
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


//Interrupt generated by Joystick button
//TODO do we need switch case here?
ISR(INT2_vect) {
	//printf("Button interrupt! Current state: %d\n\r", currentState);
	if(currentState == PINGPONGJOY) {
		//printf("Button message sent over CAN\n\r");
		struct CANMessage buttonMessage;
		buttonMessage.id = 2;
		buttonMessage.length = 1;
		struct  ButtonStruct bs;

		bs = IO_get_button_values();
		buttonMessage.data[0] = (bs.lb << 2) | (bs.rb << 1) | (bs.jb << 0);
		can_message_send(&buttonMessage);
	}
}

ISR(BADISR_vect){
  printf("BAD INTERRUPT!\n\r");
}

