#include "IODriver.h"
#include <avr/io.h>


IO_init() {
    // Setting the pins PB0 & PB1 as INPUTS.
    // Touch buttons on IO card
	DDRB &= ~(1<<PB0);
	DDRB &= ~(1<<PB1);

	//setting pin PB2 as INPUT
    //Joystick button
	DDRB &= ~(1<<PB2);
	//setting up pull-up resistor for PB2
	PORTB |= (1<<PB2);
}

struct ButtonStruct IO_get_button_values() {
    struct ButtonStruct buttonValue;

    uint8_t read_port_b = PINB;

    bool left_button = read_port_b & (1<<PB1);
    bool right_button = read_port_b & (1<<PB0);
    bool joy_button = !(read_port_b & (1<<PB2));

    buttonValue.lb = left_button;
    buttonValue.rb = right_button;
    buttonValue.jb = joy_button;

    return buttonValue;
}