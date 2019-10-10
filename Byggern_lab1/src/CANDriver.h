/**
 * \file CANDriver.h
 * \brief A file
 */

struct CANMessage {
  unsigned int id;
  uint8_t length;
  uint8_t data[8];
};

/**
 * \brief A function Initializing the CAN
 */
void can_init();
