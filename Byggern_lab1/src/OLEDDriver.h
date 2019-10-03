/**
 * \file OLEDDriver.h
 * \brief A file containing the driver for the OLED.
 */

#include "DEFINITIONS.h"
#include <stdio.h>

/**
 * \brief A function that initilaizes OLED.
 */
void OLED_init();

/**
 * \brief A function that writes a single character based on the value of the param.
 * \param data An uint8_t that contains the value of the character to be written.
 */
void oled_write_single_char(uint8_t data);

/**
 * \brief A function that initilaizes USART communication
 */
void OLED_reset();

/**
 * \brief A function that initilaizes USART communication
 * \param str
 */
void OLED_printf(char str[]);

/**
 * \brief A struct
 */
struct OLED_position {
  uint8_t row;
  uint8_t column;
  uint8_t line;
};
