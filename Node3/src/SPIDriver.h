/**
 * \file SPIDriver2.h
 * \brief A file that facilitates the SPI communication between the MCP2515 and the ATMega168.
 */

#define DDR_SPI DDRB
#define DD_SS DDB2
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5

/**
 * \brief A function that initilaizes the SPI communication on the ATMega168.
 */
void SPI_init();

/**
 * \brief A function that transmits the data specified in the parameter over the SPI to the MCP.
 * \param cData A char containing the data that is to be sent to the MCP.
*/
void SPI_transmit(char cData);

/**
 * \brief A function that recieves data sent from the MCP over the SPI.
 * \return Returns a char containing the data sent from the MCP over SPI.
*/
char SPI_receive(void);
