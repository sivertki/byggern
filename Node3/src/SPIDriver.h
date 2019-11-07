/**
 * \file SPIDriver2.h
 * \brief A file that facilitates the SPI communication between the I/O board and the Arduino Mega2560.
 */

#define DDR_SPI DDRB
#define DD_SS PB7
#define DD_MOSI PB2
#define DD_MISO PB3
#define DD_SCK PB1

/**
 * \brief A function that initilaizes the SPI communication on the ATMega162.
 */
void SPI_init();

/**
 * \brief A function that transmits the data specified in the parameter over the SPI to the MCP.
 * \param cData A char containing the data that is to be sent to the MCP.
*/
void SPI_transmit(char cData);

/**
 * \brief A function that recieves data sent from the MCP over the SPI.
*/
char SPI_receive(void);
