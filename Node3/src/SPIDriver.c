#include "SPIDriver.h"
#include "MCP2515.h"
#include <avr/io.h>

void SPI_transmit(char cData) {
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}

void SPI_init() {
  /* Set MOSI and SCK and SS as output, all others input */
  DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK) | (1<<DD_SS);
  /* set MISO as input */
  DDR_SPI &= ~(1<<DD_MISO);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

char SPI_receive(void){
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return data register */
  return SPDR;
}
