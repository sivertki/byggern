#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main (void) {
  //set pin49 as output
  DDRL |= (1<<PL0);

  while(1) {

    //set high
    PORTL |= (1<<PL0);
    _delay_ms(1000);
    //set low
    PORTL &= ~(1<<PL0);
    _delay_ms(1000);
  }
}
