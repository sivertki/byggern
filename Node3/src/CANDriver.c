#include "CANDriver.h"
#include "MCP2515.h"

void can_init() {
  MCP_writes(MCP_CANCTRL, 0x0<<5);
}

void can_message_send(struct CANMessage* message) {
  unsigned int tempId = message->id;

  uint8_t threeLSB = 0x7 & message->id;
  uint8_t SIDL = (tempId<<5) | 0<<3;

  MCP_writes(TXB0SIDH, tempId>>3);
  MCP_writes(TXB0SIDL, SIDL);
  MCP_writes(TXB0DLC, (0<<6) | message->length);

  // printf("ThreeLSB %u\n\r", threeLSB);
  // printf("ID 3 RS %u\n\r", tempId>>3);

  for(uint8_t i = 0; i < message->length; i++) {
      MCP_writes(TXB0D0 + i, message->data[i]);
  }

  MCP_requestToSend(0);
}

struct CANMessage can_data_receive() {
  struct CANMessage returnMessage;

  uint8_t threeLSB = (MCP_reads(RXB0SIDL) & 0b11100000)>>5;
  unsigned int SIDH = MCP_reads(RXB0SIDH)<<3;

  returnMessage.id = SIDH | threeLSB;

  returnMessage.length = MCP_reads(RXB0DLC) & 0x0F;

  for(uint8_t i = 0; i < returnMessage.length; i++) {
      returnMessage.data[i] = MCP_reads(RXB0D0 + i);
  }

  MCP_writes(MCP_CANINTF, 0x00);
  return returnMessage;
}

//can_error()
//can_transmit_complete()
//can_int_vect()
