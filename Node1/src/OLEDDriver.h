/**
 * \file OLEDDriver.h
 * \brief A file containing the driver for the OLED.
 */

#include "DEFINITIONS.h"
#include <stdio.h>

/**
 * \brief A struct that contains the position of the "cursor" on the OLED screen.
 */
struct OLED_position {
  uint8_t row;  /**< The current position of the OLED "cursor" in terms of row number, [0, 64]. */
  uint8_t column; /**< The current position of the OLED "cursor" in terms of column number, [0, 128]. */
  uint8_t line; /**< The current position of the OLED "cursor" in terms of line number, [0, 8]. */
};

/**
 * \brief A function that initilaizes OLED according to its data sheet.
 */
void OLED_init();

/**
 * \brief A function that writes a single character based on the value of the param.
 * \param data An uint8_t that contains the value of the character to be written.
 */
void oled_write_single_char(uint8_t data);

/**
 * \brief A function that resets the OLED screen
 * This function clears the contents of the OLED screen and puts the current position of the
 * "cursor" to the top left of the screen.
 */
void OLED_reset();

/**
 * \brief A function that writes out the contents of the parameter to the OLED screen.
 * \param str[] A string / char array that will be written to the OLED screen.
 * This function will iterate through the string / char array recieved as the parameter
 * and will print it out at the current "cursor" position on the screen. It will drop
 * down to the next row when the screen lenght is full on the current row.
 */
void OLED_printf(char str[]);

/**
 * \biref A function that moves the "cursor" to the position specified by the parameters.
 * \param line An uint8_t containing the line that the cursor should move to.
 * \param column An uint8_t containing the column that the cursor should move to.
 */
void OLED_goto_pos(uint8_t line, uint8_t column);

/**
 * \biref A function that moves the "cursor" to the line specified by the parameter.
 * \param line An uint8_t containing the line that the cursor should move to.
 */
void OLED_goto_line(uint8_t line);

/**
 * \biref A function that sets the font size for the writing on the OLED.
 * \param fsize An uint8_t containing the size that is selected, [4, 5, 8].
 */
void OLED_set_font(uint8_t fsize);
