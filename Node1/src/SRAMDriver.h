/**
 * \file SRAMDriver.h
 * \brief A file containing the driver for the SRAM.
 */

//#include <stdlib.h>
//#include <avr/io.h>

/**
 * \brief A function that initilaizes the SRAM for use.
 */
void SRAM_init(void);

/**
 * \brief A function that runs a test on the SRAM.
 */
void SRAM_test(void);

/**
 * \brief A function
 */
void SRAM_highscoreW(uint8_t score, uint8_t position);

/**
 * \brief A function
 */
uint8_t SRAM_highscoreR(uint8_t position);
