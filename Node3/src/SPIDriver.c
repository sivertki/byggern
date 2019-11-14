#include "SPIDriver.h"
#include "MCP2515.h"
#include <avr/io.h>

void SPI_transmit(char cData) {
  /* Start transmission */
  PORTC &= ~(1<<PC0);
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
  //Flip LED for testing. It does flip, so code runs here
  PORTC |= (1<<PC0);
  
}

void SPI_init() {
  /* Make sure power saving isn't blocking SPI*/
  PRR &= ~(1<<PRSPI);
  /* Set MOSI and SCK and SS as output, all others input */
  DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
  PORTB |= (1<<DD_SS);
  PORTC |= (1<<PC0);
  /* set MISO as input */
  DDR_SPI &= ~(1<<DD_MISO);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//(1<<SPIE)|;

}

char SPI_receive(void){
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return data register */
  return SPDR;
}
