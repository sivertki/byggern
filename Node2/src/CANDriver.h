/**
 * \file CANDriver.h
 * \brief A file
 */

 #include <stdio.h>

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
 */
void can_message_send(struct CANMessage* message);

/**
 * \brief A function that recieves data from the CAN bus.
 */
struct CANMessage can_data_receive(void);
