#include "MCPDriver.h"
#include "SPIDriver.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void MCP_init() {
  //MCP_reset();
  //Enable interrupt on MCP2515 for both receive buffers
  MCP_bitModify(MCP_CANINTE, 0x03, 0x03); //address, mask , data
  //Enable external interrupts for INT0 for ATMega168
  EICRA &= ~(1<<ISC01 | 1<<ISC00);
  EIMSK |= (1<<0);
}

uint8_t MCP_reads(uint8_t address){
  uint8_t result;
  PORTD &= ~(1<<PD4);
  //PORTB &= ~(1<<DD_SS); // Select CAN-controller
  SPI_transmit(MCP_READ); // Send read instruction
  SPI_transmit(address); // Send address
  SPI_transmit(0xFF);   // Send dummy byte
  // SPI_transmit(0xFF);   // Send dummy byte another time to give more time to MCU...
  result = SPI_receive(); // Read result
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS); // DeselectCAN-controller

  return result;
}

void MCP_writes(uint8_t address, uint8_t data) {
  //PORTB &= ~(1<<DD_SS);
  PORTD &= ~(1<<PD4);
  SPI_transmit(MCP_WRITE);
  SPI_transmit(address);
  SPI_transmit(data);
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS);
}

void MCP_requestToSend(uint8_t select) {
  //PORTB &= ~(1<<DD_SS);
  PORTD &= ~(1<<PD4);

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
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS);

}

void MCP_bitModify(uint8_t address, uint8_t mask, uint8_t data) {
  //PORTB &= ~(1<<DD_SS);
  PORTD &= ~(1<<PD4);
  SPI_transmit(MCP_BITMOD);
  SPI_transmit(address);
  SPI_transmit(mask);
  SPI_transmit(data);
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS);
}

uint8_t MCP_readStatus() {
  uint8_t temp;
  //PORTB &= ~(1<<DD_SS);
  PORTD &= ~(1<<PD4);
  SPI_transmit(MCP_READ_STATUS);
  SPI_transmit(0xFF);
  temp = SPI_receive();
  SPI_transmit(0xFF);
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS);
  return temp;
}

/**
 * \brief A function that transmits a reset command to the MCP.
 */
void MCP_reset() {
  //PORTB &= ~(1<<DD_SS);
  PORTD &= ~(1<<PD4);
  SPI_transmit(MCP_RESET);
  PORTD |= (1<<PD4);
  //PORTB |= (1<<DD_SS);
}
