/**
 * \file A file
 */

#include <stdio.h>

/**
 * \brief A function that initilaizes the MCP2515, and its interrupts.
*/
void MCP_init();

/**
 * \brief A function that reads an 8-bit value from the register specified in the parameter.
 * \param address A uint8_t containing the address of the register that is to be read.
*/
uint8_t MCP_reads(uint8_t address);

/**
 * \brief A function that writes a byte of data to the register specified in the parameter.
 * \param address An uint8_t containing the address of the register that is to be written to.
 * \param data An uint8_t containing the byte of data that is to be written to the register.
*/
void MCP_writes(uint8_t address, uint8_t data);

/**
 * \brief A function that requests the MCU to send data from one / all of the TX0, TX1, TX2 register(s).
 * \param select An uint8_t that is used to select the register(s) that is wanted. [0, 2] to select
 * the corresponding TX register and 3 to select ALL THREE registers.
*/
void MCP_requestToSend(uint8_t select);

/**
 * \brief A function that enables clearing or setting of individual bits in the specified status
 * and control register.
 * \param address An uint8_t containing the address of the register the manipulation will affect.
 * \param mask An uint8_t containing the mask that controls which bits in the register are allowed to change.
 * \param data An uint8_t containing the data that will be writen to the bits allowed to change.
*/
void MCP_bitModify(uint8_t address, uint8_t mask, uint8_t data);

/**
 * \brief A function that reads the some of the often accessed status bits of the MCP.
 * \return A uint8_t containing the data transmitted from the MCP.
*/
uint8_t MCP_readStatus();
