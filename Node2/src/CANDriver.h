/**
 * \file CANDriver.h
 * \brief A file that enables the CAN communications between the nodes.
 */

#include <stdio.h>

/**
 * An enum containing the two different buffers that the CAN message can be located at.
 */
typedef enum Buffer{BufferZero, BufferOne} Buffer;

/**
 * A struct containing the information transmitted over the CAN bus.
 */
struct CANMessage {
  unsigned int id;  /**< The ID of the message. */
  uint8_t length;   /**< The length of the CAN data field (in bytes). */
  uint8_t data[8];  /**< The data contained in the message. */
};

/**
 * \brief A function Initializing the CAN controller.
 */
void can_init();

/**
 * \brief A function that sends a CANMEssage struct over the CAN network.
 * \param message A CANMessage containing the message that is to be sent.
 */
void can_message_send(struct CANMessage* message);

/**
 * \brief A function that recieves data from the CAN bus.
 * \param buf A Buffer containing the buffer that is to be read.
 * \return Returns a CANMessage containing the message read from the buffer.
 */
struct CANMessage can_data_receive(Buffer buf);
