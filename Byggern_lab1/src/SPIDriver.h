/**
 * \file SPIDriver.h
 * \brief A file that facilitates the SPI communication betwenn the MCP2515 and the ATMega162. 
 */

#define DDR_SPI DDRB
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

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
