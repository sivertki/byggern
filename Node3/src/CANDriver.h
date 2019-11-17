/**
 * \file CANDriver.h
 * \brief A file
 */

 #include <stdio.h>
typedef enum Buffer{BufferZero, BufferOne} Buffer;
struct CANMessage {
  unsigned int id;
  uint8_t length;
  uint8_t data[8];
};

/**
 * \brief A function Initializing the CAN
 */
void can_init();

void can_message_send(struct CANMessage* message);

struct CANMessage can_data_receive(Buffer buf);
