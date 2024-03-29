#include "MCPDriver.h"
#include "SPIDriver.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void MCP_init() {
  //Enable interrupt on MCP2515 for both receive buffers
  MCP_bitModify(MCP_CANINTE, 0x03, 0x03); //address, mask , data
  //Enable external interrupts for INT0 for ATMega162
  MCUCR &= ~(1<<ISC01 | 1<<ISC00);
  GICR |= (1<<6);
}

uint8_t MCP_reads(uint8_t address){
  uint8_t result;
  PORTB &= ~(1<<DD_SS); // Select CAN-controller
  SPI_transmit(MCP_READ); // Send read instruction
  SPI_transmit(address); // Send address
  SPI_transmit(0xFF);   // Send dummy byte
  result = SPI_receive(); // Read result
  PORTB |= (1<<DD_SS); // DeselectCAN-controller

  return result;
}

void MCP_writes(uint8_t address, uint8_t data) {
  PORTB &= ~(1<<DD_SS);
  SPI_transmit(MCP_WRITE);
  SPI_transmit(address);
  SPI_transmit(data);
  PORTB |= (1<<DD_SS);
}

void MCP_requestToSend(uint8_t select) {
  PORTB &= ~(1<<DD_SS);

  switch (select) {
    case 0:
      SPI_transmit(MCP_RTS_TX0);
      break;
    case 1:
      SPI_transmit(MCP_RTS_TX1);
      break;
    case 2:
      SPI_transmit(MCP_RTS_TX2);
      break;
    case 3:
      SPI_transmit(MCP_RTS_ALL);
      break;
  }

  PORTB |= (1<<DD_SS);

}

void MCP_bitModify(uint8_t address, uint8_t mask, uint8_t data) {
  PORTB &= ~(1<<DD_SS);
  SPI_transmit(MCP_BITMOD);
  SPI_transmit(address);
  SPI_transmit(mask);
  SPI_transmit(data);
  PORTB |= (1<<DD_SS);
}

uint8_t MCP_readStatus() {
  uint8_t temp;
  PORTB &= ~(1<<DD_SS);
  SPI_transmit(MCP_READ_STATUS);
  SPI_transmit(0xFF);
  temp = SPI_receive();
  SPI_transmit(0xFF);
  PORTB |= (1<<DD_SS);
  return temp;
}

/**
 * \brief A function that transmits a reset command to the MCP.
 */
void MCP_reset() {
  PORTB &= ~(1<<DD_SS);
  SPI_transmit(MCP_RESET);
  PORTB |= (1<<DD_SS);
}
