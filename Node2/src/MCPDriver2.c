#include "MCPDriver2.h"
#include "SPIDriver2.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/io.h>

/*
uint8_t MCP_init(){
  uint8_t value;
  SPI_init();
  // InitializeSPI
  MCP_reset();
  // Send reset-command
  // Self-test
  MCP_reads(MCP_CANSTAT, &value);
  if((value& MODE_MASK)  != MODE_CONFIG) {
    printf(”MCP2515 is NOT in configurationmode afterreset!\n”);
    return 1;
  }
  // More initialization
  return 0;
}
*/


uint8_t MCP_reads(uint8_t address){
  uint8_t result;
  PORTB &= ~(1<<DD_SS); // Select CAN-controller
  SPI_transmit(MCP_READ); // Send read instruction
  SPI_transmit(address); // Send address
  SPI_transmit(0xFF);   // Send dummy byte
  // SPI_transmit(0xFF);   // Send dummy byte another time to give more time to MCU...
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

void MCP_reset() {
  PORTB &= ~(1<<DD_SS);
  SPI_transmit(MCP_RESET);
  PORTB |= (1<<DD_SS);
}

uint8_t MCP_readRX() {
  uint8_t result;
  PORTB &= ~(1<<DD_SS); // Select CAN-controller
  SPI_transmit(MCP_READ_RX0); // Send readRX instruction
  //SPI_transmit(address); // Send address
  SPI_transmit(0xFF);   // Send dummy byte
  // SPI_transmit(0xFF);   // Send dummy byte another time to give more time to MCU...
  result = SPI_receive(); // Read result
  PORTB |= (1<<DD_SS); // DeselectCAN-controller

  return result;
}
