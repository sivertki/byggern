#include <avr/io.h>

void IR_init() {
  //Using pin PA1, pin 77 on atmega, pin 23 on arduino Mega, to power IR emitter
  DDRA |= 1<<PA1;
  PORTA |= 1<<PA1;

  //using A15, pin 82 on Atmega, pin A15 on arduino Mega to IR receiver
  //DDRK |= 0<<A15;

  //Enabling ADC
  ADCSRA |= 1 << ADEN;

  //TODO finish
}

//TODO funciton to turn off IR emitter? For when game is not played
