#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SPIDriver2.h"


int main (void) {
  // Set pin49 as output
  DDRL |= (1<<PL0);

  SPI_init();

  while(1) {

    //set high
    PORTL |= (1<<PL0);
    _delay_ms(1000);
    //set low
    PORTL &= ~(1<<PL0);
    _delay_ms(1000);
  }
}
