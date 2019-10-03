/**
 * \file UARTDriver.h
 * \brief A file containing the driver for the UART.
 */

 #include <avr/io.h>

/**
* \brief Defining the clock speed of the ATMega162.
*/
#define FOSC 4915200

/**
* \brief Defining the baud rate of the communication with the PC.
*/
#define BAUD 9600

/**
* \brief  FOSC/16/BAUD - 1
*/
#define MYUBRR 31

/**
 * \brief A function that initilaizes USART communication
 */
void USART_Init(void);

/**
 * \brief A function that transmits the data specified in the param.
 * \param data An unsigned char that will be transmitted over the USART.
 */
void USART_transmit(unsigned char data);

/**
 * \brief A function that recieves data through the USART.
 * \return An unsigned char that was recieved through the USART.
 */
unsigned char USART_Receive(void);
